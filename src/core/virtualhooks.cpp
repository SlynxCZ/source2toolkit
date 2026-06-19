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
#include "events.h"
#include "shared.h"
#include "source2toolkit/schema/schema.h"
#include "source2toolkit/utils/plat.h"
#include "core/scheduler.h"
#include "dynlibutils/module.h"
#include "steam/isteamgameserver.h"
#include "iserver.h"
#include "mysql.h"
#include "schema/cgameresourceserviceserver.h"

namespace virtualhooks
{
    Virtuals virtuals;
    CEntityListener entityListener;

    static std::vector<IGameEvent*> eventStack;

    Virtuals::Virtuals() :
        m_pGameFrame(new KHook::Virtual(&IServerGameDLL::GameFrame, this, nullptr, &Virtuals::Hook_GameFrame)),
        m_pDispatchConCommand(new KHook::Virtual(&ICvar::DispatchConCommand, this, &Virtuals::Hook_DispatchConCommand,
                                                 nullptr)),
        m_pClientCommand(new KHook::Virtual(&IServerGameClients::ClientCommand, this, &Virtuals::Hook_ClientCommand,
                                            nullptr)),
        m_pStartupServer(new KHook::Virtual(&INetworkServerService::StartupServer, this, nullptr,
                                            &Virtuals::Hook_StartupServer)),
        m_pOnServerGamePostSimulate(new KHook::Virtual(&IGameSystem::OnServerGamePostSimulate, this, nullptr,
                                                       &Virtuals::Hook_OnServerGamePostSimulate)),
        m_pLoadEventsFromFile(new KHook::Virtual(&IGameEventManager2::LoadEventsFromFile, this, nullptr,
                                                 &Virtuals::Hook_LoadEventsFromFile)),
        m_pFireEvent(new KHook::Virtual(&IGameEventManager2::FireEvent, this, &Virtuals::Hook_FireEvent,
                                        &Virtuals::Hook_FireEventPost))
    {
    }

    void Virtuals::InitListeners()
    {
        DynLibUtils::CModule libserver(shared::g_pServer);

        m_pGameFrame->Add(shared::g_pServer);
        m_pStartupServer->Add(shared::g_pNetworkServerService);
        m_pDispatchConCommand->Add(shared::g_pCVar);
        m_pClientCommand->Add(shared::g_pGameClients);

        m_pCEntityDebugGameSystemVTable = libserver.GetVirtualTableByName("CEntityDebugGameSystem").RCast<IGameSystem
            *>();
        if (m_pCEntityDebugGameSystemVTable)
        {
            m_pOnServerGamePostSimulate->AddGlobal((IGameSystem*)&m_pCEntityDebugGameSystemVTable);
        }

        m_pCGameEventManagerVTable = libserver.GetVirtualTableByName("CGameEventManager").RCast<IGameEventManager2*>();
        if (m_pCGameEventManagerVTable)
        {
            m_pLoadEventsFromFile->AddGlobal((IGameEventManager2*)&m_pCGameEventManagerVTable);
            m_pFireEvent->AddGlobal((IGameEventManager2*)&m_pCGameEventManagerVTable);
        }
    }

    void Virtuals::DestructListeners()
    {
        m_pGameFrame->Remove(shared::g_pServer);
        m_pStartupServer->Remove(shared::g_pNetworkServerService);
        m_pDispatchConCommand->Remove(shared::g_pCVar);
        m_pClientCommand->Remove(shared::g_pGameClients);

        if (m_pCEntityDebugGameSystemVTable)
        {
            m_pOnServerGamePostSimulate->RemoveGlobal((IGameSystem*)&m_pCEntityDebugGameSystemVTable);
        }

        if (m_pCGameEventManagerVTable)
        {
            m_pLoadEventsFromFile->RemoveGlobal((IGameEventManager2*)&m_pCGameEventManagerVTable);
            m_pFireEvent->RemoveGlobal((IGameEventManager2*)&m_pCGameEventManagerVTable);
        }

        delete m_pGameFrame;
        delete m_pStartupServer;
        delete m_pDispatchConCommand;
        delete m_pClientCommand;
        delete m_pOnServerGamePostSimulate;
        delete m_pLoadEventsFromFile;
        delete m_pFireEvent;
    }

