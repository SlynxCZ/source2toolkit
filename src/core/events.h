//
// Created by Michal Přikryl on 03.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "virtualhooks.h"

#include "igameevents.h"
#include <functional>

class IGameEvent;

namespace events {
    using GameEventHandler = std::function<KHook::Action(IGameEvent* event, virtualhooks::Mode mode, bool& dontBroadcast)>;

    struct EventEntry
    {
        GameEventHandler handler;
        virtualhooks::Mode mode;
    };

    class EventManager : public IGameEventListener2
    {
        void FireGameEvent(IGameEvent* pEvent) override;
    };

    void InitEvents();
    void DestructEvents();

    bool DispatchGameEvent(IGameEvent *event, virtualhooks::Mode mode, bool &dontBroadcast);

    void RegGameEvent(const std::string &name, GameEventHandler handler, virtualhooks::Mode mode);
}
