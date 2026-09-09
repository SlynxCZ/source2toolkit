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
#include "crashhandler.h"
#include "customhud.h"
#include "http.h"
#include "events.h"
#include "networkmessages.h"
#include "plugin.h"
#include "shared.h"
#include "source2toolkit/schema/schema.h"
#include "source2toolkit/utils/plat.h"
#include "core/scheduler.h"
#include "core/menus.h"
#include "core/entities.h"
#include "dynlibutils/module.hpp"
#include "steam/isteamgameserver.h"
#include "iserver.h"
#include "engine/igameeventsystem.h"
#include "mysql.h"

namespace virtualhooks
{
    Virtuals virtuals;
    CEntityListener entityListener;

    static std::vector<IGameEvent*> eventStack;

    Virtuals::Virtuals() :
        KHOOK_NEW(m_hGameFrame, &ISource2Server::GameFrame, this, nullptr, &Virtuals::Hook_GameFrame),
        KHOOK_NEW(m_hStartupServer, &INetworkServerService::StartupServer, this, nullptr, &Virtuals::Hook_StartupServer),
        KHOOK_NEW(m_hDispatchConCommand, &ICvar::DispatchConCommand, this, &Virtuals::Hook_DispatchConCommand, nullptr),
        KHOOK_NEW(m_hClientCommand, &ISource2GameClients::ClientCommand, this, &Virtuals::Hook_ClientCommand, nullptr),
        KHOOK_NEW(m_hClientSvcUserMessage, &ISource2GameClients::ClientSvcUserMessage, this, &Virtuals::Hook_ClientSvcUserMessage, nullptr),
        // Steam only hands its HTTP client over once the API is up, and this
        // is where that happens -- see http::HTTPManager.
        KHOOK_NEW(m_hSteamAPIActivated, &ISource2Server::GameServerSteamAPIActivated, this, nullptr, &Virtuals::Hook_GameServerSteamAPIActivated),
        KHOOK_NEW(m_hSteamAPIDeactivated, &ISource2Server::GameServerSteamAPIDeactivated, this, &Virtuals::Hook_GameServerSteamAPIDeactivated, nullptr),
        // PostEventAbstract is overloaded, so the member function pointer has
        // to be disambiguated explicitly.
        KHOOK_NEW(m_hPostEventAbstract, static_cast<void (IGameEventSystem::*)(CSplitScreenSlot, bool, int, const uint64*, INetworkMessageInternal*, const CNetMessage*, unsigned long, NetChannelBufType_t)>(&IGameEventSystem::PostEventAbstract), this, &Virtuals::Hook_PostEventAbstract, nullptr),
        KHOOK_NEW(m_hOnServerGamePostSimulate, &IGameSystem::OnServerGamePostSimulate, this, nullptr, &Virtuals::Hook_OnServerGamePostSimulate),
        KHOOK_NEW(m_hLoadEventsFromFile, &IGameEventManager2::LoadEventsFromFile, this, nullptr, &Virtuals::Hook_LoadEventsFromFile),
        KHOOK_NEW(m_hFireEvent, &IGameEventManager2::FireEvent, this, &Virtuals::Hook_FireEvent, &Virtuals::Hook_FireEventPost),
        KHOOK_NEW(m_hSendNetMessage, &CServerSideClientBase::SendNetMessage, this, &Virtuals::Hook_SendNetMessage, nullptr)
    {
    }

    void Virtuals::InitListeners()
    {
        DynLibUtils::CModule libserver(g_pSource2Server);
        DynLibUtils::CModule libengine(g_pEngineServer);

        m_hGameFrame->Add(g_pSource2Server);
        m_hStartupServer->Add(g_pNetworkServerService);
        m_hDispatchConCommand->Add(g_pCVar);
        m_hClientCommand->Add(g_pSource2GameClients);
        m_hClientSvcUserMessage->Add(g_pSource2GameClients);
        m_hSteamAPIActivated->Add(g_pSource2Server);
        m_hSteamAPIDeactivated->Add(g_pSource2Server);
        m_hPostEventAbstract->Add(shared::g_pGameEventSystem);

        m_pCEntityDebugGameSystemVTable = libserver.GetVirtualTableByName("CEntityDebugGameSystem").GetPtr();
        if (m_pCEntityDebugGameSystemVTable)
            m_hOnServerGamePostSimulate->AddGlobal(reinterpret_cast<IGameSystem*>(&m_pCEntityDebugGameSystemVTable));

        m_pCGameEventManagerVTable = libserver.GetVirtualTableByName("CGameEventManager").GetPtr();
        if (m_pCGameEventManagerVTable)
        {
            m_hLoadEventsFromFile->AddGlobal(reinterpret_cast<IGameEventManager2*>(&m_pCGameEventManagerVTable));
            m_hFireEvent->AddGlobal(reinterpret_cast<IGameEventManager2*>(&m_pCGameEventManagerVTable));
        }

        // Hooked on the vtable rather than per client, so the recipient comes
        // from the hooked instance itself -- that is what the per-client
        // net-message dispatch needs and PostEventAbstract cannot give.
        m_pCServerSideClientVTable = libengine.GetVirtualTableByName("CServerSideClient").GetPtr();
        if (m_pCServerSideClientVTable)
            m_hSendNetMessage->AddGlobal(reinterpret_cast<CServerSideClientBase*>(&m_pCServerSideClientVTable));
    }

