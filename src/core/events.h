//
// Created by Michal Přikryl on 03.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "virtualhooks.h"
#include "shared.h"

#include "source2toolkit/IToolkitEvents.h"
#include "source2toolkit/IToolkitTypes.h"

#include "igameevents.h"
#include <functional>

#include "source2toolkit/IToolkitPlugin.h"

class IGameEvent;

namespace events {
    struct EventEntry
    {
        PluginId owner;
        GameEventHandler handler;
        Mode mode;
    };

    class EventListener : public IGameEventListener2
    {
        void FireGameEvent(IGameEvent* pEvent) override;
    };

    class EventManager : public IToolkitEvents
    {
    public:
        void RegGameEvent(PluginId owner, const char* pchName, GameEventHandler handler, Mode mode) override;
    public:
        void RemoveAllForPlugin(PluginId id);
    };

    extern EventManager eventManager;

    void InitEvents();
    void DestructEvents();

    bool DispatchGameEvent(IGameEvent *event, Mode mode, bool &dontBroadcast);
}
