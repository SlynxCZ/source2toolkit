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

#ifndef _INCLUDE_CCHICKENIMPL_H
#define _INCLUDE_CCHICKENIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IChicken.h"
#include "schema/entity/classes/CChicken.h"
#include "CDynamicPropImpl.h"

class CChickenImpl : public CDynamicPropImpl, public IChicken
{

public:
    explicit CChickenImpl(CChicken* p) : CDynamicPropImpl(p) {}

private:
    CChicken* Real() { return static_cast<CChicken*>(m_pReal); }
    CChicken* Real() const { return static_cast<CChicken*>(m_pReal); }

public:
    CChicken* GetOriginal() const override { return Real(); }
    ::CAttributeContainer& AttributeManager() override { return Real()->m_AttributeManager(); }
    void AttributeManagerUpdated() override { Real()->m_AttributeManager.NetworkStateChanged(); }
    ::CountdownTimer& UpdateTimer() override { return Real()->m_updateTimer(); }
    void UpdateTimerUpdated() override { Real()->m_updateTimer.NetworkStateChanged(); }
    Vector& StuckAnchor() override { return Real()->m_stuckAnchor(); }
    void StuckAnchorUpdated() override { Real()->m_stuckAnchor.NetworkStateChanged(); }
    ::CountdownTimer& StuckTimer() override { return Real()->m_stuckTimer(); }
    void StuckTimerUpdated() override { Real()->m_stuckTimer.NetworkStateChanged(); }
    ::CountdownTimer& CollisionStuckTimer() override { return Real()->m_collisionStuckTimer(); }
    void CollisionStuckTimerUpdated() override { Real()->m_collisionStuckTimer.NetworkStateChanged(); }
    bool& IsOnGround() override { return Real()->m_isOnGround(); }
    void IsOnGroundUpdated() override { Real()->m_isOnGround.NetworkStateChanged(); }
    Vector& FallVelocity() override { return Real()->m_vFallVelocity(); }
    void FallVelocityUpdated() override { Real()->m_vFallVelocity.NetworkStateChanged(); }
    ::ChickenActivity& DesiredActivity() override { return Real()->m_desiredActivity(); }
    void DesiredActivityUpdated() override { Real()->m_desiredActivity.NetworkStateChanged(); }
    ::ChickenActivity& CurrentActivity() override { return Real()->m_currentActivity(); }
    void CurrentActivityUpdated() override { Real()->m_currentActivity.NetworkStateChanged(); }
    ::CountdownTimer& ActivityTimer() override { return Real()->m_activityTimer(); }
    void ActivityTimerUpdated() override { Real()->m_activityTimer.NetworkStateChanged(); }
    float& TurnRate() override { return Real()->m_turnRate(); }
    void TurnRateUpdated() override { Real()->m_turnRate.NetworkStateChanged(); }
    CHandle<CBaseEntity>& FleeFrom() override { return Real()->m_fleeFrom(); }
    void FleeFromUpdated() override { Real()->m_fleeFrom.NetworkStateChanged(); }
    ::CountdownTimer& MoveRateThrottleTimer() override { return Real()->m_moveRateThrottleTimer(); }
    void MoveRateThrottleTimerUpdated() override { Real()->m_moveRateThrottleTimer.NetworkStateChanged(); }
    ::CountdownTimer& StartleTimer() override { return Real()->m_startleTimer(); }
    void StartleTimerUpdated() override { Real()->m_startleTimer.NetworkStateChanged(); }
    ::CountdownTimer& VocalizeTimer() override { return Real()->m_vocalizeTimer(); }
    void VocalizeTimerUpdated() override { Real()->m_vocalizeTimer.NetworkStateChanged(); }
    float& WhenZombified() override { return Real()->m_flWhenZombified(); }
    void WhenZombifiedUpdated() override { Real()->m_flWhenZombified.NetworkStateChanged(); }
    bool& JumpedThisFrame() override { return Real()->m_jumpedThisFrame(); }
    void JumpedThisFrameUpdated() override { Real()->m_jumpedThisFrame.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& Leader() override { return Real()->m_leader(); }
    void LeaderUpdated() override { Real()->m_leader.NetworkStateChanged(); }
    ::CountdownTimer& ReuseTimer() override { return Real()->m_reuseTimer(); }
    void ReuseTimerUpdated() override { Real()->m_reuseTimer.NetworkStateChanged(); }
    bool& HasBeenUsed() override { return Real()->m_hasBeenUsed(); }
    void HasBeenUsedUpdated() override { Real()->m_hasBeenUsed.NetworkStateChanged(); }
    ::CountdownTimer& JumpTimer() override { return Real()->m_jumpTimer(); }
    void JumpTimerUpdated() override { Real()->m_jumpTimer.NetworkStateChanged(); }
    float& LastJumpTime() override { return Real()->m_flLastJumpTime(); }
    void LastJumpTimeUpdated() override { Real()->m_flLastJumpTime.NetworkStateChanged(); }
    bool& InJump() override { return Real()->m_bInJump(); }
    void InJumpUpdated() override { Real()->m_bInJump.NetworkStateChanged(); }
    ::CountdownTimer& RepathTimer() override { return Real()->m_repathTimer(); }
    void RepathTimerUpdated() override { Real()->m_repathTimer.NetworkStateChanged(); }
    Vector& PathGoal() override { return Real()->m_vecPathGoal(); }
    void PathGoalUpdated() override { Real()->m_vecPathGoal.NetworkStateChanged(); }
    float& ActiveFollowStartTime() override { return Real()->m_flActiveFollowStartTime(); }
    void ActiveFollowStartTimeUpdated() override { Real()->m_flActiveFollowStartTime.NetworkStateChanged(); }
    ::CountdownTimer& FollowMinuteTimer() override { return Real()->m_followMinuteTimer(); }
    void FollowMinuteTimerUpdated() override { Real()->m_followMinuteTimer.NetworkStateChanged(); }
    ::CountdownTimer& BlockDirectionTimer() override { return Real()->m_BlockDirectionTimer(); }
    void BlockDirectionTimerUpdated() override { Real()->m_BlockDirectionTimer.NetworkStateChanged(); }
};

inline IChicken* CChicken::ToInterface() { return new CChickenImpl(this); }
inline IChicken* IChicken::FromOriginal(CChicken* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCHICKENIMPL_H