    void Virtuals::DestructListeners()
    {
        m_hGameFrame->Remove(g_pSource2Server);
        m_hStartupServer->Remove(g_pNetworkServerService);
        m_hDispatchConCommand->Remove(g_pCVar);
        m_hClientCommand->Remove(g_pSource2GameClients);
        m_hClientSvcUserMessage->Remove(g_pSource2GameClients);
        m_hSteamAPIActivated->Remove(g_pSource2Server);
        m_hSteamAPIDeactivated->Remove(g_pSource2Server);
        m_hPostEventAbstract->Remove(shared::g_pGameEventSystem);

        if (m_pCEntityDebugGameSystemVTable)
            m_hOnServerGamePostSimulate->RemoveGlobal(reinterpret_cast<IGameSystem*>(&m_pCEntityDebugGameSystemVTable));

        if (m_pCGameEventManagerVTable)
        {
            m_hLoadEventsFromFile->RemoveGlobal(reinterpret_cast<IGameEventManager2*>(&m_pCGameEventManagerVTable));
            m_hFireEvent->RemoveGlobal(reinterpret_cast<IGameEventManager2*>(&m_pCGameEventManagerVTable));
        }

        if (m_pCServerSideClientVTable)
            m_hSendNetMessage->RemoveGlobal(reinterpret_cast<CServerSideClientBase*>(&m_pCServerSideClientVTable));

        delete m_hGameFrame;
        delete m_hStartupServer;
        delete m_hDispatchConCommand;
        delete m_hClientCommand;
        delete m_hClientSvcUserMessage;
        delete m_hSteamAPIActivated;
        delete m_hSteamAPIDeactivated;
        delete m_hPostEventAbstract;
        delete m_hOnServerGamePostSimulate;
        delete m_hLoadEventsFromFile;
        delete m_hFireEvent;
        delete m_hSendNetMessage;

        m_hGameFrame = nullptr;
        m_hStartupServer = nullptr;
        m_hDispatchConCommand = nullptr;
        m_hClientCommand = nullptr;
        m_hClientSvcUserMessage = nullptr;
        m_hSteamAPIActivated = nullptr;
        m_hSteamAPIDeactivated = nullptr;
        m_hPostEventAbstract = nullptr;
        m_hOnServerGamePostSimulate = nullptr;
        m_hLoadEventsFromFile = nullptr;
        m_hFireEvent = nullptr;
        m_hSendNetMessage = nullptr;

        m_pCEntityDebugGameSystemVTable = nullptr;
        m_pCGameEventManagerVTable = nullptr;
        m_pCServerSideClientVTable = nullptr;
    }

    KHook::Return<void> Virtuals::Hook_GameFrame(ISource2Server* pThis, bool simulating, bool bFirstTick, bool bLastTick)
    {
        // First, and before the early return below: a signal handler someone
        // replaced has to go back regardless of whether the world is up.
        crashhandler::OnGameFrame();

        scheduler::Tick(simulating);

        // Center HTML menus fade, so the open ones have to be redrawn every
        // frame. MenuManager::Tick() existed but nothing called it, which left
        // a menu on screen for a moment and then gone.
        menus::menuManager.Tick();

        if (!shared::getGlobalVars())
            return { KHook::Action::Ignore };

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

        return { KHook::Action::Ignore };
    }

    KHook::Return<void> Virtuals::Hook_StartupServer(INetworkServerService* pThis, const GameSessionConfiguration_t& config, ISource2WorldSession* pWorldSession, const char* pszMapName)
    {
        crashhandler::OnStartupServer(pszMapName);

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

        return { KHook::Action::Ignore };
    }

    KHook::Return<void> Virtuals::Hook_DispatchConCommand(ICvar* pThis, ConCommandRef cmd, const CCommandContext& ctx, const CCommand& args)
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
                        Action r = commands::DispatchConsoleListener(ctx, parsed, false);

                        if (r != Action::Supersede)
                            commands::DispatchConsoleListener(ctx, parsed, true);

