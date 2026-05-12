/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
 * AlliedModders LLC. All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl and
 * AlliedModders LLC give you permission to link the code of this program
 * (as well as its derivative works) to "Counter-Strike 2," "Source 2,"
 * "Steam," and any Game MODs or server software running on software by
 * Valve Corporation. You must obey the GNU General Public License in all
 * respects for all other code used.
 *
 * Additionally, this exception applies to all derivative works unless
 * otherwise stated in LICENSE.txt.
 *
 * Authors:
 *   - Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl
 *   - AlliedModders LLC
 *
 * Project: Source2Toolkit
 */
#include "scheduler.h"
#include <algorithm>
#include <chrono>
#include <mutex>
#include <queue>

bool g_bHasTicked = false;
double g_dUniversalTime = 0.0;
double g_dLastTickTime = 0.0;
double g_dTimerNextThink = 0.0;

Scheduler toolkitScheduler;

namespace {
    std::vector<Timer *> once_off_timers;
    std::vector<Timer *> repeat_timers;
    std::mutex nextFrameMutex;
    std::queue<std::function<void()> > nextFrameQueue;
}

void Scheduler::NextFrame(std::function<void()> &&task) {
    std::lock_guard lock(nextFrameMutex);
    nextFrameQueue.emplace(std::move(task));
}

Timer *Scheduler::AddTimer(float interval, TimerCallback callback, int flags) {
    Timer *timer = new Timer(interval, g_dUniversalTime + interval, std::move(callback), flags);

    if (flags & TIMER_FLAG_REPEAT)
        repeat_timers.push_back(timer);
    else
        once_off_timers.push_back(timer);

    return timer;
}

void Scheduler::KillTimer(Timer *timer) {
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