    KHook::Return<void> Virtuals::Hook_GameFrame(IServerGameDLL* pThis, bool simulating, bool bFirstTick,
                                                 bool bLastTick)
    {
        scheduler::Tick(simulating);

        if (!shared::getGlobalVars())
            return {KHook::Action::Ignore};

        if (shared::g_pEntitySystem)
        {
            for (int i = 0; i < shared::getGlobalVars()->maxClients; i++)
            {
                auto steamId = shared::g_pEngine->GetClientSteamID(CPlayerSlot(i));
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
                                                shared::g_pGameClients->GetPlayerScore(CPlayerSlot(i)));
                        }
                    }
                }
            }
        }

        g_bHasTicked = true;
        return {KHook::Action::Ignore};
    }

    KHook::Return<void> Virtuals::Hook_StartupServer(INetworkServerService* pThis,
                                                     const GameSessionConfiguration_t& config,
                                                     ISource2WorldSession* pWorldSession, const char*)
    {
        if (!shared::g_bDetoursLoaded)
        {
            shared::g_pEntitySystem = shared::g_pGameResourceServiceServer->GetGameEntitySystem();
            shared::g_pEntitySystem->AddListenerEntity(&entityListener);
            shared::g_bDetoursLoaded = true;
        }
        if (g_bHasTicked)
        {
            scheduler::RemoveMapChangeTimers();
        }
        g_bHasTicked = false;
        return {KHook::Action::Ignore};
    }

    KHook::Return<void> Virtuals::Hook_DispatchConCommand(ICvar* pThis, ConCommandRef cmd, const CCommandContext& ctx,
                                                          const CCommand& args)
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
                        Action r = commands::DispatchConsoleListener(ctx, parsed, Mode::Pre);

                        if (r != Action::Supersede)
                            commands::DispatchConsoleListener(ctx, parsed, Mode::Post);

                        if (r == Action::Supersede)
                            return {KHook::Action::Supersede};
                    }

                    if (isSilent)
                        return {KHook::Action::Supersede};

                    return {KHook::Action::Ignore};
                }
            }
        }

        Action result = commands::DispatchConsoleListener(ctx, args, Mode::Pre);

        if (result > Action::Ignore)
            return {static_cast<KHook::Action>(result)};

        commands::DispatchConsoleListener(ctx, args, Mode::Post);

        return {static_cast<KHook::Action>(result)};
    }

    KHook::Return<void> Virtuals::Hook_ClientCommand(IServerGameClients* pThis, CPlayerSlot slot, const CCommand& args)
    {
        if (slot != -1 && !V_strncmp(args.Arg(0), "jointeam", 8))
        {
            CCommandContext ctx(CT_NO_TARGET, slot);
            Action result = commands::DispatchConsoleListener(ctx, args, Mode::Pre);
            if (result > Action::Ignore)
                return {static_cast<KHook::Action>(result)};

            commands::DispatchConsoleListener(ctx, args, Mode::Post);
        }

        return {KHook::Action::Ignore};
    }

    KHook::Return<void> Virtuals::Hook_OnServerGamePostSimulate(IGameSystem* pThis,
                                                                const EventServerGamePostSimulate_t* const pMsg)
    {
        for (auto connection : mysql::mysqlManager.m_vecMysqlConnections)
        {
            connection->RunFrame();
        }
        return {KHook::Action::Ignore};
    }

    KHook::Return<int> Virtuals::Hook_LoadEventsFromFile(IGameEventManager2* pThis, const char* filename,
                                                         bool bSearchAll)
    {
        ExecuteOnce(
            shared::g_pGameEventManager = pThis;
            events::InitEvents();
        )

        return {KHook::Action::Ignore, 0};
    }

    KHook::Return<bool> Virtuals::Hook_FireEvent(IGameEventManager2* pThis, IGameEvent* event, bool bDontBroadcast)
    {
        if (!event)
            return {KHook::Action::Ignore, false};

        bool localDontBroadcast = bDontBroadcast;
        if (!events::DispatchGameEvent(event, Mode::Pre, localDontBroadcast))
            return {KHook::Action::Supersede, false};

        if (IGameEvent* copy = shared::g_pGameEventManager->DuplicateEvent(event))
            eventStack.push_back(copy);

        if (localDontBroadcast != bDontBroadcast)
        {
            bool original = m_pFireEvent->CallOriginal(pThis, event, localDontBroadcast);
            return {KHook::Action::Supersede, original};
        }

        return {KHook::Action::Ignore, true};
    }

    KHook::Return<bool> Virtuals::Hook_FireEventPost(IGameEventManager2* pThis, IGameEvent* event, bool bDontBroadcast)
    {
        if (!event)
            return {KHook::Action::Ignore, false};

        if (!eventStack.empty())
        {
            IGameEvent* copy = eventStack.back();
            eventStack.pop_back();

            bool dummy = bDontBroadcast;
            events::DispatchGameEvent(copy, Mode::Post, dummy);
            shared::g_pGameEventManager->FreeEvent(copy);
        }

        return {KHook::Action::Ignore, true};
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
    }

    void CEntityListener::OnEntityParentChanged(CEntityInstance* pEntity, CEntityInstance* pNewParent)
    {
    }
}
