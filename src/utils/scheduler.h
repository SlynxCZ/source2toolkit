//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once

#include <functional>

#include "source2toolkit/IToolkitScheduler.h"

using TimerCallback = std::function<void()>;

extern bool g_bHasTicked;
extern double g_dUniversalTime;
extern double g_dLastTickTime;
extern double g_dTimerNextThink;

class Scheduler : public IToolkitScheduler
{
public:
    void NextFrame(std::function<void()> &&task) override;
    Timer* AddTimer(float interval, TimerCallback callback, int flags = 0) override;
    void KillTimer(Timer* timer) override;
};

extern Scheduler toolkitScheduler;

namespace scheduler {
    void Init();
    void Shutdown();
    void Tick(bool simulating = true);
    void RemoveMapChangeTimers();
}