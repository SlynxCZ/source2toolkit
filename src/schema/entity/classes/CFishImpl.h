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

#ifndef _INCLUDE_CFISHIMPL_H
#define _INCLUDE_CFISHIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IFish.h"
#include "schema/entity/classes/CFish.h"
#include "CBaseAnimGraphImpl.h"

class CFishImpl : public CBaseAnimGraphImpl, public IFish
{

public:
    explicit CFishImpl(CFish* p) : CBaseAnimGraphImpl(p) {}

private:
    CFish* Real() { return static_cast<CFish*>(m_pReal); }
    CFish* Real() const { return static_cast<CFish*>(m_pReal); }

public:
    CFish* GetOriginal() const override { return Real(); }
    CHandle<CFishPool>& Pool() override { return Real()->m_pool(); }
    void PoolUpdated() override { Real()->m_pool.NetworkStateChanged(); }
    uint32_t& Id() override { return Real()->m_id(); }
    void IdUpdated() override { Real()->m_id.NetworkStateChanged(); }
    float& X() override { return Real()->m_x(); }
    void XUpdated() override { Real()->m_x.NetworkStateChanged(); }
    float& Y() override { return Real()->m_y(); }
    void YUpdated() override { Real()->m_y.NetworkStateChanged(); }
    float& Z() override { return Real()->m_z(); }
    void ZUpdated() override { Real()->m_z.NetworkStateChanged(); }
    float& Angle() override { return Real()->m_angle(); }
    void AngleUpdated() override { Real()->m_angle.NetworkStateChanged(); }
    float& AngleChange() override { return Real()->m_angleChange(); }
    void AngleChangeUpdated() override { Real()->m_angleChange.NetworkStateChanged(); }
    Vector& Forward() override { return Real()->m_forward(); }
    void ForwardUpdated() override { Real()->m_forward.NetworkStateChanged(); }
    Vector& Perp() override { return Real()->m_perp(); }
    void PerpUpdated() override { Real()->m_perp.NetworkStateChanged(); }
    Vector& PoolOrigin() override { return Real()->m_poolOrigin(); }
    void PoolOriginUpdated() override { Real()->m_poolOrigin.NetworkStateChanged(); }
    float& WaterLevel() override { return Real()->m_waterLevel(); }
    void WaterLevelUpdated() override { Real()->m_waterLevel.NetworkStateChanged(); }
    float& Speed() override { return Real()->m_speed(); }
    void SpeedUpdated() override { Real()->m_speed.NetworkStateChanged(); }
    float& DesiredSpeed() override { return Real()->m_desiredSpeed(); }
    void DesiredSpeedUpdated() override { Real()->m_desiredSpeed.NetworkStateChanged(); }
    float& CalmSpeed() override { return Real()->m_calmSpeed(); }
    void CalmSpeedUpdated() override { Real()->m_calmSpeed.NetworkStateChanged(); }
    float& PanicSpeed() override { return Real()->m_panicSpeed(); }
    void PanicSpeedUpdated() override { Real()->m_panicSpeed.NetworkStateChanged(); }
    float& AvoidRange() override { return Real()->m_avoidRange(); }
    void AvoidRangeUpdated() override { Real()->m_avoidRange.NetworkStateChanged(); }
    CountdownTimer& TurnTimer() override { return Real()->m_turnTimer(); }
    void TurnTimerUpdated() override { Real()->m_turnTimer.NetworkStateChanged(); }
    bool& TurnClockwise() override { return Real()->m_turnClockwise(); }
    void TurnClockwiseUpdated() override { Real()->m_turnClockwise.NetworkStateChanged(); }
    CountdownTimer& GoTimer() override { return Real()->m_goTimer(); }
    void GoTimerUpdated() override { Real()->m_goTimer.NetworkStateChanged(); }
    CountdownTimer& MoveTimer() override { return Real()->m_moveTimer(); }
    void MoveTimerUpdated() override { Real()->m_moveTimer.NetworkStateChanged(); }
    CountdownTimer& PanicTimer() override { return Real()->m_panicTimer(); }
    void PanicTimerUpdated() override { Real()->m_panicTimer.NetworkStateChanged(); }
    CountdownTimer& DisperseTimer() override { return Real()->m_disperseTimer(); }
    void DisperseTimerUpdated() override { Real()->m_disperseTimer.NetworkStateChanged(); }
    CountdownTimer& ProximityTimer() override { return Real()->m_proximityTimer(); }
    void ProximityTimerUpdated() override { Real()->m_proximityTimer.NetworkStateChanged(); }
    CUtlVector<CFish*>& Visible() override { return Real()->m_visible(); }
    void VisibleUpdated() override { Real()->m_visible.NetworkStateChanged(); }
};

inline IFish* CFish::ToInterface() { return new CFishImpl(this); }
inline IFish* IFish::FromOriginal(CFish* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CFISHIMPL_H
