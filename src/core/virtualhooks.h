//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "ISmmPlugin.h"
#include "igameevents.h"
#include "eiface.h"
#include "entitysystem.h"

#include <dynlibutils/memaddr.h>

namespace virtualhooks {
    enum class Mode : std::uint8_t {
        // Hook callback has been called before original function
        Pre = 0,
        // Hook callback has been called after original function
        Post
    };

    class Virtuals {
    public:
        Virtuals();

        void InitListeners();
        void DestructListeners();
    public:
        KHook::Return<void> Hook_GameFrame(IServerGameDLL* pThis, bool simulating, bool bFirstTick, bool bLastTick);
        KHook::Return<void> Hook_StartupServer(INetworkServerService* pThis, const GameSessionConfiguration_t &config, ISource2WorldSession *pWorldSession, const char *);
        KHook::Return<void> Hook_DispatchConCommand(ICvar* pThis, ConCommandRef cmd, const CCommandContext& ctx, const CCommand& args);
        KHook::Return<void> Hook_ClientCommand(IServerGameClients* pThis, CPlayerSlot slot, const CCommand& args);
        KHook::Return<int> Hook_LoadEventsFromFile(IGameEventManager2* pThis, const char *filename, bool bSearchAll);
        KHook::Return<bool> Hook_FireEvent(IGameEventManager2* pThis, IGameEvent *event, bool bDontBroadcast);
        KHook::Return<bool> Hook_FireEventPost(IGameEventManager2* pThis, IGameEvent *event, bool bDontBroadcast);
    protected:
        KHook::Virtual<IServerGameDLL, void, bool, bool, bool> m_GameFrame;
        KHook::Virtual<INetworkServerService, void, const GameSessionConfiguration_t&, ISource2WorldSession*, const char*> m_StartupServer;
        KHook::Virtual<ICvar, void, ConCommandRef, const CCommandContext&, const CCommand&> m_DispatchConCommand;
        KHook::Virtual<IServerGameClients, void, CPlayerSlot, const CCommand&> m_ClientCommand;
        KHook::Virtual<IGameEventManager2, int, const char*, bool> m_LoadEventsFromFile;
        KHook::Virtual<IGameEventManager2, bool, IGameEvent*, bool> m_FireEventPre;
        KHook::Virtual<IGameEventManager2, bool, IGameEvent*, bool> m_FireEventPost;
    protected:
        IGameEventManager2* m_pCGameEventManagerVTable;
    };

    class CEntityListener: public IEntityListener {
    public:
        void OnEntityCreated(CEntityInstance* pEntity) override;
        void OnEntitySpawned(CEntityInstance* pEntity) override;
        void OnEntityDeleted(CEntityInstance* pEntity) override;
        void OnEntityParentChanged(CEntityInstance* pEntity, CEntityInstance* pNewParent) override;
    };

    extern Virtuals virtuals;
    extern CEntityListener entityListener;
}