                        if (r == Action::Supersede)
                            return { KHook::Action::Supersede };
                    }

                    if (isSilent)
                        return { KHook::Action::Supersede };

                    return { KHook::Action::Ignore };
                }
            }
        }

        Action result = commands::DispatchConsoleListener(ctx, args, false);

        if (result > Action::Ignore)
            return { result };

        commands::DispatchConsoleListener(ctx, args, true);

        return { result };
    }

    KHook::Return<void> Virtuals::Hook_ClientCommand(ISource2GameClients* pThis, CPlayerSlot slot, const CCommand& args)
    {
        if (slot != -1 && !V_strncmp(args.Arg(0), "jointeam", 8))
        {
            CCommandContext ctx(CT_NO_TARGET, slot);
            Action result = commands::DispatchConsoleListener(ctx, args, false);
            if (result > Action::Ignore)
                return { result };

            commands::DispatchConsoleListener(ctx, args, true);
        }

        return { KHook::Action::Ignore };
    }

    KHook::Return<void> Virtuals::Hook_ClientSvcUserMessage(ISource2GameClients* pThis, CPlayerSlot slot, int nType, uint32 nSize, const void* pBuffer)
    {
        if (nType != customhud::CS_UM_CustomHudClicked)
            return { KHook::Action::Ignore };

        if (auto* pController = CCSPlayerController::FromSlot(slot))
            customhud::customHudManager.HandleClick(pController, pBuffer, nSize);

        return { KHook::Action::Ignore };
    }

    KHook::Return<void> Virtuals::Hook_GameServerSteamAPIActivated(ISource2Server* pThis)
    {
        http::httpManager.OnSteamAPIActivated();
        // After the HTTP manager: the crash report waiting for Steam goes out
        // through it.
        crashhandler::OnSteamAPIActivated();

        return { KHook::Action::Ignore };
    }

    KHook::Return<void> Virtuals::Hook_GameServerSteamAPIDeactivated(ISource2Server* pThis)
    {
        http::httpManager.OnSteamAPIDeactivated();

        return { KHook::Action::Ignore };
    }

    KHook::Return<void> Virtuals::Hook_PostEventAbstract(IGameEventSystem* pThis, CSplitScreenSlot nSlot, bool bLocalOnly, int nClientCount, const uint64* clients, INetworkMessageInternal* pEvent, const CNetMessage* pData, unsigned long nSize, NetChannelBufType_t bufType)
    {
        if (!pEvent || !pData)
            return { KHook::Action::Ignore };

        NetMessageInfo_t* pInfo = pEvent->GetNetMessageInfo();
        if (!pInfo)
            return { KHook::Action::Ignore };

        Action result = networkmessages::DispatchServerHook(const_cast<uint64_t*>(reinterpret_cast<const uint64_t*>(clients)), pInfo->m_MessageId, const_cast<CNetMessage*>(pData));

        return { result };
    }

    KHook::Return<void> Virtuals::Hook_OnServerGamePostSimulate(IGameSystem* pThis, const EventServerGamePostSimulate_t* const pMsg)
    {
        mysql::mysqlManager.RunFrame();
        return { KHook::Action::Ignore };
    }

    KHook::Return<int> Virtuals::Hook_LoadEventsFromFile(IGameEventManager2* pThis, const char* filename, bool bSearchAll)
    {
        ExecuteOnce(
            shared::g_pGameEventManager = pThis;
            events::InitEvents();
        )

        return { KHook::Action::Ignore, 0 };
    }

    KHook::Return<bool> Virtuals::Hook_FireEvent(IGameEventManager2* pThis, IGameEvent* event, bool bDontBroadcast)
    {
        if (!event)
            return { KHook::Action::Ignore, false };

        bool localDontBroadcast = bDontBroadcast;
        if (!events::DispatchGameEvent(event, false, localDontBroadcast))
            return { KHook::Action::Supersede, false };

        if (IGameEvent* copy = shared::g_pGameEventManager->DuplicateEvent(event))
            eventStack.push_back(copy);

        if (localDontBroadcast != bDontBroadcast)
        {
            // A listener changed the broadcast flag: run the original with the
            // new one ourselves and drop the hooked call so it does not fire twice.
            bool original = m_hFireEvent->CallOriginal(pThis, event, localDontBroadcast);
            return { KHook::Action::Supersede, original };
        }

        return { KHook::Action::Ignore, true };
    }

    KHook::Return<bool> Virtuals::Hook_FireEventPost(IGameEventManager2* pThis, IGameEvent* event, bool bDontBroadcast)
    {
        if (!event)
            return { KHook::Action::Ignore, false };

        if (!eventStack.empty())
        {
            IGameEvent* copy = eventStack.back();
            eventStack.pop_back();

            bool dummy = bDontBroadcast;
            events::DispatchGameEvent(copy, true, dummy);
            shared::g_pGameEventManager->FreeEvent(copy);
        }

        return { KHook::Action::Ignore, true };
    }

    KHook::Return<bool> Virtuals::Hook_SendNetMessage(CServerSideClientBase* pThis, const CNetMessage* pData, NetChannelBufType_t bufType)
    {
        if (!pThis || !pData)
            return { KHook::Action::Ignore, true };

        INetworkMessageInternal* pNetMsg = pData->GetNetMessage();
        if (!pNetMsg)
            return { KHook::Action::Ignore, true };

        NetMessageInfo_t* pInfo = pNetMsg->GetNetMessageInfo();
        if (!pInfo)
            return { KHook::Action::Ignore, true };

        Action result = networkmessages::DispatchServerInternalHook(pThis->GetPlayerSlot(), pInfo->m_MessageId, const_cast<CNetMessage*>(pData));

        return { result, true };
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
