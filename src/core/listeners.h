//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "igameevents.h"
#include "eiface.h"
#include "entitysystem.h"

namespace listeners {
    void InitListeners();
    void DestructListeners();

    class SourceHooks {
    public:
        void Hook_GameFrame(bool simulating, bool, bool);
        void Hook_StartupServer(const GameSessionConfiguration_t&, ISource2WorldSession*, const char*);
        void Hook_DispatchConCommand(ConCommandRef cmd, const CCommandContext& ctx, const CCommand& args);
        int Hook_LoadEventsFromFile(const char*, bool);
        bool Hook_FireEvent(IGameEvent *event, bool bDontBroadcast);
        bool Hook_FireEventPost(IGameEvent *event, bool bDontBroadcast);
    };

    class CEntityListener: public IEntityListener {
    public:
        void OnEntityCreated(CEntityInstance* pEntity) override;
        void OnEntitySpawned(CEntityInstance* pEntity) override;
        void OnEntityDeleted(CEntityInstance* pEntity) override;
        void OnEntityParentChanged(CEntityInstance* pEntity, CEntityInstance* pNewParent) override;
    };

    extern SourceHooks sourceHooks;
    extern CEntityListener entityListener;
}
