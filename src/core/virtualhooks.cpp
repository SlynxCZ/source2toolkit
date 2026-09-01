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
#include "virtualhooks.h"

#include "source2toolkit/schema/entity/classes/CBaseEntity.h"
#include "source2toolkit/schema/entity/classes/CCSGameRulesProxy.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController.h"

#include "commands.h"
#include "source2toolkit/schema/entity/classes/CCSCustomHudLayout.h"
#include "customhud.h"
#include "http.h"
#include "events.h"
#include "networkmessages.h"
#include "plugin.h"
#include "shared.h"
#include "source2toolkit/schema/schema.h"
#include "source2toolkit/schema/serversideclient.h"
#include "source2toolkit/utils/plat.h"
#include "core/scheduler.h"
#include "core/menus.h"
#include "core/entities.h"
#include "dynlibutils/module.hpp"
#include "steam/isteamgameserver.h"
#include "iserver.h"
#include "engine/igameeventsystem.h"
#include "mysql.h"

SH_DECL_HOOK3_void(IServerGameDLL, GameFrame, SH_NOATTRIB, 0, bool, bool, bool);
SH_DECL_HOOK3_void(INetworkServerService, StartupServer, SH_NOATTRIB, 0, const GameSessionConfiguration_t&, ISource2WorldSession*, const char*);
SH_DECL_HOOK3_void(ICvar, DispatchConCommand, SH_NOATTRIB, 0, ConCommandRef, const CCommandContext&, const CCommand&);
SH_DECL_HOOK2_void(IServerGameClients, ClientCommand, SH_NOATTRIB, 0, CPlayerSlot, const CCommand&);
SH_DECL_HOOK4_void(IServerGameClients, ClientSvcUserMessage, SH_NOATTRIB, 0, CPlayerSlot, int, uint32, const void*);
SH_DECL_HOOK0_void(ISource2Server, GameServerSteamAPIActivated, SH_NOATTRIB, 0);
SH_DECL_HOOK0_void(ISource2Server, GameServerSteamAPIDeactivated, SH_NOATTRIB, 0);
SH_DECL_HOOK8_void(IGameEventSystem, PostEventAbstract, SH_NOATTRIB, 0, CSplitScreenSlot, bool, int, const uint64*, INetworkMessageInternal*, const CNetMessage*, unsigned long, NetChannelBufType_t);
SH_DECL_HOOK1_void(IGameSystem, OnServerGamePostSimulate, SH_NOATTRIB, 0, const EventServerGamePostSimulate_t*);
SH_DECL_HOOK2(IGameEventManager2, LoadEventsFromFile, SH_NOATTRIB, 0, int, const char*, bool);
SH_DECL_HOOK2(IGameEventManager2, FireEvent, SH_NOATTRIB, 0, bool, IGameEvent*, bool);
SH_DECL_HOOK2(CServerSideClient, SendNetMessage, SH_NOATTRIB, 0, bool, const CNetMessage*, NetChannelBufType_t);

namespace virtualhooks
{
    Virtuals virtuals;
    CEntityListener entityListener;

    static std::vector<IGameEvent*> eventStack;

