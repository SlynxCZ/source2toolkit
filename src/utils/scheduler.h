//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once

#include <functional>

using TimerCallback = std::function<void()>;

enum TimerFlags {
    TIMER_FLAG_REPEAT = 1 << 0,
    TIMER_FLAG_NO_MAPCHANGE = 1 << 1,
};

extern bool has_ticked;
extern double universal_time;
extern double last_tick_time;
extern double timer_next_think;

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

namespace scheduler {
    void Init();
    void Shutdown();
    void Tick(bool simulating = true);
    void NextFrame(std::function<void()> &&task);
    Timer* AddTimer(float interval, TimerCallback callback, int flags = 0);
    void KillTimer(Timer* timer);
    void RemoveMapChangeTimers();
}