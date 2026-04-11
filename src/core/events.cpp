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

    static void RegisterListenerIfNeeded(const std::string& name)
    {
        if (!shared::g_pGameEventManager)
            return;

        if (!shared::g_pGameEventManager->FindListener(&eventListener, name.c_str()))
        {
            shared::g_pGameEventManager->AddListener(&eventListener, name.c_str(), true);
        }
    }

    void EventManager::RegGameEvent(PluginId owner, const char* name, GameEventHandler handler, Mode mode)
    {
        gameEvents[name].push_back({owner, handler, mode});
        RegisterListenerIfNeeded(name);
    }

    void EventManager::RemoveAllForPlugin(PluginId id)
    {
        for (auto it = gameEvents.begin(); it != gameEvents.end(); )
        {
            auto& vec = it->second;

            std::erase_if(vec, [id](const EventEntry& e) {
                return e.owner == id;
            });

            if (vec.empty())
                it = gameEvents.erase(it);
            else
                ++it;
        }
    }

    void EventListener::FireGameEvent(IGameEvent* pEvent) {}

    void InitEvents()
    {
        if (!shared::g_pGameEventManager)
            return;

        for (const auto& [name, _] : gameEvents)
        {
            RegisterListenerIfNeeded(name);
        }
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