    void Virtuals::InitListeners()
    {
        DynLibUtils::CModule libserver(g_pSource2Server);
        DynLibUtils::CModule libengine(g_pEngineServer);

        m_iGameFrameHookID = SH_ADD_HOOK(IServerGameDLL, GameFrame, g_pSource2Server, SH_MEMBER(this, &Virtuals::Hook_GameFrame), true);
        m_iStartupServerHookID = SH_ADD_HOOK(INetworkServerService, StartupServer, g_pNetworkServerService, SH_MEMBER(this, &Virtuals::Hook_StartupServer), true);
        m_iDispatchConCommandHookID = SH_ADD_HOOK(ICvar, DispatchConCommand, g_pCVar, SH_MEMBER(this, &Virtuals::Hook_DispatchConCommand), false);
        m_iClientCommandHookID = SH_ADD_HOOK(IServerGameClients, ClientCommand, g_pSource2GameClients, SH_MEMBER(this, &Virtuals::Hook_ClientCommand), false);
        m_iClientSvcUserMessageHookID = SH_ADD_HOOK(IServerGameClients, ClientSvcUserMessage, g_pSource2GameClients, SH_MEMBER(this, &Virtuals::Hook_ClientSvcUserMessage), false);
        // Steam only hands its HTTP client over once the API is up, and this
        // is where that happens -- see http::HTTPManager.
        m_iSteamAPIActivatedHookID = SH_ADD_HOOK(ISource2Server, GameServerSteamAPIActivated, g_pSource2Server, SH_MEMBER(this, &Virtuals::Hook_GameServerSteamAPIActivated), true);
        m_iSteamAPIDeactivatedHookID = SH_ADD_HOOK(ISource2Server, GameServerSteamAPIDeactivated, g_pSource2Server, SH_MEMBER(this, &Virtuals::Hook_GameServerSteamAPIDeactivated), false);
        m_iPostEventAbstractHookID = SH_ADD_HOOK(IGameEventSystem, PostEventAbstract, shared::g_pGameEventSystem, SH_MEMBER(this, &Virtuals::Hook_PostEventAbstract), false);

        if (DynLibUtils::CMemory vtable = libserver.GetVirtualTableByName("CEntityDebugGameSystem"); vtable.IsValid())
        {
            m_iOnServerGamePostSimulateHookID = SH_ADD_DVPHOOK(IGameSystem, OnServerGamePostSimulate, vtable.RCast<IGameSystem*>(), SH_MEMBER(this, &Virtuals::Hook_OnServerGamePostSimulate), true);
        }

        if (DynLibUtils::CMemory vtable = libserver.GetVirtualTableByName("CGameEventManager"); vtable.IsValid())
        {
            m_iLoadEventsFromFileHookID = SH_ADD_DVPHOOK(IGameEventManager2, LoadEventsFromFile, vtable.RCast<IGameEventManager2*>(), SH_MEMBER(this, &Virtuals::Hook_LoadEventsFromFile), true);
            m_iFireEventHookID = SH_ADD_DVPHOOK(IGameEventManager2, FireEvent, vtable.RCast<IGameEventManager2*>(), SH_MEMBER(this, &Virtuals::Hook_FireEvent), false);
            m_iFireEventPostHookID = SH_ADD_DVPHOOK(IGameEventManager2, FireEvent, vtable.RCast<IGameEventManager2*>(), SH_MEMBER(this, &Virtuals::Hook_FireEventPost), true);
        }

        if (DynLibUtils::CMemory vtable = libengine.GetVirtualTableByName("CServerSideClient"); vtable.IsValid())
        {
            m_iSendNetMessageHookID = SH_ADD_DVPHOOK(CServerSideClient, SendNetMessage, vtable.RCast<CServerSideClient*>(), SH_MEMBER(this, &Virtuals::Hook_SendNetMessage), false);
        }
    }

    void Virtuals::DestructListeners()
    {
        SH_REMOVE_HOOK_ID(m_iGameFrameHookID);
        SH_REMOVE_HOOK_ID(m_iStartupServerHookID);
        SH_REMOVE_HOOK_ID(m_iDispatchConCommandHookID);
        SH_REMOVE_HOOK_ID(m_iClientCommandHookID);
        SH_REMOVE_HOOK_ID(m_iClientSvcUserMessageHookID);
        SH_REMOVE_HOOK_ID(m_iSteamAPIActivatedHookID);
        SH_REMOVE_HOOK_ID(m_iSteamAPIDeactivatedHookID);
        SH_REMOVE_HOOK_ID(m_iPostEventAbstractHookID);
        SH_REMOVE_HOOK_ID(m_iOnServerGamePostSimulateHookID);
        SH_REMOVE_HOOK_ID(m_iLoadEventsFromFileHookID);
        SH_REMOVE_HOOK_ID(m_iFireEventHookID);
        SH_REMOVE_HOOK_ID(m_iFireEventPostHookID);
        SH_REMOVE_HOOK_ID(m_iSendNetMessageHookID);
    }

    void Virtuals::Hook_GameFrame(bool simulating, bool bFirstTick, bool bLastTick)
    {
        scheduler::Tick(simulating);

        // Center HTML menus fade, so the open ones have to be redrawn every
        // frame. MenuManager::Tick() existed but nothing called it, which left
        // a menu on screen for a moment and then gone.
        menus::menuManager.Tick();

        if (!shared::getGlobalVars())
            RETURN_META(MRES_IGNORED);

        if (shared::g_pEntitySystem)
        {
            for (int i = 0; i < shared::getGlobalVars()->maxClients; i++)
            {
                auto steamId = g_pEngineServer->GetClientSteamID(CPlayerSlot(i));
                if (steamId)
                {
                    auto controller = static_cast<CCSPlayerController*>(shared::g_pEntitySystem->GetEntityInstance(
                        CEntityIndex(i + 1)));
                    if (controller)
                    {
                        ISteamGameServer* gs = SteamGameServer();
                        if (gs && gs->BLoggedOn())
                        {
                            gs->BUpdateUserData(*steamId, controller->GetPlayerName(),
                                                g_pSource2GameClients->GetPlayerScore(CPlayerSlot(i)));
                        }
                    }
                }
            }
        }

        g_bHasTicked = true;

        RETURN_META(MRES_IGNORED);
    }

