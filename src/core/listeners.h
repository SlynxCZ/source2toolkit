//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "eiface.h"
#include "entitysystem.h"

namespace listeners {
    void InitListeners();

    void DestructListeners();

    class SourceHooks {
    public:
        void Hook_GameFrame(bool simulating, bool bFirstTick, bool bLastTick);
        void Hook_StartupServer(const GameSessionConfiguration_t& config, ISource2WorldSession*, const char*);
        int Hook_LoadEventsFromFile(const char* filename, bool bSearchAll);
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
