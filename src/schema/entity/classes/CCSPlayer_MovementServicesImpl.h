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

#ifndef _INCLUDE_CCSPLAYER_MOVEMENTSERVICESIMPL_H
#define _INCLUDE_CCSPLAYER_MOVEMENTSERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayer_MovementServices.h"
#include "schema/entity/classes/CCSPlayer_MovementServices.h"
#include "CPlayer_MovementServices_HumanoidImpl.h"

class CCSPlayer_MovementServicesImpl : public CPlayer_MovementServices_HumanoidImpl, public virtual ICSPlayer_MovementServices
{

public:
    explicit CCSPlayer_MovementServicesImpl(CCSPlayer_MovementServices* p) : CPlayer_MovementServices_HumanoidImpl(p) {}

private:
    CCSPlayer_MovementServices* Real() { return static_cast<CCSPlayer_MovementServices*>(m_pReal); }
    CCSPlayer_MovementServices* Real() const { return static_cast<CCSPlayer_MovementServices*>(m_pReal); }

public:
    CCSPlayer_MovementServices* GetOriginal() const override { return Real(); }
    ::CCSPlayerAnimationState& AnimationState() override { return Real()->m_AnimationState(); }
    void AnimationStateUpdated() override { Real()->m_AnimationState.NetworkStateChanged(); }
    bool& UsingGroundTopologyOffset() override { return Real()->m_bUsingGroundTopologyOffset(); }
    void UsingGroundTopologyOffsetUpdated() override { Real()->m_bUsingGroundTopologyOffset.NetworkStateChanged(); }
    float& UsingGroundTopologyOffsetTransitionSmoothing() override { return Real()->m_flUsingGroundTopologyOffsetTransitionSmoothing(); }
    void UsingGroundTopologyOffsetTransitionSmoothingUpdated() override { Real()->m_flUsingGroundTopologyOffsetTransitionSmoothing.NetworkStateChanged(); }
    Vector& LadderNormal() override { return Real()->m_vecLadderNormal(); }
    void LadderNormalUpdated() override { Real()->m_vecLadderNormal.NetworkStateChanged(); }
    int32_t& LadderSurfacePropIndex() override { return Real()->m_nLadderSurfacePropIndex(); }
    void LadderSurfacePropIndexUpdated() override { Real()->m_nLadderSurfacePropIndex.NetworkStateChanged(); }
    bool& Ducked() override { return Real()->m_bDucked(); }
    void DuckedUpdated() override { Real()->m_bDucked.NetworkStateChanged(); }
    float& DuckAmount() override { return Real()->m_flDuckAmount(); }
    void DuckAmountUpdated() override { Real()->m_flDuckAmount.NetworkStateChanged(); }
    float& DuckSpeed() override { return Real()->m_flDuckSpeed(); }
    void DuckSpeedUpdated() override { Real()->m_flDuckSpeed.NetworkStateChanged(); }
    bool& DuckOverride() override { return Real()->m_bDuckOverride(); }
    void DuckOverrideUpdated() override { Real()->m_bDuckOverride.NetworkStateChanged(); }
    bool& DesiresDuck() override { return Real()->m_bDesiresDuck(); }
    void DesiresDuckUpdated() override { Real()->m_bDesiresDuck.NetworkStateChanged(); }
    bool& Ducking() override { return Real()->m_bDucking(); }
    void DuckingUpdated() override { Real()->m_bDucking.NetworkStateChanged(); }
    float& DuckRootOffset() override { return Real()->m_flDuckRootOffset(); }
    void DuckRootOffsetUpdated() override { Real()->m_flDuckRootOffset.NetworkStateChanged(); }
    float& DuckViewOffset() override { return Real()->m_flDuckViewOffset(); }
    void DuckViewOffsetUpdated() override { Real()->m_flDuckViewOffset.NetworkStateChanged(); }
    float& LastDuckTime() override { return Real()->m_flLastDuckTime(); }
    void LastDuckTimeUpdated() override { Real()->m_flLastDuckTime.NetworkStateChanged(); }
    float& BombPlantViewOffset() override { return Real()->m_flBombPlantViewOffset(); }
    void BombPlantViewOffsetUpdated() override { Real()->m_flBombPlantViewOffset.NetworkStateChanged(); }
    Vector2D& LastPositionAtFullCrouchSpeed() override { return Real()->m_vecLastPositionAtFullCrouchSpeed(); }
    void LastPositionAtFullCrouchSpeedUpdated() override { Real()->m_vecLastPositionAtFullCrouchSpeed.NetworkStateChanged(); }
    bool& DuckUntilOnGround() override { return Real()->m_duckUntilOnGround(); }
    void DuckUntilOnGroundUpdated() override { Real()->m_duckUntilOnGround.NetworkStateChanged(); }
    bool& HasWalkMovedSinceLastJump() override { return Real()->m_bHasWalkMovedSinceLastJump(); }
    void HasWalkMovedSinceLastJumpUpdated() override { Real()->m_bHasWalkMovedSinceLastJump.NetworkStateChanged(); }
    bool& InStuckTest() override { return Real()->m_bInStuckTest(); }
    void InStuckTestUpdated() override { Real()->m_bInStuckTest.NetworkStateChanged(); }
    int32_t& TraceCount() override { return Real()->m_nTraceCount(); }
    void TraceCountUpdated() override { Real()->m_nTraceCount.NetworkStateChanged(); }
    int32_t& StuckLast() override { return Real()->m_StuckLast(); }
    void StuckLastUpdated() override { Real()->m_StuckLast.NetworkStateChanged(); }
    bool& SpeedCropped() override { return Real()->m_bSpeedCropped(); }
    void SpeedCroppedUpdated() override { Real()->m_bSpeedCropped.NetworkStateChanged(); }
    int32_t& OldWaterLevel() override { return Real()->m_nOldWaterLevel(); }
    void OldWaterLevelUpdated() override { Real()->m_nOldWaterLevel.NetworkStateChanged(); }
    float& WaterEntryTime() override { return Real()->m_flWaterEntryTime(); }
    void WaterEntryTimeUpdated() override { Real()->m_flWaterEntryTime.NetworkStateChanged(); }
    Vector& Forward() override { return Real()->m_vecForward(); }
    void ForwardUpdated() override { Real()->m_vecForward.NetworkStateChanged(); }
    Vector& Left() override { return Real()->m_vecLeft(); }
    void LeftUpdated() override { Real()->m_vecLeft.NetworkStateChanged(); }
    Vector& Up() override { return Real()->m_vecUp(); }
    void UpUpdated() override { Real()->m_vecUp.NetworkStateChanged(); }
    int32_t& GameCodeHasMovedPlayerAfterCommand() override { return Real()->m_nGameCodeHasMovedPlayerAfterCommand(); }
    void GameCodeHasMovedPlayerAfterCommandUpdated() override { Real()->m_nGameCodeHasMovedPlayerAfterCommand.NetworkStateChanged(); }
    bool& MadeFootstepNoise() override { return Real()->m_bMadeFootstepNoise(); }
    void MadeFootstepNoiseUpdated() override { Real()->m_bMadeFootstepNoise.NetworkStateChanged(); }
    int32_t& Footsteps() override { return Real()->m_iFootsteps(); }
    void FootstepsUpdated() override { Real()->m_iFootsteps.NetworkStateChanged(); }
    float& StashGrenadeParameterWhen() override { return Real()->m_fStashGrenadeParameterWhen(); }
    void StashGrenadeParameterWhenUpdated() override { Real()->m_fStashGrenadeParameterWhen.NetworkStateChanged(); }
    uint64_t& ButtonDownMaskPrev() override { return Real()->m_nButtonDownMaskPrev(); }
    void ButtonDownMaskPrevUpdated() override { Real()->m_nButtonDownMaskPrev.NetworkStateChanged(); }
    bool& UseFrictionStashedSpeed() override { return Real()->m_bUseFrictionStashedSpeed(); }
    void UseFrictionStashedSpeedUpdated() override { Real()->m_bUseFrictionStashedSpeed.NetworkStateChanged(); }
    float& UseFrictionStashedSpeedUntilFrac() override { return Real()->m_flUseFrictionStashedSpeedUntilFrac(); }
    void UseFrictionStashedSpeedUntilFracUpdated() override { Real()->m_flUseFrictionStashedSpeedUntilFrac.NetworkStateChanged(); }
    float& FrictionStashedSpeed() override { return Real()->m_flFrictionStashedSpeed(); }
    void FrictionStashedSpeedUpdated() override { Real()->m_flFrictionStashedSpeed.NetworkStateChanged(); }
    float& Stamina() override { return Real()->m_flStamina(); }
    void StaminaUpdated() override { Real()->m_flStamina.NetworkStateChanged(); }
    float& HeightAtJumpStart() override { return Real()->m_flHeightAtJumpStart(); }
    void HeightAtJumpStartUpdated() override { Real()->m_flHeightAtJumpStart.NetworkStateChanged(); }
    float& MaxJumpHeightThisJump() override { return Real()->m_flMaxJumpHeightThisJump(); }
    void MaxJumpHeightThisJumpUpdated() override { Real()->m_flMaxJumpHeightThisJump.NetworkStateChanged(); }
    float& MaxJumpHeightLastJump() override { return Real()->m_flMaxJumpHeightLastJump(); }
    void MaxJumpHeightLastJumpUpdated() override { Real()->m_flMaxJumpHeightLastJump.NetworkStateChanged(); }
    float& StaminaAtJumpStart() override { return Real()->m_flStaminaAtJumpStart(); }
    void StaminaAtJumpStartUpdated() override { Real()->m_flStaminaAtJumpStart.NetworkStateChanged(); }
    float& VelMulAtJumpStart() override { return Real()->m_flVelMulAtJumpStart(); }
    void VelMulAtJumpStartUpdated() override { Real()->m_flVelMulAtJumpStart.NetworkStateChanged(); }
    float& AccumulatedJumpError() override { return Real()->m_flAccumulatedJumpError(); }
    void AccumulatedJumpErrorUpdated() override { Real()->m_flAccumulatedJumpError.NetworkStateChanged(); }
    ::CCSPlayerLegacyJump& LegacyJump() override { return Real()->m_LegacyJump(); }
    void LegacyJumpUpdated() override { Real()->m_LegacyJump.NetworkStateChanged(); }
    ::CCSPlayerModernJump& ModernJump() override { return Real()->m_ModernJump(); }
    void ModernJumpUpdated() override { Real()->m_ModernJump.NetworkStateChanged(); }
    int32_t& LastJumpTick() override { return Real()->m_nLastJumpTick(); }
    void LastJumpTickUpdated() override { Real()->m_nLastJumpTick.NetworkStateChanged(); }
    float& LastJumpFrac() override { return Real()->m_flLastJumpFrac(); }
    void LastJumpFracUpdated() override { Real()->m_flLastJumpFrac.NetworkStateChanged(); }
    float& LastJumpVelocityZ() override { return Real()->m_flLastJumpVelocityZ(); }
    void LastJumpVelocityZUpdated() override { Real()->m_flLastJumpVelocityZ.NetworkStateChanged(); }
    bool& JumpApexPending() override { return Real()->m_bJumpApexPending(); }
    void JumpApexPendingUpdated() override { Real()->m_bJumpApexPending.NetworkStateChanged(); }
    float& TicksSinceLastSurfingDetected() override { return Real()->m_flTicksSinceLastSurfingDetected(); }
    void TicksSinceLastSurfingDetectedUpdated() override { Real()->m_flTicksSinceLastSurfingDetected.NetworkStateChanged(); }
    bool& WasSurfing() override { return Real()->m_bWasSurfing(); }
    void WasSurfingUpdated() override { Real()->m_bWasSurfing.NetworkStateChanged(); }
    Vector2D& WalkWishVel() override { return Real()->m_vecWalkWishVel(); }
    void WalkWishVelUpdated() override { Real()->m_vecWalkWishVel.NetworkStateChanged(); }
    bool& HasEverProcessedCommand() override { return Real()->m_bHasEverProcessedCommand(); }
    void HasEverProcessedCommandUpdated() override { Real()->m_bHasEverProcessedCommand.NetworkStateChanged(); }
};

inline ICSPlayer_MovementServices* CCSPlayer_MovementServices::ToInterface() { return new CCSPlayer_MovementServicesImpl(this); }
inline ICSPlayer_MovementServices* ICSPlayer_MovementServices::FromRaw(CEntityInstance*) { return nullptr; }
inline ICSPlayer_MovementServices* ICSPlayer_MovementServices::FromOriginal(CCSPlayer_MovementServices* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSPLAYER_MOVEMENTSERVICESIMPL_H
