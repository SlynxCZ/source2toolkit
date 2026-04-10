//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once

#include <functional>

#include "source2toolkit/IToolkitScheduler.h"

using TimerCallback = std::function<void()>;

enum TimerFlags {
    TIMER_FLAG_REPEAT = 1 << 0,
    TIMER_FLAG_NO_MAPCHANGE = 1 << 1,
};

extern bool g_bHasTicked;
extern double g_dUniversalTime;
extern double g_dLastTickTime;
extern double g_dTimerNextThink;

class Timer {
public:
    Timer(float interval, double execTime, TimerCallback callback, int flags);
    ~Timer() = default;

    float Interval;
    double ExecTime;
    TimerCallback Callback;
    int Flags;
    bool InExec = false;
    bool KillMe = false;
};

class Scheduler : public IToolkitScheduler
{
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