    void Virtuals::Hook_StartupServer(const GameSessionConfiguration_t& config, ISource2WorldSession* pWorldSession, const char* pszMapName)
    {
        // Re-read every time rather than once: the engine can hand out a new
        // entity system for the next map, and CS2Fixes refreshes it on every
        // StartupServer for the same reason. Keeping the first one would mean
        // a stale pointer and listeners attached to a system nothing uses.
        auto* pEntitySystem = *DynLibUtils::CMemory(g_pGameResourceServiceServer)
                                   .Offset(shared::g_pGameConfig->GetOffset("GameEntitySystem"))
                                   .RCast<CGameEntitySystem**>();

        if (pEntitySystem && pEntitySystem != shared::g_pEntitySystem)
        {
            shared::g_pEntitySystem = pEntitySystem;
            pEntitySystem->AddListenerEntity(&entityListener);

            // Plugins register their listeners while they load, which is
            // before the first entity system exists at all.
            entities::entitiesManager.AttachEntityListeners();

            shared::g_bDetoursLoaded = true;
        }

        if (g_bHasTicked)
        {
            scheduler::RemoveMapChangeTimers();
        }

        g_bHasTicked = false;

        RETURN_META(MRES_IGNORED);
    }

    void Virtuals::Hook_DispatchConCommand(ConCommandRef cmd, const CCommandContext& ctx, const CCommand& args)
    {
        if (args.ArgC() >= 2)
        {
            const char* cmdName = args.Arg(0);
            const char* msg = args.Arg(1);

            if (V_strcmp(cmdName, "say") == 0 || V_strcmp(cmdName, "say_team") == 0)
            {
                std::string message = msg;

                if (message.size() >= 2 && message.front() == '"' && message.back() == '"')
                    message = message.substr(1, message.size() - 2);

                std::string prefix;

                bool isPublic =
                    shared::g_pCoreConfig->IsPublicChatTrigger(message, prefix);

                bool isSilent =
                    shared::g_pCoreConfig->IsSilentChatTrigger(message, prefix);

                if (isPublic || isSilent)
                {
                    std::string cleaned = message.substr(prefix.size());

                    CCommand parsed;
                    parsed.Tokenize(cleaned.c_str());

                    if (parsed.ArgC() > 0)
                    {
                        META_RES r = commands::DispatchConsoleListener(ctx, parsed, false);

                        if (r != MRES_SUPERCEDE)
                            commands::DispatchConsoleListener(ctx, parsed, true);

                        if (r == MRES_SUPERCEDE)
                            RETURN_META(MRES_SUPERCEDE);
                    }

                    if (isSilent)
                        RETURN_META(MRES_SUPERCEDE);

                    RETURN_META(MRES_IGNORED);
                }
            }
        }

        META_RES result = commands::DispatchConsoleListener(ctx, args, false);

        if (result > MRES_IGNORED)
            RETURN_META(result);

        commands::DispatchConsoleListener(ctx, args, true);

        RETURN_META(result);
    }

    void Virtuals::Hook_ClientCommand(CPlayerSlot slot, const CCommand& args)
    {
        if (slot != -1 && !V_strncmp(args.Arg(0), "jointeam", 8))
        {
            CCommandContext ctx(CT_NO_TARGET, slot);
            META_RES result = commands::DispatchConsoleListener(ctx, args, false);
            if (result > MRES_IGNORED)
                RETURN_META(result);

            commands::DispatchConsoleListener(ctx, args, true);
        }

        RETURN_META(MRES_IGNORED);
    }

    void Virtuals::Hook_ClientSvcUserMessage(CPlayerSlot slot, int nType, uint32 nSize, const void* pBuffer)
    {
        if (nType != customhud::CS_UM_CustomHudClicked)
            RETURN_META(MRES_IGNORED);

        if (auto* pController = CCSPlayerController::FromSlot(slot))
            customhud::customHudManager.HandleClick(pController, pBuffer, nSize);

        RETURN_META(MRES_IGNORED);
    }

    void Virtuals::Hook_GameServerSteamAPIActivated()
    {
        http::httpManager.OnSteamAPIActivated();

        RETURN_META(MRES_IGNORED);
    }

    void Virtuals::Hook_GameServerSteamAPIDeactivated()
    {
        http::httpManager.OnSteamAPIDeactivated();

        RETURN_META(MRES_IGNORED);
    }

