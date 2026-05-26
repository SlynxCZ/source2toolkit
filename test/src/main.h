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

#include "sdk/isteamgamecoordinator.h"

#include "eiface.h"
#include "khook.hpp"

#include <google/protobuf/message.h>
#include <steammessages.pb.h>
#include <cstrike15_gcmessages.pb.h>
#include <string>
#include <vector>
#include <utility>
#include <optional>

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
    void OnLevelInit(const char* mapName, const char* mapEntities, const char* oldLevel, const char* landmarkName,
                     bool loadGame, bool background) override;
    void OnLevelShutdown() override;

public:
    std::optional<std::pair<uint32_t, std::string>> CreateGCSendProto(uint32_t type, google::protobuf::Message& msg,
                                                                      CMsgProtoBufHeader* pHeader = nullptr);
    void QueueGCMessage(uint32_t type, google::protobuf::Message& msg, CMsgProtoBufHeader* pHeader = nullptr);
    void TriggerGCCallback();

public:
    KHook::Return<void> CSource2Server_GameServerSteamAPIActivated(ISource2Server* pThis);
    KHook::Return<EGCResults> ISteamGameCoordinator_SendMessage(ISteamGameCoordinator* pThis, uint32_t unMsgType, const void* pubData, uint32_t cubData);
    KHook::Return<bool> ISteamGameCoordinator_IsMessageAvailable(ISteamGameCoordinator* pThis, uint32_t* pcubMsgSize);
    KHook::Return<EGCResults> ISteamGameCoordinator_RetrieveMessage(ISteamGameCoordinator* pThis, uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize);
    KHook::Return<void> ISteamGameServer_RunCallbacks();
    KHook::Return<void> ISteamGameServer_RegisterCallback(CCallbackBase* pCallback, int iCallback);
    KHook::Return<void> ISteamGameServer_UnregisterCallback(CCallbackBase* pCallback);

protected:
    KHook::Virtual<ISource2Server, void>* m_pGameServerSteamAPIActivated = nullptr;
    KHook::Virtual<ISteamGameCoordinator, EGCResults, uint32, const void*, uint32>* m_pSendMessage = nullptr;
    KHook::Virtual<ISteamGameCoordinator, bool, uint32*>* m_pIsMessageAvailable = nullptr;
    KHook::Virtual<ISteamGameCoordinator, EGCResults, uint32*, void*, uint32, uint32*>* m_pRetrieveMessage = nullptr;
    KHook::Function<void>* m_pRunCallbacks = nullptr;
    KHook::Function<void, CCallbackBase*, int>* m_pRegisterCallback = nullptr;
    KHook::Function<void, CCallbackBase*>* m_pUnregisterCallback = nullptr;

private:
    const char* GetAuthor() override;
    const char* GetName() override;
    const char* GetDescription() override;
    const char* GetVersion() override;
};

extern Plugin g_Plugin;

#endif //SOURCE2TOOLKIT_TEST_LIBRARY_H
