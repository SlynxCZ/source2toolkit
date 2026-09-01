/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
 * AlliedModders LLC. All rights reserved.
 * =============================================================================
 *
 * Project: Source2Toolkit
 */
#include "core/paths.h"
#include "core/pluginmanager.h"

#include "utils/paths.h"

namespace paths
{
    PathsManager pathsManager;

    namespace
    {
        // Built on first use: the game directory is not known until the engine
        // is up, so none of these can be initialised statically.
        const char* Cached(std::string& slot, std::string (*build)())
        {
            if (slot.empty())
                slot = build();

            return slot.c_str();
        }
    }

    const char* PathsManager::GameDirectory()     { return Cached(m_sGame,     &paths::GameDirectory); }
    const char* PathsManager::RootDirectory()     { return Cached(m_sRoot,     &paths::GetRootDirectory); }
    const char* PathsManager::ConfigsDirectory()  { return Cached(m_sConfigs,  &paths::GetConfigsDirectory); }
    const char* PathsManager::GamedataDirectory() { return Cached(m_sGamedata, &paths::GetGamedataDirectory); }
    const char* PathsManager::PluginsDirectory()  { return Cached(m_sPlugins,  &paths::GetPluginsDirectory); }
    const char* PathsManager::SharedDirectory()   { return Cached(m_sShared,   &paths::GetSharedDirectory); }

    const char* PathsManager::PluginConfigDirectory(PluginId owner)
    {
        if (auto it = m_PluginConfigs.find(owner); it != m_PluginConfigs.end())
            return it->second.c_str();

        for (auto& plugin : pluginManager.m_plugins)
        {
            if (!plugin || plugin->id != owner || !plugin->api)
                continue;

            const char* pszName = plugin->api->GetName();
            if (!pszName || !*pszName)
                return nullptr;

            auto [iter, _] = m_PluginConfigs.emplace(owner, GetPluginConfigDirectory(pszName));
            return iter->second.c_str();
        }

        return nullptr;
    }
}
