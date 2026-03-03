//
// Created by Michal Přikryl on 03.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "igameevents.h"

#include "KHook.hpp"
#include <functional>

class IGameEvent;

namespace events {
    using GameEventHandler = std::function<KHook::Action(IGameEvent* event, KHook::Mode mode, bool& dontBroadcast)>;

    struct EventEntry
    {
        GameEventHandler handler;
        KHook::Mode mode;
    };

    class EventManager : public IGameEventListener2
    {
        void FireGameEvent(IGameEvent* pEvent) override;
    };

    void InitEvents();
    void DestructEvents();

    bool DispatchGameEvent(IGameEvent *event, KHook::Mode mode, bool &dontBroadcast);

    void RegGameEvent(const std::string &name, GameEventHandler handler, KHook::Mode mode);
}
