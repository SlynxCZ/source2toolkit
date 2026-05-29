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

#ifndef _INCLUDE_CCSWEAPONBASEVDATAIMPL_H
#define _INCLUDE_CCSWEAPONBASEVDATAIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSWeaponBaseVData.h"
#include "schema/entity/classes/CCSWeaponBaseVData.h"
#include "CBasePlayerWeaponVDataImpl.h"

class CCSWeaponBaseVDataImpl : public CBasePlayerWeaponVDataImpl, public virtual ICSWeaponBaseVData
{

public:
    explicit CCSWeaponBaseVDataImpl(CCSWeaponBaseVData* p) : CBasePlayerWeaponVDataImpl(p) {}

private:
    CCSWeaponBaseVData* Real() { return static_cast<CCSWeaponBaseVData*>(m_pReal); }
    CCSWeaponBaseVData* Real() const { return static_cast<CCSWeaponBaseVData*>(m_pReal); }

public:
    CCSWeaponBaseVData* GetOriginal() const override { return Real(); }
    ::CSWeaponType& WeaponType() override { return Real()->m_WeaponType(); }
    void WeaponTypeUpdated() override { Real()->m_WeaponType.NetworkStateChanged(); }
    ::CSWeaponCategory& WeaponCategory() override { return Real()->m_WeaponCategory(); }
    void WeaponCategoryUpdated() override { Real()->m_WeaponCategory.NetworkStateChanged(); }
    Vector& MuzzlePos0() override { return Real()->m_vecMuzzlePos0(); }
    void MuzzlePos0Updated() override { Real()->m_vecMuzzlePos0.NetworkStateChanged(); }
    Vector& MuzzlePos1() override { return Real()->m_vecMuzzlePos1(); }
    void MuzzlePos1Updated() override { Real()->m_vecMuzzlePos1.NetworkStateChanged(); }
    ::gear_slot_t& GearSlot() override { return Real()->m_GearSlot(); }
    void GearSlotUpdated() override { Real()->m_GearSlot.NetworkStateChanged(); }
    int32_t& GearSlotPosition() override { return Real()->m_GearSlotPosition(); }
    void GearSlotPositionUpdated() override { Real()->m_GearSlotPosition.NetworkStateChanged(); }
    ::loadout_slot_t& DefaultLoadoutSlot() override { return Real()->m_DefaultLoadoutSlot(); }
    void DefaultLoadoutSlotUpdated() override { Real()->m_DefaultLoadoutSlot.NetworkStateChanged(); }
    int32_t& Price() override { return Real()->m_nPrice(); }
    void PriceUpdated() override { Real()->m_nPrice.NetworkStateChanged(); }
    int32_t& KillAward() override { return Real()->m_nKillAward(); }
    void KillAwardUpdated() override { Real()->m_nKillAward.NetworkStateChanged(); }
    int32_t& PrimaryReserveAmmoMax() override { return Real()->m_nPrimaryReserveAmmoMax(); }
    void PrimaryReserveAmmoMaxUpdated() override { Real()->m_nPrimaryReserveAmmoMax.NetworkStateChanged(); }
    int32_t& SecondaryReserveAmmoMax() override { return Real()->m_nSecondaryReserveAmmoMax(); }
    void SecondaryReserveAmmoMaxUpdated() override { Real()->m_nSecondaryReserveAmmoMax.NetworkStateChanged(); }
    bool& MeleeWeapon() override { return Real()->m_bMeleeWeapon(); }
    void MeleeWeaponUpdated() override { Real()->m_bMeleeWeapon.NetworkStateChanged(); }
    bool& HasBurstMode() override { return Real()->m_bHasBurstMode(); }
    void HasBurstModeUpdated() override { Real()->m_bHasBurstMode.NetworkStateChanged(); }
    bool& IsRevolver() override { return Real()->m_bIsRevolver(); }
    void IsRevolverUpdated() override { Real()->m_bIsRevolver.NetworkStateChanged(); }
    bool& CannotShootUnderwater() override { return Real()->m_bCannotShootUnderwater(); }
    void CannotShootUnderwaterUpdated() override { Real()->m_bCannotShootUnderwater.NetworkStateChanged(); }
    CGlobalSymbol& Name() override { return Real()->m_szName(); }
    void NameUpdated() override { Real()->m_szName.NetworkStateChanged(); }
    ::CSWeaponSilencerType& SilencerType() override { return Real()->m_eSilencerType(); }
    void SilencerTypeUpdated() override { Real()->m_eSilencerType.NetworkStateChanged(); }
    int32_t& CrosshairMinDistance() override { return Real()->m_nCrosshairMinDistance(); }
    void CrosshairMinDistanceUpdated() override { Real()->m_nCrosshairMinDistance.NetworkStateChanged(); }
    int32_t& CrosshairDeltaDistance() override { return Real()->m_nCrosshairDeltaDistance(); }
    void CrosshairDeltaDistanceUpdated() override { Real()->m_nCrosshairDeltaDistance.NetworkStateChanged(); }
    bool& IsFullAuto() override { return Real()->m_bIsFullAuto(); }
    void IsFullAutoUpdated() override { Real()->m_bIsFullAuto.NetworkStateChanged(); }
    int32_t& NumBullets() override { return Real()->m_nNumBullets(); }
    void NumBulletsUpdated() override { Real()->m_nNumBullets.NetworkStateChanged(); }
    bool& ReloadsSingleShells() override { return Real()->m_bReloadsSingleShells(); }
    void ReloadsSingleShellsUpdated() override { Real()->m_bReloadsSingleShells.NetworkStateChanged(); }
    ::CFiringModeFloat& CycleTime() override { return Real()->m_flCycleTime(); }
    void CycleTimeUpdated() override { Real()->m_flCycleTime.NetworkStateChanged(); }
    float& CycleTimeWhenInBurstMode() override { return Real()->m_flCycleTimeWhenInBurstMode(); }
    void CycleTimeWhenInBurstModeUpdated() override { Real()->m_flCycleTimeWhenInBurstMode.NetworkStateChanged(); }
    float& TimeBetweenBurstShots() override { return Real()->m_flTimeBetweenBurstShots(); }
    void TimeBetweenBurstShotsUpdated() override { Real()->m_flTimeBetweenBurstShots.NetworkStateChanged(); }
    ::CFiringModeFloat& MaxSpeed() override { return Real()->m_flMaxSpeed(); }
    void MaxSpeedUpdated() override { Real()->m_flMaxSpeed.NetworkStateChanged(); }
    ::CFiringModeFloat& Spread() override { return Real()->m_flSpread(); }
    void SpreadUpdated() override { Real()->m_flSpread.NetworkStateChanged(); }
    ::CFiringModeFloat& InaccuracyCrouch() override { return Real()->m_flInaccuracyCrouch(); }
    void InaccuracyCrouchUpdated() override { Real()->m_flInaccuracyCrouch.NetworkStateChanged(); }
    ::CFiringModeFloat& InaccuracyStand() override { return Real()->m_flInaccuracyStand(); }
    void InaccuracyStandUpdated() override { Real()->m_flInaccuracyStand.NetworkStateChanged(); }
    ::CFiringModeFloat& InaccuracyJump() override { return Real()->m_flInaccuracyJump(); }
    void InaccuracyJumpUpdated() override { Real()->m_flInaccuracyJump.NetworkStateChanged(); }
    ::CFiringModeFloat& InaccuracyLand() override { return Real()->m_flInaccuracyLand(); }
    void InaccuracyLandUpdated() override { Real()->m_flInaccuracyLand.NetworkStateChanged(); }
    ::CFiringModeFloat& InaccuracyLadder() override { return Real()->m_flInaccuracyLadder(); }
    void InaccuracyLadderUpdated() override { Real()->m_flInaccuracyLadder.NetworkStateChanged(); }
    ::CFiringModeFloat& InaccuracyFire() override { return Real()->m_flInaccuracyFire(); }
    void InaccuracyFireUpdated() override { Real()->m_flInaccuracyFire.NetworkStateChanged(); }
    ::CFiringModeFloat& InaccuracyMove() override { return Real()->m_flInaccuracyMove(); }
    void InaccuracyMoveUpdated() override { Real()->m_flInaccuracyMove.NetworkStateChanged(); }
    ::CFiringModeFloat& RecoilAngle() override { return Real()->m_flRecoilAngle(); }
    void RecoilAngleUpdated() override { Real()->m_flRecoilAngle.NetworkStateChanged(); }
    ::CFiringModeFloat& RecoilAngleVariance() override { return Real()->m_flRecoilAngleVariance(); }
    void RecoilAngleVarianceUpdated() override { Real()->m_flRecoilAngleVariance.NetworkStateChanged(); }
    ::CFiringModeFloat& RecoilMagnitude() override { return Real()->m_flRecoilMagnitude(); }
    void RecoilMagnitudeUpdated() override { Real()->m_flRecoilMagnitude.NetworkStateChanged(); }
    ::CFiringModeFloat& RecoilMagnitudeVariance() override { return Real()->m_flRecoilMagnitudeVariance(); }
    void RecoilMagnitudeVarianceUpdated() override { Real()->m_flRecoilMagnitudeVariance.NetworkStateChanged(); }
    ::CFiringModeInt& TracerFrequency() override { return Real()->m_nTracerFrequency(); }
    void TracerFrequencyUpdated() override { Real()->m_nTracerFrequency.NetworkStateChanged(); }
    float& InaccuracyJumpInitial() override { return Real()->m_flInaccuracyJumpInitial(); }
    void InaccuracyJumpInitialUpdated() override { Real()->m_flInaccuracyJumpInitial.NetworkStateChanged(); }
    float& InaccuracyJumpApex() override { return Real()->m_flInaccuracyJumpApex(); }
    void InaccuracyJumpApexUpdated() override { Real()->m_flInaccuracyJumpApex.NetworkStateChanged(); }
    float& InaccuracyReload() override { return Real()->m_flInaccuracyReload(); }
    void InaccuracyReloadUpdated() override { Real()->m_flInaccuracyReload.NetworkStateChanged(); }
    float& DeployDuration() override { return Real()->m_flDeployDuration(); }
    void DeployDurationUpdated() override { Real()->m_flDeployDuration.NetworkStateChanged(); }
    float& DisallowAttackAfterReloadStartDuration() override { return Real()->m_flDisallowAttackAfterReloadStartDuration(); }
    void DisallowAttackAfterReloadStartDurationUpdated() override { Real()->m_flDisallowAttackAfterReloadStartDuration.NetworkStateChanged(); }
    int32_t& BurstShotCount() override { return Real()->m_nBurstShotCount(); }
    void BurstShotCountUpdated() override { Real()->m_nBurstShotCount.NetworkStateChanged(); }
    bool& AllowBurstHolster() override { return Real()->m_bAllowBurstHolster(); }
    void AllowBurstHolsterUpdated() override { Real()->m_bAllowBurstHolster.NetworkStateChanged(); }
    int32_t& RecoilSeed() override { return Real()->m_nRecoilSeed(); }
    void RecoilSeedUpdated() override { Real()->m_nRecoilSeed.NetworkStateChanged(); }
    int32_t& SpreadSeed() override { return Real()->m_nSpreadSeed(); }
    void SpreadSeedUpdated() override { Real()->m_nSpreadSeed.NetworkStateChanged(); }
    float& AttackMovespeedFactor() override { return Real()->m_flAttackMovespeedFactor(); }
    void AttackMovespeedFactorUpdated() override { Real()->m_flAttackMovespeedFactor.NetworkStateChanged(); }
    float& InaccuracyPitchShift() override { return Real()->m_flInaccuracyPitchShift(); }
    void InaccuracyPitchShiftUpdated() override { Real()->m_flInaccuracyPitchShift.NetworkStateChanged(); }
    float& InaccuracyAltSoundThreshold() override { return Real()->m_flInaccuracyAltSoundThreshold(); }
    void InaccuracyAltSoundThresholdUpdated() override { Real()->m_flInaccuracyAltSoundThreshold.NetworkStateChanged(); }
    CUtlString& UseRadioSubtitle() override { return Real()->m_szUseRadioSubtitle(); }
    void UseRadioSubtitleUpdated() override { Real()->m_szUseRadioSubtitle.NetworkStateChanged(); }
    bool& UnzoomsAfterShot() override { return Real()->m_bUnzoomsAfterShot(); }
    void UnzoomsAfterShotUpdated() override { Real()->m_bUnzoomsAfterShot.NetworkStateChanged(); }
    bool& HideViewModelWhenZoomed() override { return Real()->m_bHideViewModelWhenZoomed(); }
    void HideViewModelWhenZoomedUpdated() override { Real()->m_bHideViewModelWhenZoomed.NetworkStateChanged(); }
    int32_t& ZoomLevels() override { return Real()->m_nZoomLevels(); }
    void ZoomLevelsUpdated() override { Real()->m_nZoomLevels.NetworkStateChanged(); }
    int32_t& ZoomFOV1() override { return Real()->m_nZoomFOV1(); }
    void ZoomFOV1Updated() override { Real()->m_nZoomFOV1.NetworkStateChanged(); }
    int32_t& ZoomFOV2() override { return Real()->m_nZoomFOV2(); }
    void ZoomFOV2Updated() override { Real()->m_nZoomFOV2.NetworkStateChanged(); }
    float& ZoomTime0() override { return Real()->m_flZoomTime0(); }
    void ZoomTime0Updated() override { Real()->m_flZoomTime0.NetworkStateChanged(); }
    float& ZoomTime1() override { return Real()->m_flZoomTime1(); }
    void ZoomTime1Updated() override { Real()->m_flZoomTime1.NetworkStateChanged(); }
    float& ZoomTime2() override { return Real()->m_flZoomTime2(); }
    void ZoomTime2Updated() override { Real()->m_flZoomTime2.NetworkStateChanged(); }
    float& IronSightPullUpSpeed() override { return Real()->m_flIronSightPullUpSpeed(); }
    void IronSightPullUpSpeedUpdated() override { Real()->m_flIronSightPullUpSpeed.NetworkStateChanged(); }
    float& IronSightPutDownSpeed() override { return Real()->m_flIronSightPutDownSpeed(); }
    void IronSightPutDownSpeedUpdated() override { Real()->m_flIronSightPutDownSpeed.NetworkStateChanged(); }
    float& IronSightFOV() override { return Real()->m_flIronSightFOV(); }
    void IronSightFOVUpdated() override { Real()->m_flIronSightFOV.NetworkStateChanged(); }
    float& IronSightPivotForward() override { return Real()->m_flIronSightPivotForward(); }
    void IronSightPivotForwardUpdated() override { Real()->m_flIronSightPivotForward.NetworkStateChanged(); }
    float& IronSightLooseness() override { return Real()->m_flIronSightLooseness(); }
    void IronSightLoosenessUpdated() override { Real()->m_flIronSightLooseness.NetworkStateChanged(); }
    int32_t& Damage() override { return Real()->m_nDamage(); }
    void DamageUpdated() override { Real()->m_nDamage.NetworkStateChanged(); }
    float& HeadshotMultiplier() override { return Real()->m_flHeadshotMultiplier(); }
    void HeadshotMultiplierUpdated() override { Real()->m_flHeadshotMultiplier.NetworkStateChanged(); }
    float& ArmorRatio() override { return Real()->m_flArmorRatio(); }
    void ArmorRatioUpdated() override { Real()->m_flArmorRatio.NetworkStateChanged(); }
    float& Penetration() override { return Real()->m_flPenetration(); }
    void PenetrationUpdated() override { Real()->m_flPenetration.NetworkStateChanged(); }
    float& Range() override { return Real()->m_flRange(); }
    void RangeUpdated() override { Real()->m_flRange.NetworkStateChanged(); }
    float& RangeModifier() override { return Real()->m_flRangeModifier(); }
    void RangeModifierUpdated() override { Real()->m_flRangeModifier.NetworkStateChanged(); }
    float& FlinchVelocityModifierLarge() override { return Real()->m_flFlinchVelocityModifierLarge(); }
    void FlinchVelocityModifierLargeUpdated() override { Real()->m_flFlinchVelocityModifierLarge.NetworkStateChanged(); }
    float& FlinchVelocityModifierSmall() override { return Real()->m_flFlinchVelocityModifierSmall(); }
    void FlinchVelocityModifierSmallUpdated() override { Real()->m_flFlinchVelocityModifierSmall.NetworkStateChanged(); }
    float& RecoveryTimeCrouch() override { return Real()->m_flRecoveryTimeCrouch(); }
    void RecoveryTimeCrouchUpdated() override { Real()->m_flRecoveryTimeCrouch.NetworkStateChanged(); }
    float& RecoveryTimeStand() override { return Real()->m_flRecoveryTimeStand(); }
    void RecoveryTimeStandUpdated() override { Real()->m_flRecoveryTimeStand.NetworkStateChanged(); }
    float& RecoveryTimeCrouchFinal() override { return Real()->m_flRecoveryTimeCrouchFinal(); }
    void RecoveryTimeCrouchFinalUpdated() override { Real()->m_flRecoveryTimeCrouchFinal.NetworkStateChanged(); }
    float& RecoveryTimeStandFinal() override { return Real()->m_flRecoveryTimeStandFinal(); }
    void RecoveryTimeStandFinalUpdated() override { Real()->m_flRecoveryTimeStandFinal.NetworkStateChanged(); }
    int32_t& RecoveryTransitionStartBullet() override { return Real()->m_nRecoveryTransitionStartBullet(); }
    void RecoveryTransitionStartBulletUpdated() override { Real()->m_nRecoveryTransitionStartBullet.NetworkStateChanged(); }
    int32_t& RecoveryTransitionEndBullet() override { return Real()->m_nRecoveryTransitionEndBullet(); }
    void RecoveryTransitionEndBulletUpdated() override { Real()->m_nRecoveryTransitionEndBullet.NetworkStateChanged(); }
    float& ThrowVelocity() override { return Real()->m_flThrowVelocity(); }
    void ThrowVelocityUpdated() override { Real()->m_flThrowVelocity.NetworkStateChanged(); }
    Vector& SmokeColor() override { return Real()->m_vSmokeColor(); }
    void SmokeColorUpdated() override { Real()->m_vSmokeColor.NetworkStateChanged(); }
    CGlobalSymbol& AnimClass() override { return Real()->m_szAnimClass(); }
    void AnimClassUpdated() override { Real()->m_szAnimClass.NetworkStateChanged(); }
};

inline ICSWeaponBaseVData* CCSWeaponBaseVData::ToInterface() { return new CCSWeaponBaseVDataImpl(this); }
inline ICSWeaponBaseVData* ICSWeaponBaseVData::FromRaw(CEntityInstance*) { return nullptr; }
inline ICSWeaponBaseVData* ICSWeaponBaseVData::FromOriginal(CCSWeaponBaseVData* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSWEAPONBASEVDATAIMPL_H
