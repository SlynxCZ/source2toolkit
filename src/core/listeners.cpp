//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "listeners.h"

#include "commands.h"
#include "events.h"
#include "shared.h"
#include "utils/scheduler.h"
#include "dynlibutils/module.h"
#include "iserver.h"
#include "schema/cgameresourceserviceserver.h"

#include "KHook.hpp"

class GameSessionConfiguration_t
{
};

namespace listeners {
    SourceHooks sourceHooks;
    CEntityListener entityListener;

    SH_DECL_HOOK3_void(IServerGameDLL, GameFrame, SH_NOATTRIB, 0, bool, bool, bool);
    SH_DECL_HOOK3_void(INetworkServerService, StartupServer, SH_NOATTRIB, 0, const GameSessionConfiguration_t&, ISource2WorldSession*, const char*);
    SH_DECL_HOOK3_void(ICvar, DispatchConCommand, SH_NOATTRIB, 0, ConCommandRef, const CCommandContext&, const CCommand&);
    SH_DECL_HOOK2(IGameEventManager2, LoadEventsFromFile, SH_NOATTRIB, 0, int, const char*, bool);
    SH_DECL_HOOK2(IGameEventManager2, FireEvent, SH_NOATTRIB, 0, bool, IGameEvent*, bool);

    int g_iLoadEventsFromFileId = -1;
    int g_iFireEvent = -1;
    int g_iFireEventPost = -1;

    static std::vector<IGameEvent *> eventStack;

    void InitListeners() {
        SH_ADD_HOOK(IServerGameDLL, GameFrame, shared::g_pServer, SH_MEMBER(&sourceHooks,&SourceHooks::Hook_GameFrame), false);
        SH_ADD_HOOK(INetworkServerService, StartupServer, shared::g_pNetworkServerService, SH_MEMBER(&sourceHooks, &SourceHooks::Hook_StartupServer), true);
        auto pCGameEventManagerVTable = DynLibUtils::CModule(shared::g_pServer).GetVirtualTableByName("CGameEventManager").RCast<IGameEventManager2*>();
        g_iLoadEventsFromFileId = SH_ADD_DVPHOOK(IGameEventManager2, LoadEventsFromFile, pCGameEventManagerVTable, SH_MEMBER(&sourceHooks, &SourceHooks::Hook_LoadEventsFromFile), false);
        g_iFireEvent = SH_ADD_DVPHOOK(IGameEventManager2, FireEvent, pCGameEventManagerVTable, SH_MEMBER(&sourceHooks, &SourceHooks::Hook_FireEvent), false);
        g_iFireEventPost = SH_ADD_DVPHOOK(IGameEventManager2, FireEvent, pCGameEventManagerVTable, SH_MEMBER(&sourceHooks, &SourceHooks::Hook_FireEventPost), true);
    }

    void DestructListeners() {
        SH_REMOVE_HOOK(IServerGameDLL, GameFrame, shared::g_pServer, SH_MEMBER(&sourceHooks,&SourceHooks::Hook_GameFrame), false);
        SH_REMOVE_HOOK(INetworkServerService, StartupServer, shared::g_pNetworkServerService, SH_MEMBER(&sourceHooks, &SourceHooks::Hook_StartupServer), true);
        SH_REMOVE_HOOK_ID(g_iLoadEventsFromFileId);
        SH_REMOVE_HOOK_ID(g_iFireEvent);
        SH_REMOVE_HOOK_ID(g_iFireEventPost);
    }

    void SourceHooks::Hook_GameFrame(bool simulating, bool, bool)
    {
        scheduler::Tick(simulating);

        if (!shared::getGlobalVars())
            return;

        has_ticked = true;
    }

    void SourceHooks::Hook_StartupServer(const GameSessionConfiguration_t&, ISource2WorldSession*, const char*)
    {
        if (!shared::g_bDetoursLoaded)
        {
            shared::g_pEntitySystem = shared::g_pGameResourceServiceServer->GetGameEntitySystem();
            shared::g_pEntitySystem->AddListenerEntity(&entityListener);
            shared::g_bDetoursLoaded = true;
        }
        if (has_ticked)
        {
            scheduler::RemoveMapChangeTimers();
        }
        has_ticked = false;
    }

    void SourceHooks::Hook_DispatchConCommand(ConCommandRef cmd, const CCommandContext &ctx, const CCommand &args) {
        if (args.ArgC() >= 2) {
            const char *cmd = args.Arg(0);
            const char *msg = args.Arg(1);

            if (V_strcmp(cmd, "say") == 0 || V_strcmp(cmd, "say_team") == 0) {
                std::string message = msg;

                if (message.size() >= 2 && message.front() == '"' && message.back() == '"')
                    message = message.substr(1, message.size() - 2);

                if (!message.empty() && (message[0] == '!' || message[0] == '/')) {
                    std::string cleaned = message.substr(1);

                    CCommand parsed;
                    parsed.Tokenize(cleaned.c_str());

                    if (parsed.ArgC() > 0) {
                        KHook::Action r = commands::DispatchConsoleListener(ctx, parsed, KHook::Mode::Pre);
                        if (r != KHook::Action::Supersede)
                            commands::DispatchConsoleListener(ctx, parsed, KHook::Mode::Post);
                    }

                    RETURN_META(MRES_SUPERCEDE);
                }
            }
        }

        KHook::Action result = commands::DispatchConsoleListener(ctx, args, KHook::Mode::Pre);

        if (result == KHook::Action::Supersede)
            RETURN_META(MRES_SUPERCEDE);

        if (result == KHook::Action::Override)
            RETURN_META(MRES_OVERRIDE);

        commands::DispatchConsoleListener(ctx, args, KHook::Mode::Post);
    }

    int SourceHooks::Hook_LoadEventsFromFile(const char*, bool)
    {
        ExecuteOnce(shared::g_pGameEventManager = META_IFACEPTR(IGameEventManager2));
        events::InitEvents();
        RETURN_META_VALUE(MRES_IGNORED, 0);
    }

    bool SourceHooks::Hook_FireEvent(IGameEvent* event, bool bDontBroadcast)
    {
        if (!event)
            RETURN_META_VALUE(MRES_IGNORED, false);

        bool localDontBroadcast = bDontBroadcast;
        if (!events::DispatchGameEvent(event, KHook::Mode::Pre, localDontBroadcast))
            RETURN_META_VALUE(MRES_SUPERCEDE, false);

        if (IGameEvent *copy = shared::g_pGameEventManager->DuplicateEvent(event))
            eventStack.push_back(copy);

        if (localDontBroadcast != bDontBroadcast)
            RETURN_META_VALUE_NEWPARAMS(MRES_IGNORED, true, &IGameEventManager2::FireEvent,
                                    (event, localDontBroadcast));

        RETURN_META_VALUE(MRES_IGNORED, true);
    }

    bool SourceHooks::Hook_FireEventPost(IGameEvent* event, bool bDontBroadcast)
    {
        if (!event)
            RETURN_META_VALUE(MRES_IGNORED, false);

        if (!eventStack.empty()) {
            IGameEvent *copy = eventStack.back();
            eventStack.pop_back();

            bool dummy = bDontBroadcast;
            events::DispatchGameEvent(copy, KHook::Mode::Post, dummy);
            shared::g_pGameEventManager->FreeEvent(copy);
        }

        RETURN_META_VALUE(MRES_IGNORED, true);
    }

    void CEntityListener::OnEntityCreated(CEntityInstance* pEntity) {}
    void CEntityListener::OnEntitySpawned(CEntityInstance* pEntity) {}
    void CEntityListener::OnEntityDeleted(CEntityInstance* pEntity) {}
    void CEntityListener::OnEntityParentChanged(CEntityInstance* pEntity, CEntityInstance* pNewParent) {}
}
