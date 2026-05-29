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

#ifndef _INCLUDE_CHOSTAGEIMPL_H
#define _INCLUDE_CHOSTAGEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IHostage.h"
#include "schema/entity/classes/CHostage.h"
#include "CHostageExpresserShimImpl.h"

class CHostageImpl : public CHostageExpresserShimImpl, public IHostage
{

public:
    explicit CHostageImpl(CHostage* p) : CHostageExpresserShimImpl(p) {}

private:
    CHostage* Real() { return static_cast<CHostage*>(m_pReal); }
    CHostage* Real() const { return static_cast<CHostage*>(m_pReal); }

public:
    CHostage* GetOriginal() const override { return Real(); }
    CEntityIOOutput& OnHostageBeginGrab() override { return Real()->m_OnHostageBeginGrab(); }
    void OnHostageBeginGrabUpdated() override { Real()->m_OnHostageBeginGrab.NetworkStateChanged(); }
    CEntityIOOutput& OnFirstPickedUp() override { return Real()->m_OnFirstPickedUp(); }
    void OnFirstPickedUpUpdated() override { Real()->m_OnFirstPickedUp.NetworkStateChanged(); }
    CEntityIOOutput& OnDroppedNotRescued() override { return Real()->m_OnDroppedNotRescued(); }
    void OnDroppedNotRescuedUpdated() override { Real()->m_OnDroppedNotRescued.NetworkStateChanged(); }
    CEntityIOOutput& OnRescued() override { return Real()->m_OnRescued(); }
    void OnRescuedUpdated() override { Real()->m_OnRescued.NetworkStateChanged(); }
    EntitySpottedState_t& EntitySpottedState() override { return Real()->m_entitySpottedState(); }
    void EntitySpottedStateUpdated() override { Real()->m_entitySpottedState.NetworkStateChanged(); }
    int32_t& SpotRules() override { return Real()->m_nSpotRules(); }
    void SpotRulesUpdated() override { Real()->m_nSpotRules.NetworkStateChanged(); }
    uint32_t& UiHostageSpawnExclusionGroupMask() override { return Real()->m_uiHostageSpawnExclusionGroupMask(); }
    void UiHostageSpawnExclusionGroupMaskUpdated() override { Real()->m_uiHostageSpawnExclusionGroupMask.NetworkStateChanged(); }
    uint32_t& HostageSpawnRandomFactor() override { return Real()->m_nHostageSpawnRandomFactor(); }
    void HostageSpawnRandomFactorUpdated() override { Real()->m_nHostageSpawnRandomFactor.NetworkStateChanged(); }
    bool& Remove() override { return Real()->m_bRemove(); }
    void RemoveUpdated() override { Real()->m_bRemove.NetworkStateChanged(); }
    Vector& Vel() override { return Real()->m_vel(); }
    void VelUpdated() override { Real()->m_vel.NetworkStateChanged(); }
    bool& IsRescued() override { return Real()->m_isRescued(); }
    void IsRescuedUpdated() override { Real()->m_isRescued.NetworkStateChanged(); }
    bool& JumpedThisFrame() override { return Real()->m_jumpedThisFrame(); }
    void JumpedThisFrameUpdated() override { Real()->m_jumpedThisFrame.NetworkStateChanged(); }
    int32_t& HostageState() override { return Real()->m_nHostageState(); }
    void HostageStateUpdated() override { Real()->m_nHostageState.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Leader() override { return Real()->m_leader(); }
    void LeaderUpdated() override { Real()->m_leader.NetworkStateChanged(); }
    CHandle<CCSPlayerPawnBase>& LastLeader() override { return Real()->m_lastLeader(); }
    void LastLeaderUpdated() override { Real()->m_lastLeader.NetworkStateChanged(); }
    CountdownTimer& ReuseTimer() override { return Real()->m_reuseTimer(); }
    void ReuseTimerUpdated() override { Real()->m_reuseTimer.NetworkStateChanged(); }
    bool& HasBeenUsed() override { return Real()->m_hasBeenUsed(); }
    void HasBeenUsedUpdated() override { Real()->m_hasBeenUsed.NetworkStateChanged(); }
    Vector& Accel() override { return Real()->m_accel(); }
    void AccelUpdated() override { Real()->m_accel.NetworkStateChanged(); }
    bool& IsRunning() override { return Real()->m_isRunning(); }
    void IsRunningUpdated() override { Real()->m_isRunning.NetworkStateChanged(); }
    bool& IsCrouching() override { return Real()->m_isCrouching(); }
    void IsCrouchingUpdated() override { Real()->m_isCrouching.NetworkStateChanged(); }
    CountdownTimer& JumpTimer() override { return Real()->m_jumpTimer(); }
    void JumpTimerUpdated() override { Real()->m_jumpTimer.NetworkStateChanged(); }
    bool& IsWaitingForLeader() override { return Real()->m_isWaitingForLeader(); }
    void IsWaitingForLeaderUpdated() override { Real()->m_isWaitingForLeader.NetworkStateChanged(); }
    CountdownTimer& RepathTimer() override { return Real()->m_repathTimer(); }
    void RepathTimerUpdated() override { Real()->m_repathTimer.NetworkStateChanged(); }
    CountdownTimer& InhibitDoorTimer() override { return Real()->m_inhibitDoorTimer(); }
    void InhibitDoorTimerUpdated() override { Real()->m_inhibitDoorTimer.NetworkStateChanged(); }
    CountdownTimer& InhibitObstacleAvoidanceTimer() override { return Real()->m_inhibitObstacleAvoidanceTimer(); }
    void InhibitObstacleAvoidanceTimerUpdated() override { Real()->m_inhibitObstacleAvoidanceTimer.NetworkStateChanged(); }
    CountdownTimer& WiggleTimer() override { return Real()->m_wiggleTimer(); }
    void WiggleTimerUpdated() override { Real()->m_wiggleTimer.NetworkStateChanged(); }
    bool& IsAdjusted() override { return Real()->m_isAdjusted(); }
    void IsAdjustedUpdated() override { Real()->m_isAdjusted.NetworkStateChanged(); }
    bool& HandsHaveBeenCut() override { return Real()->m_bHandsHaveBeenCut(); }
    void HandsHaveBeenCutUpdated() override { Real()->m_bHandsHaveBeenCut.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& HostageGrabber() override { return Real()->m_hHostageGrabber(); }
    void HostageGrabberUpdated() override { Real()->m_hHostageGrabber.NetworkStateChanged(); }
    float& LastGrabTime() override { return Real()->m_fLastGrabTime(); }
    void LastGrabTimeUpdated() override { Real()->m_fLastGrabTime.NetworkStateChanged(); }
    Vector& PositionWhenStartedDroppingToGround() override { return Real()->m_vecPositionWhenStartedDroppingToGround(); }
    void PositionWhenStartedDroppingToGroundUpdated() override { Real()->m_vecPositionWhenStartedDroppingToGround.NetworkStateChanged(); }
    Vector& GrabbedPos() override { return Real()->m_vecGrabbedPos(); }
    void GrabbedPosUpdated() override { Real()->m_vecGrabbedPos.NetworkStateChanged(); }
    float& RescueStartTime() override { return Real()->m_flRescueStartTime(); }
    void RescueStartTimeUpdated() override { Real()->m_flRescueStartTime.NetworkStateChanged(); }
    float& GrabSuccessTime() override { return Real()->m_flGrabSuccessTime(); }
    void GrabSuccessTimeUpdated() override { Real()->m_flGrabSuccessTime.NetworkStateChanged(); }
    float& DropStartTime() override { return Real()->m_flDropStartTime(); }
    void DropStartTimeUpdated() override { Real()->m_flDropStartTime.NetworkStateChanged(); }
    int32_t& ApproachRewardPayouts() override { return Real()->m_nApproachRewardPayouts(); }
    void ApproachRewardPayoutsUpdated() override { Real()->m_nApproachRewardPayouts.NetworkStateChanged(); }
    int32_t& PickupEventCount() override { return Real()->m_nPickupEventCount(); }
    void PickupEventCountUpdated() override { Real()->m_nPickupEventCount.NetworkStateChanged(); }
    Vector& SpawnGroundPos() override { return Real()->m_vecSpawnGroundPos(); }
    void SpawnGroundPosUpdated() override { Real()->m_vecSpawnGroundPos.NetworkStateChanged(); }
    Vector& HostageResetPosition() override { return Real()->m_vecHostageResetPosition(); }
    void HostageResetPositionUpdated() override { Real()->m_vecHostageResetPosition.NetworkStateChanged(); }
};

inline IHostage* CHostage::ToInterface() { return new CHostageImpl(this); }
inline IHostage* IHostage::FromOriginal(CHostage* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CHOSTAGEIMPL_H
