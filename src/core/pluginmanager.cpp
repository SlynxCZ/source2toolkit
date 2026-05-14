/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
 * AlliedModders LLC. All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl and
 * AlliedModders LLC give you permission to link the code of this program
 * (as well as its derivative works) to "Counter-Strike 2," "Source 2,"
 * "Steam," and any Game MODs or server software running on software by
 * Valve Corporation. You must obey the GNU General Public License in all
 * respects for all other code used.
 *
 * Additionally, this exception applies to all derivative works unless
 * otherwise stated in LICENSE.txt.
 *
 * Authors:
 *   - Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl
 *   - AlliedModders LLC
 *
 * Project: Source2Toolkit
 */
#include "pluginmanager.h"
#include <cstring>

#include "commands.h"
#include "events.h"
#include "entityio.h"

#include "source2toolkit/IToolkitApi.h"
#include "source2toolkit/IToolkitPlugin.h"

#include "pluginapi.h"
#include "core/shared.h"
#include "utils/log.h"
#include "utils/paths.h"
#include "utils/scheduler.h"

#ifndef _WIN32
#include <sys/inotify.h>
#include <sys/select.h>
#include <unistd.h>
#endif

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

bool PluginManager::LoadPluginFromPath(const char* fullPath, char* error, size_t maxlen, bool hotReload)
{
    std::string dlErr;
    auto lib = OpenLib(fullPath, dlErr);

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
        FAILF("CreateInterface not found in %s", fullPath);
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
    if (!plugin->Load(stored->id, &pluginApi, err, sizeof(err), hotReload))
    {
        FAILF("Plugin load failed: %s", err);
    }

    auto newId = m_plugins.back()->id;

    for (auto& p : m_plugins)
    {
        for (auto* l : p->listeners)
            l->OnPluginLoad(newId);
    }

    FP_INFO("{} plugin {}", hotReload ? "Hot reloaded" : "Loaded", std::filesystem::path(fullPath).stem().string());
    return true;
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

    return LoadPluginFromPath(fullPath.c_str(), error, maxlen, false);
}

bool PluginManager::ReloadPlugin(int id)
{
    std::string path;

    for (auto it = m_plugins.begin(); it != m_plugins.end(); ++it)
    {
        if ((*it)->id != id)
            continue;

        path = (*it)->path;

        for (auto& other : m_plugins)
            for (auto* l : other->listeners)
                l->OnPluginUnload(id);

        char err[128]{};
        (*it)->api->Unload(err, sizeof(err));
        (*it)->listeners.clear();

        events::eventManager.RemoveAllForPlugin(id);
        commands::commandsManager.RemoveAllForPlugin(id);

        CloseLib((*it)->lib);
        m_plugins.erase(it);
        break;
    }

    if (path.empty())
        return false;

    char err[256]{};
    return LoadPluginFromPath(path.c_str(), err, sizeof(err), true);
}

bool PluginManager::ReloadPluginByPath(const std::string& fullPath)
{
    auto normalized = std::filesystem::weakly_canonical(fullPath).string();

    for (auto& p : m_plugins)
    {
        if (std::filesystem::weakly_canonical(p->path).string() == normalized)
            return ReloadPlugin(p->id);
    }

    return false;
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

    if (!shared::g_pCoreConfig->PluginAutoLoadEnabled)
        return true;

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

void PluginManager::StartFileWatcher()
{
#ifndef _WIN32
    if (!shared::g_pCoreConfig->PluginHotReloadEnabled)
        return;

    m_stopWatcher = false;
    auto dir = paths::GetPluginsDirectory();

    m_watcherThread = std::thread([this, dir]()
    {
        int fd = inotify_init1(IN_NONBLOCK);
        if (fd < 0)
        {
            FP_ERROR("inotify_init1 failed, hot reload unavailable");
            return;
        }

        inotify_add_watch(fd, dir.c_str(), IN_CLOSE_WRITE);

        alignas(struct inotify_event) char buf[4096];

        while (!m_stopWatcher)
        {
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(fd, &fds);

            timeval tv{0, 100000};
            if (select(fd + 1, &fds, nullptr, nullptr, &tv) <= 0)
                continue;

            int len = read(fd, buf, sizeof(buf));
            if (len <= 0)
                continue;

            for (int i = 0; i < len; )
            {
                auto* ev = reinterpret_cast<struct inotify_event*>(buf + i);

                if (ev->len > 0 && (ev->mask & IN_CLOSE_WRITE))
                {
                    std::string name = ev->name;
                    if (name.size() > 4 && name.substr(name.size() - 4) == ".stx")
                    {
                        std::string fullPath = dir + "/" + name;
                        FP_INFO("Detected change in {}, queuing hot reload...", name);
                        toolkitScheduler.NextFrame([this, fullPath]()
                        {
                            ReloadPluginByPath(fullPath);
                        });
                    }
                }

                i += static_cast<int>(sizeof(struct inotify_event)) + ev->len;
            }
        }

        close(fd);
    });
#endif
}

void PluginManager::StopFileWatcher()
{
#ifndef _WIN32
    m_stopWatcher = true;
    if (m_watcherThread.joinable())
        m_watcherThread.join();
#endif
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