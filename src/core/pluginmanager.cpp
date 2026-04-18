//
// Created by Michal Přikryl on 10.04.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "pluginmanager.h"
#include <cstring>

#include "commands.h"
#include "events.h"
#include "entityio.h"

#include "source2toolkit/IToolkitApi.h"
#include "source2toolkit/IToolkitPlugin.h"

#include "pluginapi.h"
#include "utils/log.h"
#include "utils/paths.h"

PluginManager pluginManager;

static LibHandle OpenLib(const char* path, std::string& outError)
{
#ifdef _WIN32
    auto lib = LoadLibraryA(path);
    if (!lib)
    {
        outError = "LoadLibrary failed";
    }
    return lib;
#else
    dlerror();

    void* lib = dlopen(path, RTLD_NOW);
    if (!lib)
    {
        const char* err = dlerror();
        outError = err ? err : "unknown dlopen error";
    }

    return lib;
#endif
}

static void CloseLib(LibHandle lib)
{
#ifdef _WIN32
    FreeLibrary(lib);
#else
    dlclose(lib);
#endif
}

static void* GetSymbol(LibHandle lib, const char* name)
{
#ifdef _WIN32
    return (void*)GetProcAddress(lib, name);
#else
    return dlsym(lib, name);
#endif
}

static std::string FindPluginBinary(const std::string& name)
{
    namespace fs = std::filesystem;

    auto dir = paths::GetPluginsDirectory();

    if (!fs::exists(dir) || !fs::is_directory(dir))
        return "";

    for (const auto& entry : fs::directory_iterator(dir))
    {
        if (!entry.is_regular_file())
            continue;

        auto path = entry.path();

        if (path.extension() != ".stx")
            continue;

        if (path.stem().string().find(name) != std::string::npos)
        {
            return path.string();
        }
    }

    return "";
}

#define FAIL(msg) \
    do { \
        if (error && maxlen) snprintf(error, maxlen, "%s", msg); \
        if (lib) CloseLib(lib); \
        return false; \
    } while(0)

#define FAILF(fmt, ...) \
    do { \
        if (error && maxlen) snprintf(error, maxlen, fmt, __VA_ARGS__); \
        if (lib) CloseLib(lib); \
        return false; \
    } while(0)

bool PluginManager::IsPluginLoaded(const std::string& fullPath)
{
    auto normalized = std::filesystem::weakly_canonical(fullPath).string();

    for (auto& p : m_plugins)
    {
        auto existing = std::filesystem::weakly_canonical(p->path).string();

        if (existing == normalized)
            return true;
    }

    return false;
}

bool PluginManager::LoadPlugin(const char* name, char* error, size_t maxlen)
{
    std::string fullPath = FindPluginBinary(name);

    if (fullPath.empty())
    {
        if (error && maxlen)
            snprintf(error, maxlen, "Plugin '%s' not found", name);

        return false;
    }

    auto normalized = std::filesystem::weakly_canonical(fullPath).string();

    for (auto& p : m_plugins)
    {
        auto existing = std::filesystem::weakly_canonical(p->path).string();

        if (existing == normalized)
        {
            if (error && maxlen)
                snprintf(error, maxlen, "Plugin already loaded (same file)");
            return false;
        }
    }

    std::string dlErr;
    auto lib = OpenLib(fullPath.c_str(), dlErr);

    if (!lib)
    {
        if (error && maxlen)
            snprintf(error, maxlen, "%s", dlErr.c_str());

        FP_ERROR("Failed to load {}: {}", fullPath, dlErr);
        return false;
    }

    auto fn = (CreateInterfaceFn)GetSymbol(lib, "CreateInterface");
    if (!fn)
    {
        FAILF("CreateInterface not found in %s", fullPath.c_str());
    }

    int ret = 0;
    auto plugin = (IToolkitPlugin*)fn(TOOLKIT_PLAPI_NAME, &ret);

    if (!plugin || ret != TOOLKIT_IFACE_OK)
    {
        FAIL("Invalid plugin interface");
    }

    if (plugin->GetApiVersion() != TOOLKIT_PLAPI_VERSION)
    {
        FAIL("Plugin API version mismatch");
    }

    auto pl = std::make_unique<ToolkitPlugin>();
    pl->id = m_nextId++;
    pl->lib = lib;
    pl->api = plugin;
    pl->path = fullPath;

    m_plugins.push_back(std::move(pl));

    auto& stored = m_plugins.back();

    char err[256]{};
    if (!plugin->Load(stored->id, &pluginApi, err, sizeof(err), false))
    {
        FAILF("Plugin load failed: %s", err);
    }

    auto newId = m_plugins.back()->id;

    for (auto& p : m_plugins)
    {
        for (auto* l : p->listeners)
            l->OnPluginLoad(newId);
    }

    return true;
}

