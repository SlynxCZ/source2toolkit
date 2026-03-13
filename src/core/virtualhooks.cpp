//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "virtualhooks.h"

#include "commands.h"
#include "events.h"
#include "shared.h"
#include "utils/plat.h"
#include "utils/scheduler.h"
#include "dynlibutils/module.h"
#include "iserver.h"
#include "schema/cgameresourceserviceserver.h"
#include "schema/entity/classes/CCSGameRulesProxy.h"

class GameSessionConfiguration_t
{
};

namespace virtualhooks
{
    Virtuals virtuals;
    CEntityListener entityListener;

    static std::vector<IGameEvent*> eventStack;

    Virtuals::Virtuals() :
        m_GameFrame(&IServerGameDLL::GameFrame, this, nullptr, &Virtuals::Hook_GameFrame),
        m_StartupServer(&INetworkServerService::StartupServer, this, nullptr, &Virtuals::Hook_StartupServer),
        m_DispatchConCommand(&ICvar::DispatchConCommand, this, &Virtuals::Hook_DispatchConCommand, nullptr),
        m_ClientCommand(&IServerGameClients::ClientCommand, this, &Virtuals::Hook_ClientCommand, nullptr),
        m_LoadEventsFromFile(&IGameEventManager2::LoadEventsFromFile, this, &Virtuals::Hook_LoadEventsFromFile, nullptr),
        m_FireEventPre(&IGameEventManager2::FireEvent,this, &Virtuals::Hook_FireEvent, nullptr),
        m_FireEventPost(&IGameEventManager2::FireEvent, this, nullptr, &Virtuals::Hook_FireEventPost)
    {
    }

    void Virtuals::InitListeners()
    {
        m_GameFrame.Add(shared::g_pServer);
        m_StartupServer.Add(shared::g_pNetworkServerService);
        m_DispatchConCommand.Add(shared::g_pCVar);
        m_ClientCommand.Add(shared::g_pGameClients);

        m_pCGameEventManagerVTable = DynLibUtils::CModule(shared::g_pServer).GetVirtualTableByName("CGameEventManager").RCast<IGameEventManager2*>();

        m_LoadEventsFromFile.AddGlobal(m_pCGameEventManagerVTable);
        m_FireEventPre.AddGlobal(m_pCGameEventManagerVTable);
        m_FireEventPost.AddGlobal(m_pCGameEventManagerVTable);
    }

    void Virtuals::DestructListeners()
    {
        m_GameFrame.Remove(shared::g_pServer);
        m_StartupServer.Remove(shared::g_pNetworkServerService);
        m_DispatchConCommand.Remove(shared::g_pCVar);
        m_ClientCommand.Remove(shared::g_pGameClients);
        m_LoadEventsFromFile.RemoveGlobal(m_pCGameEventManagerVTable);
        m_FireEventPre.RemoveGlobal(m_pCGameEventManagerVTable);
        m_FireEventPost.RemoveGlobal(m_pCGameEventManagerVTable);
    }

    KHook::Return<void> Virtuals::Hook_GameFrame(IServerGameDLL* pThis, bool simulating, bool bFirstTick, bool bLastTick)
    {
        scheduler::Tick(simulating);

        if (!shared::getGlobalVars())
            return {KHook::Action::Ignore};

        g_bHasTicked = true;
        return {KHook::Action::Ignore};
    }

