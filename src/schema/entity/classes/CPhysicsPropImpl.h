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

#ifndef _INCLUDE_CPHYSICSPROPIMPL_H
#define _INCLUDE_CPHYSICSPROPIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPhysicsProp.h"
#include "schema/entity/classes/CPhysicsProp.h"
#include "CBreakablePropImpl.h"

class CPhysicsPropImpl : public CBreakablePropImpl, public IPhysicsProp
{

public:
    explicit CPhysicsPropImpl(CPhysicsProp* p) : CBreakablePropImpl(p) {}

private:
    CPhysicsProp* Real() { return static_cast<CPhysicsProp*>(m_pReal); }

public:
    CEntityIOOutput& MotionEnabled() override { return Real()->m_MotionEnabled(); }
    void MotionEnabledUpdated() override { Real()->m_MotionEnabled.NetworkStateChanged(); }
    CEntityIOOutput& OnAwakened() override { return Real()->m_OnAwakened(); }
    void OnAwakenedUpdated() override { Real()->m_OnAwakened.NetworkStateChanged(); }
    CEntityIOOutput& OnAwake() override { return Real()->m_OnAwake(); }
    void OnAwakeUpdated() override { Real()->m_OnAwake.NetworkStateChanged(); }
    CEntityIOOutput& OnAsleep() override { return Real()->m_OnAsleep(); }
    void OnAsleepUpdated() override { Real()->m_OnAsleep.NetworkStateChanged(); }
    CEntityIOOutput& OnPlayerUse() override { return Real()->m_OnPlayerUse(); }
    void OnPlayerUseUpdated() override { Real()->m_OnPlayerUse.NetworkStateChanged(); }
    CEntityIOOutput& OnOutOfWorld() override { return Real()->m_OnOutOfWorld(); }
    void OnOutOfWorldUpdated() override { Real()->m_OnOutOfWorld.NetworkStateChanged(); }
    CEntityIOOutput& OnPlayerPickup() override { return Real()->m_OnPlayerPickup(); }
    void OnPlayerPickupUpdated() override { Real()->m_OnPlayerPickup.NetworkStateChanged(); }
    bool& ForceNavIgnore() override { return Real()->m_bForceNavIgnore(); }
    void ForceNavIgnoreUpdated() override { Real()->m_bForceNavIgnore.NetworkStateChanged(); }
    bool& NoNavmeshBlocker() override { return Real()->m_bNoNavmeshBlocker(); }
    void NoNavmeshBlockerUpdated() override { Real()->m_bNoNavmeshBlocker.NetworkStateChanged(); }
    bool& ForceNpcExclude() override { return Real()->m_bForceNpcExclude(); }
    void ForceNpcExcludeUpdated() override { Real()->m_bForceNpcExclude.NetworkStateChanged(); }
    float& MassScale() override { return Real()->m_massScale(); }
    void MassScaleUpdated() override { Real()->m_massScale.NetworkStateChanged(); }
    float& BuoyancyScale() override { return Real()->m_buoyancyScale(); }
    void BuoyancyScaleUpdated() override { Real()->m_buoyancyScale.NetworkStateChanged(); }
    int32_t& DamageType() override { return Real()->m_damageType(); }
    void DamageTypeUpdated() override { Real()->m_damageType.NetworkStateChanged(); }
    int32_t& DamageToEnableMotion() override { return Real()->m_damageToEnableMotion(); }
    void DamageToEnableMotionUpdated() override { Real()->m_damageToEnableMotion.NetworkStateChanged(); }
    float& ForceToEnableMotion() override { return Real()->m_flForceToEnableMotion(); }
    void ForceToEnableMotionUpdated() override { Real()->m_flForceToEnableMotion.NetworkStateChanged(); }
    bool& ThrownByPlayer() override { return Real()->m_bThrownByPlayer(); }
    void ThrownByPlayerUpdated() override { Real()->m_bThrownByPlayer.NetworkStateChanged(); }
    bool& DroppedByPlayer() override { return Real()->m_bDroppedByPlayer(); }
    void DroppedByPlayerUpdated() override { Real()->m_bDroppedByPlayer.NetworkStateChanged(); }
    bool& TouchedByPlayer() override { return Real()->m_bTouchedByPlayer(); }
    void TouchedByPlayerUpdated() override { Real()->m_bTouchedByPlayer.NetworkStateChanged(); }
    bool& FirstCollisionAfterLaunch() override { return Real()->m_bFirstCollisionAfterLaunch(); }
    void FirstCollisionAfterLaunchUpdated() override { Real()->m_bFirstCollisionAfterLaunch.NetworkStateChanged(); }
    bool& HasBeenAwakened() override { return Real()->m_bHasBeenAwakened(); }
    void HasBeenAwakenedUpdated() override { Real()->m_bHasBeenAwakened.NetworkStateChanged(); }
    bool& IsOverrideProp() override { return Real()->m_bIsOverrideProp(); }
    void IsOverridePropUpdated() override { Real()->m_bIsOverrideProp.NetworkStateChanged(); }
    float& LastBurn() override { return Real()->m_flLastBurn(); }
    void LastBurnUpdated() override { Real()->m_flLastBurn.NetworkStateChanged(); }
    DynamicContinuousContactBehavior_t& DynamicContinuousContactBehavior() override { return Real()->m_nDynamicContinuousContactBehavior(); }
    void DynamicContinuousContactBehaviorUpdated() override { Real()->m_nDynamicContinuousContactBehavior.NetworkStateChanged(); }
    float& NextCheckDisableMotionContactsTime() override { return Real()->m_fNextCheckDisableMotionContactsTime(); }
    void NextCheckDisableMotionContactsTimeUpdated() override { Real()->m_fNextCheckDisableMotionContactsTime.NetworkStateChanged(); }
    int32_t& InitialGlowState() override { return Real()->m_iInitialGlowState(); }
    void InitialGlowStateUpdated() override { Real()->m_iInitialGlowState.NetworkStateChanged(); }
    int32_t& GlowRange() override { return Real()->m_nGlowRange(); }
    void GlowRangeUpdated() override { Real()->m_nGlowRange.NetworkStateChanged(); }
    int32_t& GlowRangeMin() override { return Real()->m_nGlowRangeMin(); }
    void GlowRangeMinUpdated() override { Real()->m_nGlowRangeMin.NetworkStateChanged(); }
    Color& GlowColor() override { return Real()->m_glowColor(); }
    void GlowColorUpdated() override { Real()->m_glowColor.NetworkStateChanged(); }
    bool& ShouldAutoConvertBackFromDebris() override { return Real()->m_bShouldAutoConvertBackFromDebris(); }
    void ShouldAutoConvertBackFromDebrisUpdated() override { Real()->m_bShouldAutoConvertBackFromDebris.NetworkStateChanged(); }
    bool& MuteImpactEffects() override { return Real()->m_bMuteImpactEffects(); }
    void MuteImpactEffectsUpdated() override { Real()->m_bMuteImpactEffects.NetworkStateChanged(); }
    INavObstacle__NavObstacleType_t& NavObstacleType() override { return Real()->m_nNavObstacleType(); }
    void NavObstacleTypeUpdated() override { Real()->m_nNavObstacleType.NetworkStateChanged(); }
    bool& UpdateNavWhenMoving() override { return Real()->m_bUpdateNavWhenMoving(); }
    void UpdateNavWhenMovingUpdated() override { Real()->m_bUpdateNavWhenMoving.NetworkStateChanged(); }
    bool& ForceNavObstacleCut() override { return Real()->m_bForceNavObstacleCut(); }
    void ForceNavObstacleCutUpdated() override { Real()->m_bForceNavObstacleCut.NetworkStateChanged(); }
    bool& AllowObstacleConvexHullMerging() override { return Real()->m_bAllowObstacleConvexHullMerging(); }
    void AllowObstacleConvexHullMergingUpdated() override { Real()->m_bAllowObstacleConvexHullMerging.NetworkStateChanged(); }
    bool& AcceptDamageFromHeldObjects() override { return Real()->m_bAcceptDamageFromHeldObjects(); }
    void AcceptDamageFromHeldObjectsUpdated() override { Real()->m_bAcceptDamageFromHeldObjects.NetworkStateChanged(); }
    bool& EnableUseOutput() override { return Real()->m_bEnableUseOutput(); }
    void EnableUseOutputUpdated() override { Real()->m_bEnableUseOutput.NetworkStateChanged(); }
    CPhysicsProp__CrateType_t& CrateType() override { return Real()->m_CrateType(); }
    void CrateTypeUpdated() override { Real()->m_CrateType.NetworkStateChanged(); }
    CUtlSymbolLarge* StrItemClass() override { return Real()->m_strItemClass(); }
    int32_t* ItemCount() override { return Real()->m_nItemCount(); }
    bool& RemovableForAmmoBalancing() override { return Real()->m_bRemovableForAmmoBalancing(); }
    void RemovableForAmmoBalancingUpdated() override { Real()->m_bRemovableForAmmoBalancing.NetworkStateChanged(); }
    bool& Awake() override { return Real()->m_bAwake(); }
    void AwakeUpdated() override { Real()->m_bAwake.NetworkStateChanged(); }
    bool& AttachedToReferenceFrame() override { return Real()->m_bAttachedToReferenceFrame(); }
    void AttachedToReferenceFrameUpdated() override { Real()->m_bAttachedToReferenceFrame.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPHYSICSPROPIMPL_H
