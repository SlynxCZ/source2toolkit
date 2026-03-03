//
// Created by Michal Přikryl on 03.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "events.h"

#include "shared.h"
#include "utils/log.h"

#include "khook.hpp"

namespace events {
    static std::unordered_map<std::string, std::vector<EventEntry> > gameEvents;
    static EventManager eventManager;

    void InitEvents()
    {
        // Todo: shared API vtable
    }

    void DestructEvents()
    {
        shared::g_pGameEventManager->RemoveListener(&eventManager);
        gameEvents.clear();
    }

    bool DispatchGameEvent(IGameEvent *event, KHook::Mode mode, bool &dontBroadcast) {
        const char *name = event->GetName();
        auto it = gameEvents.find(name);
        if (it == gameEvents.end())
            return true;

        for (const auto &hook: it->second) {
            if (hook.mode != mode)
                continue;

            KHook::Action result = hook.handler(event, mode, dontBroadcast);

            if (result == KHook::Action::Supersede)
                return false;
        }

        return true;
    }

    void RegGameEvent(const std::string &name, GameEventHandler handler, KHook::Mode mode) {
        gameEvents[name].push_back({handler, mode});
        if (!shared::g_pGameEventManager->FindListener(&eventManager, name.c_str()))
        {
            shared::g_pGameEventManager->AddListener(&eventManager, name.c_str(), true);
        }
    }
}