    KHook::Return<void> Virtuals::Hook_StartupServer(INetworkServerService* pThis, const GameSessionConfiguration_t& config,
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

    KHook::Return<void> Virtuals::Hook_DispatchConCommand(ICvar* pThis, ConCommandRef cmd, const CCommandContext& ctx, const CCommand& args)
    {
        if (args.ArgC() >= 2)
        {
            const char* cmd = args.Arg(0);
            const char* msg = args.Arg(1);

            if (V_strcmp(cmd, "say") == 0 || V_strcmp(cmd, "say_team") == 0)
            {
                std::string message = msg;

                if (message.size() >= 2 && message.front() == '"' && message.back() == '"')
                    message = message.substr(1, message.size() - 2);

                if (!message.empty() && (message[0] == '!' || message[0] == '/'))
                {
                    std::string cleaned = message.substr(1);

                    CCommand parsed;
                    parsed.Tokenize(cleaned.c_str());

                    if (parsed.ArgC() > 0)
                    {
                        KHook::Action r = commands::DispatchConsoleListener(ctx, parsed, virtualhooks::Mode::Pre);
                        if (r != KHook::Action::Supersede)
                            commands::DispatchConsoleListener(ctx, parsed, virtualhooks::Mode::Post);
                    }

                    return {KHook::Action::Supersede};
                }
            }
        }

        KHook::Action result = commands::DispatchConsoleListener(ctx, args, virtualhooks::Mode::Pre);
        if (result > KHook::Action::Ignore)
            return {result};

        commands::DispatchConsoleListener(ctx, args, virtualhooks::Mode::Post);
        return {result};
    }

    KHook::Return<void> Virtuals::Hook_ClientCommand(IServerGameClients* pThis, CPlayerSlot slot, const CCommand& args)
    {
        if (slot != -1 && !V_strncmp(args.Arg(0), "jointeam", 8))
        {
            CCommandContext ctx(CT_NO_TARGET, slot);
            KHook::Action result = commands::DispatchConsoleListener(ctx, args, virtualhooks::Mode::Pre);
            if (result > KHook::Action::Ignore)
                return {result};

            commands::DispatchConsoleListener(ctx, args, virtualhooks::Mode::Post);
        }

        return {KHook::Action::Ignore};
    }

    KHook::Return<int> Virtuals::Hook_LoadEventsFromFile(IGameEventManager2* pThis, const char* filename, bool bSearchAll)
    {
        ExecuteOnce(shared::g_pGameEventManager = pThis);
        events::InitEvents();
        return {KHook::Action::Ignore, 0};
    }

    KHook::Return<bool> Virtuals::Hook_FireEvent(IGameEventManager2* pThis, IGameEvent* event, bool bDontBroadcast)
    {
        if (!event)
            return {KHook::Action::Ignore, false};

        bool localDontBroadcast = bDontBroadcast;
        if (!events::DispatchGameEvent(event, virtualhooks::Mode::Pre, localDontBroadcast))
            return {KHook::Action::Supersede, false};

        if (IGameEvent* copy = shared::g_pGameEventManager->DuplicateEvent(event))
            eventStack.push_back(copy);

        if (localDontBroadcast != bDontBroadcast)
        {
            bool original = m_FireEventPre.CallOriginal(pThis, event, localDontBroadcast);
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
            events::DispatchGameEvent(copy, virtualhooks::Mode::Post, dummy);
            shared::g_pGameEventManager->FreeEvent(copy);
        }

        return {KHook::Action::Ignore, true};
    }

    void Patch_GetHammerUniqueId(CEntityInstance* pEntity)
    {
        static int offset = shared::g_pGameConfig->GetOffset("GetHammerUniqueId");
        void** vtable = *(void***)pEntity;

        // xor al, al -> mov al, 1
        // so it always returns true and allows hammerid to be copied into the schema prop
        Plat_WriteMemory(vtable[offset], (uint8_t*)"\xB0\x01", 2);
    }

    void CEntityListener::OnEntitySpawned(CEntityInstance* pEntity)
    {
    }

    void CEntityListener::OnEntityCreated(CEntityInstance* pEntity)
    {
        ExecuteOnce(Patch_GetHammerUniqueId(pEntity));

        if (!V_strcmp("cs_gamerules", pEntity->GetClassname()))
            shared::g_pGameRules = ((CCSGameRulesProxy*)pEntity)->m_pGameRules;
    }

    void CEntityListener::OnEntityDeleted(CEntityInstance* pEntity)
    {
    }

    void CEntityListener::OnEntityParentChanged(CEntityInstance* pEntity, CEntityInstance* pNewParent)
    {
    }
}
