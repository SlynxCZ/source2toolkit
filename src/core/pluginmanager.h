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
#pragma once

#include <ISmmPluginExt.h>
#include <vector>
#include <string>
#include <memory>

#ifdef _WIN32
#include <Windows.h>
using LibHandle = HMODULE;
#else
#include <dlfcn.h>
using LibHandle = void*;
#endif

class IToolkitPlugin;
class IToolkitListener;

struct ToolkitPlugin
{
    int id;
    std::string path;
    LibHandle lib;
    IToolkitPlugin* api;
    std::vector<IToolkitListener*> listeners;
};

class PluginManager
{
public:
    bool IsPluginLoaded(const std::string& fullPath);

    bool LoadPlugin(const char* path, char* error, size_t maxlen);
    bool UnloadPlugin(int id);

    bool LoadMissing();

    bool LoadAll();
    void UnloadAll();

    void SetAllLoaded();
    void FireMetamodLoaded();

    void AddListener(IToolkitPlugin* plugin, IToolkitListener* listener);
public:
    void OnPluginLoad(SourceMM::PluginId id);
    void OnPluginUnload(SourceMM::PluginId id);
    void OnLevelInit(char const* pMapName, char const* pMapEntities, char const* pOldLevel, char const* pLandmarkName, bool loadGame, bool background);
    void OnLevelShutdown();
public:
    std::vector<std::unique_ptr<ToolkitPlugin>> m_plugins;
    int m_nextId = 1;
};

extern PluginManager pluginManager;