bool PluginManager::UnloadPlugin(PluginId id)
{
    for (auto it = m_plugins.begin(); it != m_plugins.end(); ++it)
    {
        auto& p = *it;

        if (p->id != id)
            continue;

        // notify listeners FIRST
        for (auto& other : m_plugins)
        {
            for (auto* l : other->listeners)
                l->OnPluginUnload(id);
        }

        char err[128]{};
        p->api->Unload(err, sizeof(err));

        p->listeners.clear();

        events::eventManager.RemoveAllForPlugin(id);
        commands::commandsManager.RemoveAllForPlugin(id);

        CloseLib(p->lib);

        m_plugins.erase(it);
        return true;
    }

    return false;
}

bool PluginManager::LoadMissing()
{
    namespace fs = std::filesystem;

    auto dir = paths::GetPluginsDirectory();

    if (!fs::exists(dir))
        return false;

    char error[256];

    int loaded = 0;

    for (const auto& entry : fs::directory_iterator(dir))
    {
        if (!entry.is_regular_file())
            continue;

        auto path = entry.path();

        if (path.extension() != ".stx")
            continue;

        auto fullPath = path.string();

        if (IsPluginLoaded(fullPath))
            continue;

        if (LoadPlugin(path.stem().string().c_str(), error, sizeof(error)))
        {
            loaded++;
        }
    }

    if (loaded > 0)
        SetAllLoaded();

    return true;
}

bool PluginManager::LoadAll()
{
    namespace fs = std::filesystem;

    auto dir = paths::GetPluginsDirectory();

    if (!fs::exists(dir))
        return false;

    char error[256];

    for (const auto& entry : fs::directory_iterator(dir))
    {
        if (!entry.is_regular_file())
            continue;

        auto path = entry.path();

        if (path.extension() != ".stx")
            continue;

        LoadPlugin(path.stem().string().c_str(), error, sizeof(error));
    }

    SetAllLoaded();
    return true;
}

void PluginManager::UnloadAll()
{
    for (auto& p : m_plugins)
    {
        for (auto& other : m_plugins)
        {
            for (auto* l : other->listeners)
                l->OnPluginUnload(p->id);
        }

        char err[128]{};
        p->api->Unload(err, sizeof(err));

        p->listeners.clear();

        events::eventManager.RemoveAllForPlugin(p->id);
        commands::commandsManager.RemoveAllForPlugin(p->id);

        CloseLib(p->lib);
    }

    m_plugins.clear();
}

void PluginManager::SetAllLoaded()
{
    for (auto& p : m_plugins)
    {
        for (auto* l : p->listeners)
            l->OnAllToolkitPluginsLoaded();
    }
}

void PluginManager::FireMetamodLoaded()
{
    for (auto& p : m_plugins)
    {
        for (auto* l : p->listeners)
            l->OnAllMetamodPluginsLoaded();
    }
}

void PluginManager::AddListener(IToolkitPlugin* plugin, IToolkitListener* listener)
{
    for (auto& p : m_plugins)
    {
        if (p->api == plugin)
        {
            p->listeners.push_back(listener);
            return;
        }
    }
}

void PluginManager::OnPluginLoad(SourceMM::PluginId id)
{
    for (auto& p : pluginManager.m_plugins)
    {
        for (auto* l : p->listeners)
            l->OnPluginLoad(id);
    }
}

void PluginManager::OnPluginUnload(SourceMM::PluginId id)
{
    for (auto& p : pluginManager.m_plugins)
    {
        for (auto* l : p->listeners)
            l->OnPluginUnload(id);
    }
}

void PluginManager::OnLevelInit(char const* pMapName, char const* pMapEntities, char const* pOldLevel,
                                char const* pLandmarkName, bool loadGame, bool background)
{
    for (auto& p : pluginManager.m_plugins)
    {
        for (auto* l : p->listeners)
            l->OnLevelInit(pMapName, pMapEntities, pOldLevel, pLandmarkName, loadGame, background);
    }
}

void PluginManager::OnLevelShutdown()
{
    for (auto& p : pluginManager.m_plugins)
    {
        for (auto* l : p->listeners)
            l->OnLevelShutdown();
    }
}