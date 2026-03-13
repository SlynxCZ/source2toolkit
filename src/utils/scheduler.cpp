//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "scheduler.h"
#include <algorithm>
#include <chrono>
#include <mutex>
#include <queue>

bool g_bHasTicked = false;
double g_dUniversalTime = 0.0;
double g_dLastTickTime = 0.0;
double g_dTimerNextThink = 0.0;

namespace {
    std::vector<Timer *> once_off_timers;
    std::vector<Timer *> repeat_timers;
    std::mutex nextFrameMutex;
    std::queue<std::function<void()> > nextFrameQueue;
}
void scheduler::NextFrame(std::function<void()> &&task) {
    std::lock_guard lock(nextFrameMutex);
    nextFrameQueue.emplace(std::move(task));
}

Timer::Timer(float interval, double execTime, TimerCallback callback, int flags)
    : Interval(interval), ExecTime(execTime), Callback(std::move(callback)), Flags(flags) {
}

void scheduler::Init() {
    g_dUniversalTime = 0.0;
    g_dLastTickTime = 0.0;
    g_dTimerNextThink = 0.0;
}

void scheduler::Shutdown() {
    for (auto *timer: once_off_timers)
        delete timer;
    for (auto *timer: repeat_timers)
        delete timer;
    once_off_timers.clear();
    repeat_timers.clear();
    std::lock_guard lock(nextFrameMutex);
    std::queue<std::function<void()> > empty;
    std::swap(nextFrameQueue, empty);
}

void scheduler::Tick(bool simulating) {
    std::queue<std::function<void()>> localQueue;
    {
        std::lock_guard lock(nextFrameMutex);
        std::swap(localQueue, nextFrameQueue);
    }

    while (!localQueue.empty()) {
        try {
            localQueue.front()();
        } catch (...) {
        }
        localQueue.pop();
    }

    double now = std::chrono::duration_cast<std::chrono::duration<float> >(
        std::chrono::steady_clock::now().time_since_epoch()).count();

    if (simulating)
        g_dUniversalTime += now - g_dLastTickTime;
    else
        g_dUniversalTime += 0.015;

    g_dLastTickTime = now;

    if (g_dUniversalTime < g_dTimerNextThink)
        return;

    for (int i = static_cast<int>(once_off_timers.size()) - 1; i >= 0; --i) {
        Timer *timer = once_off_timers[i];
        if (g_dUniversalTime >= timer->ExecTime) {
            timer->InExec = true;
            try {
                timer->Callback();
            } catch (...) {
            }
            delete timer;
            once_off_timers.erase(once_off_timers.begin() + i);
        }
    }

    for (int i = static_cast<int>(repeat_timers.size()) - 1; i >= 0; --i) {
        Timer *timer = repeat_timers[i];
        if (g_dUniversalTime >= timer->ExecTime) {
            timer->InExec = true;
            try {
                timer->Callback();
            } catch (...) {
            }

            if (timer->KillMe) {
                delete timer;
                repeat_timers.erase(repeat_timers.begin() + i);
                continue;
            }

            timer->InExec = false;
            timer->ExecTime = g_dUniversalTime + timer->Interval;
        }
    }

    g_dTimerNextThink = g_dUniversalTime + 0.1;
}

Timer *scheduler::AddTimer(float interval, TimerCallback callback, int flags) {
    Timer *timer = new Timer(interval, g_dUniversalTime + interval, std::move(callback), flags);

    if (flags & TIMER_FLAG_REPEAT)
        repeat_timers.push_back(timer);
    else
        once_off_timers.push_back(timer);

    return timer;
}

void scheduler::KillTimer(Timer *timer) {
    if (!timer) return;

    auto killFrom = [](std::vector<Timer *> &list, Timer *target) {
        auto it = std::remove_if(list.begin(), list.end(), [=](Timer *t) { return t == target; });
        if (it != list.end()) {
            delete target;
            list.erase(it, list.end());
        }
    };

    if (timer->InExec) {
        timer->KillMe = true;
        return;
    }

    if (timer->Flags & TIMER_FLAG_REPEAT)
        killFrom(repeat_timers, timer);
    else
        killFrom(once_off_timers, timer);
}

void scheduler::RemoveMapChangeTimers() {
    auto removeFrom = [](std::vector<Timer*>& list) {
        for (int i = static_cast<int>(list.size()) - 1; i >= 0; --i) {
            Timer* t = list[i];
            if (t->Flags & TIMER_FLAG_NO_MAPCHANGE) {
                delete t;
                list.erase(list.begin() + i);
            }
        }
    };

    removeFrom(once_off_timers);
    removeFrom(repeat_timers);
}
