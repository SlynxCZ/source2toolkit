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

#ifndef _INCLUDE_METAMOD_SOURCE_STUB_PLUGIN_H_
#define _INCLUDE_METAMOD_SOURCE_STUB_PLUGIN_H_

#include "ISmmPlugin.h"

// Redirects SH_GLOB_SHPTR/SH_GLOB_PLUGPTR onto the toolkit's own private
// SourceHook engine instead of metamod's shared g_SHPtr/g_PLID -- must come
// after ISmmPlugin.h (which defines the defaults this overrides) and before
// any SH_DECL_HOOK*/SH_ADD_*HOOK usage. Plugins join this same engine via
// sourcehook_metamod_shared.h; see TOOLKIT_SOURCEHOOK_INTERFACE.
#include "sourcehook/sourcehook_metamod_override.h"

class ToolkitCore : public ISmmPlugin, public IMetamodListener
{
public:
    bool Load(PluginId id, ISmmAPI *ismm, char *error, size_t maxlen, bool late) override;
    bool Unload(char *error, size_t maxlen) override;
    void AllPluginsLoaded() override;
public:
    void OnPluginLoad(PluginId id) override;
    void OnPluginUnload(PluginId id) override;
    void OnLevelInit(char const* pMapName, char const* pMapEntities, char const* pOldLevel, char const* pLandmarkName, bool loadGame, bool background) override;
    void OnLevelShutdown() override;
public:
    const char *GetAuthor() override;
    const char *GetName() override;
    const char *GetDescription() override;
    const char *GetURL() override;
    const char *GetLicense() override;
    const char *GetVersion() override;
    const char *GetDate() override;
    const char *GetLogTag() override;
};

extern ToolkitCore g_ToolkitCore;

#endif //_INCLUDE_METAMOD_SOURCE_STUB_PLUGIN_H_

PLUGIN_GLOBALVARS();
