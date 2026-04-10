//
// Created by Michal Přikryl on 03.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "virtualhooks.h"
#include "events.h"
#include "shared.h"
#include "utils/log.h"

namespace events {
    static std::unordered_map<std::string, std::vector<EventEntry> > gameEvents;
    static EventListener eventListener;

    EventManager eventManager;

    void EventManager::RegGameEvent(const char* pchName, GameEventHandler handler, Mode mode) {
        gameEvents[pchName].push_back({handler, mode});
        if (!shared::g_pGameEventManager->FindListener(&eventListener, pchName))
        {
            shared::g_pGameEventManager->AddListener(&eventListener, pchName, true);
        }
    }

    void EventListener::FireGameEvent(IGameEvent* pEvent) {}

    void InitEvents()
    {
        // Todo: shared API vtable
    }

    void DestructEvents()
    {
        if (shared::g_pGameEventManager)
            shared::g_pGameEventManager->RemoveListener(&eventListener);
        gameEvents.clear();
    }

    bool DispatchGameEvent(IGameEvent *event, Mode mode, bool &dontBroadcast) {
        const char *name = event->GetName();
        auto it = gameEvents.find(name);
        if (it == gameEvents.end())
            return true;

        for (const auto &hook: it->second) {
            if (hook.mode != mode)
                continue;

            Action result = hook.handler(event, mode, dontBroadcast);

            if (result == Action::Supersede)
                return false;
        }

        return true;
    }
}
