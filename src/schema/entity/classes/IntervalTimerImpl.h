/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
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
 * As a special exception, Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl and
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
 *   - Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl
 *   - AlliedModders LLC
 *
 * Project: Source2Toolkit
 */

#ifndef _INCLUDE_INTERVALTIMERIMPL_H
#define _INCLUDE_INTERVALTIMERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IIntervalTimer.h"
#include "schema/entity/classes/IntervalTimer.h"

class IntervalTimerImpl : public virtual IIntervalTimer
{

protected:
    void* m_pReal;

public:
    explicit IntervalTimerImpl(void* p) : m_pReal(p) {}

private:
    IntervalTimer* Real() { return static_cast<IntervalTimer*>(m_pReal); }
    IntervalTimer* Real() const { return static_cast<IntervalTimer*>(m_pReal); }

public:
    IntervalTimer* GetOriginal() const override { return Real(); }
    float& Timestamp() override { return Real()->m_timestamp(); }
    void TimestampUpdated() override { Real()->m_timestamp.NetworkStateChanged(); }
    WorldGroupId_t& WorldGroupId() override { return Real()->m_nWorldGroupId(); }
    void WorldGroupIdUpdated() override { Real()->m_nWorldGroupId.NetworkStateChanged(); }
};

inline IIntervalTimer* IntervalTimer::ToInterface() { return new IntervalTimerImpl(this); }
inline IIntervalTimer* IIntervalTimer::FromRaw(CEntityInstance*) { return nullptr; }
inline IIntervalTimer* IIntervalTimer::FromOriginal(IntervalTimer* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_INTERVALTIMERIMPL_H
