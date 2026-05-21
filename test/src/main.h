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
#ifndef SOURCE2TOOLKIT_TEST_LIBRARY_H
#define SOURCE2TOOLKIT_TEST_LIBRARY_H

#pragma once

#include "source2toolkit/IToolkitPlugin.h"

#include "eiface.h"
#include "khook.hpp"

class CBasePlayerWeapon;
class CCSPlayer_WeaponServices;
class CNETMsg_StringCmd_t;
class CServerSideClientBase;

class Plugin final : public IToolkitPlugin, IToolkitListener
{
public:
    Plugin();

    bool Load(PluginId id, IToolkitAPI* api, char* error, size_t maxlen, bool late) override;
    bool Unload(char* error, size_t maxlen) override;

public:
    void OnPluginLoad(PluginId id) override;
    void OnPluginUnload(PluginId id) override;
    void OnAllToolkitPluginsLoaded() override;
    void OnAllMetamodPluginsLoaded() override;
    void OnLevelInit(const char* mapName, const char* mapEntities, const char* oldLevel, const char* landmarkName, bool loadGame, bool background) override;
    void OnLevelShutdown() override;

public:
    KHook::Return<void> CCSPlayer_WeaponServices_SelectItem(CCSPlayer_WeaponServices* pThis, CBasePlayerWeapon* pWeapon, int unk1);
    KHook::Return<bool> CServerSideClient_ExecuteStringCommand(CServerSideClientBase* pThis, const CNETMsg_StringCmd_t& msg);

protected:
    KHook::Virtual<CCSPlayer_WeaponServices, void, CBasePlayerWeapon*, int>* m_pSelectItem = nullptr;
    KHook::Virtual<CServerSideClientBase, bool, const CNETMsg_StringCmd_t&>* m_pExecuteStringCommand = nullptr;

    CCSPlayer_WeaponServices* m_pCCSPlayer_WeaponServicesVTable = nullptr;
    CServerSideClientBase* m_pCServerSideClientBaseVTable = nullptr;

private:
    const char* GetAuthor() override;
    const char* GetName() override;
    const char* GetDescription() override;
    const char* GetVersion() override;
};

extern Plugin g_Plugin;

#endif //SOURCE2TOOLKIT_TEST_LIBRARY_H