    void Virtuals::Hook_PostEventAbstract(CSplitScreenSlot nSlot, bool bLocalOnly, int nClientCount, const uint64* clients, INetworkMessageInternal* pEvent, const CNetMessage* pData, unsigned long nSize,NetChannelBufType_t bufType)
    {
        if (!pEvent || !pData)
            RETURN_META(MRES_IGNORED);

        NetMessageInfo_t* pInfo = pEvent->GetNetMessageInfo();
        if (!pInfo)
            RETURN_META(MRES_IGNORED);

        META_RES result = networkmessages::DispatchServerHook(const_cast<uint64_t*>(reinterpret_cast<const uint64_t*>(clients)), pInfo->m_MessageId, const_cast<CNetMessage*>(pData));

        RETURN_META(result);
    }

    void Virtuals::Hook_OnServerGamePostSimulate(const EventServerGamePostSimulate_t* const pMsg)
    {
        for (auto connection : mysql::mysqlManager.m_vecMysqlConnections)
        {
            connection->RunFrame();
        }
        RETURN_META(MRES_IGNORED);
    }

    int Virtuals::Hook_LoadEventsFromFile(const char* filename, bool bSearchAll)
    {
        ExecuteOnce(
            shared::g_pGameEventManager = META_IFACEPTR(IGameEventManager2);
            events::InitEvents();
        )

        RETURN_META_VALUE(MRES_IGNORED, 0);
    }

    bool Virtuals::Hook_FireEvent(IGameEvent* event, bool bDontBroadcast)
    {
        if (!event)
            RETURN_META_VALUE(MRES_IGNORED, false);

        bool localDontBroadcast = bDontBroadcast;
        if (!events::DispatchGameEvent(event, false, localDontBroadcast))
            RETURN_META_VALUE(MRES_SUPERCEDE, false);

        if (IGameEvent* copy = shared::g_pGameEventManager->DuplicateEvent(event))
            eventStack.push_back(copy);

        if (localDontBroadcast != bDontBroadcast)
        {
            bool original = SH_CALL(META_IFACEPTR(IGameEventManager2), &IGameEventManager2::FireEvent)(event, localDontBroadcast);
            RETURN_META_VALUE(MRES_SUPERCEDE, original);
        }

        RETURN_META_VALUE(MRES_IGNORED, true);
    }

    bool Virtuals::Hook_FireEventPost(IGameEvent* event, bool bDontBroadcast)
    {
        if (!event)
            RETURN_META_VALUE(MRES_IGNORED, false);

        if (!eventStack.empty())
        {
            IGameEvent* copy = eventStack.back();
            eventStack.pop_back();

            bool dummy = bDontBroadcast;
            events::DispatchGameEvent(copy, true, dummy);
            shared::g_pGameEventManager->FreeEvent(copy);
        }

        RETURN_META_VALUE(MRES_IGNORED, true);
    }

    bool Virtuals::Hook_SendNetMessage(const CNetMessage* pData, NetChannelBufType_t bufType)
    {
        CServerSideClient* pClient = META_IFACEPTR(CServerSideClient);
        if (!pClient || !pData)
            RETURN_META_VALUE(MRES_IGNORED, true);

        INetworkMessageInternal* pNetMsg = pData->GetNetMessage();
        if (!pNetMsg)
            RETURN_META_VALUE(MRES_IGNORED, true);

        NetMessageInfo_t* pInfo = pNetMsg->GetNetMessageInfo();
        if (!pInfo)
            RETURN_META_VALUE(MRES_IGNORED, true);

        META_RES result = networkmessages::DispatchServerInternalHook(pClient->GetPlayerSlot(), pInfo->m_MessageId, const_cast<CNetMessage*>(pData));

        RETURN_META_VALUE(result, true);
    }

    void CEntityListener::OnEntitySpawned(CEntityInstance* pEntity)
    {
    }

    void CEntityListener::OnEntityCreated(CEntityInstance* pEntity)
    {
        if (!V_strcmp("cs_gamerules", pEntity->GetClassname()))
            shared::g_pGameRules = static_cast<CCSGameRulesProxy*>(pEntity)->m_pGameRules;
    }

    void CEntityListener::OnEntityDeleted(CEntityInstance* pEntity)
    {
        // Drop a layout's click callbacks the moment the entity goes, rather
        // than waiting for the next click to notice the handle went stale --
        // the handlers hold plugin code and there may never be another click.
        if (!V_strcmp("custom_hud_layout", pEntity->GetClassname()))
            customhud::customHudManager.UnhookCustomHudClick(static_cast<CCSCustomHudLayout*>(pEntity));
    }

    void CEntityListener::OnEntityParentChanged(CEntityInstance* pEntity, CEntityInstance* pNewParent)
    {
    }
}
