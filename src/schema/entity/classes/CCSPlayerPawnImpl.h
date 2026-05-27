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

#ifndef _INCLUDE_CCSPLAYERPAWNIMPL_H
#define _INCLUDE_CCSPLAYERPAWNIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayerPawn.h"
#include "schema/entity/classes/CCSPlayerPawn.h"
#include "CCSPlayerPawnBaseImpl.h"

class CCSPlayerPawnImpl : public CCSPlayerPawnBaseImpl, public ICSPlayerPawn
{

public:
    explicit CCSPlayerPawnImpl(CCSPlayerPawn* p) : CCSPlayerPawnBaseImpl(p) {}

private:
    CCSPlayerPawn* Real() { return static_cast<CCSPlayerPawn*>(m_pReal); }

public:
    CCSPlayer_BulletServices*& BulletServices() override { return Real()->m_pBulletServices(); }
    void BulletServicesUpdated() override { Real()->m_pBulletServices.NetworkStateChanged(); }
    CCSPlayer_HostageServices*& HostageServices() override { return Real()->m_pHostageServices(); }
    void HostageServicesUpdated() override { Real()->m_pHostageServices.NetworkStateChanged(); }
    CCSPlayer_BuyServices*& BuyServices() override { return Real()->m_pBuyServices(); }
    void BuyServicesUpdated() override { Real()->m_pBuyServices.NetworkStateChanged(); }
    CCSPlayer_ActionTrackingServices*& ActionTrackingServices() override { return Real()->m_pActionTrackingServices(); }
    void ActionTrackingServicesUpdated() override { Real()->m_pActionTrackingServices.NetworkStateChanged(); }
    CCSPlayer_AimPunchServices*& AimPunchServices() override { return Real()->m_pAimPunchServices(); }
    void AimPunchServicesUpdated() override { Real()->m_pAimPunchServices.NetworkStateChanged(); }
    CCSPlayer_RadioServices*& RadioServices() override { return Real()->m_pRadioServices(); }
    void RadioServicesUpdated() override { Real()->m_pRadioServices.NetworkStateChanged(); }
    CCSPlayer_DamageReactServices*& DamageReactServices() override { return Real()->m_pDamageReactServices(); }
    void DamageReactServicesUpdated() override { Real()->m_pDamageReactServices.NetworkStateChanged(); }
    uint16_t& CharacterDefIndex() override { return Real()->m_nCharacterDefIndex(); }
    void CharacterDefIndexUpdated() override { Real()->m_nCharacterDefIndex.NetworkStateChanged(); }
    bool& HasFemaleVoice() override { return Real()->m_bHasFemaleVoice(); }
    void HasFemaleVoiceUpdated() override { Real()->m_bHasFemaleVoice.NetworkStateChanged(); }
    CUtlString& StrVOPrefix() override { return Real()->m_strVOPrefix(); }
    void StrVOPrefixUpdated() override { Real()->m_strVOPrefix.NetworkStateChanged(); }
    char* LastPlaceName() override { return Real()->m_szLastPlaceName(); }
    bool& InHostageResetZone() override { return Real()->m_bInHostageResetZone(); }
    void InHostageResetZoneUpdated() override { Real()->m_bInHostageResetZone.NetworkStateChanged(); }
    bool& InBuyZone() override { return Real()->m_bInBuyZone(); }
    void InBuyZoneUpdated() override { Real()->m_bInBuyZone.NetworkStateChanged(); }
    CUtlVector<CHandle<CBaseEntity>>& TouchingBuyZones() override { return Real()->m_TouchingBuyZones(); }
    void TouchingBuyZonesUpdated() override { Real()->m_TouchingBuyZones.NetworkStateChanged(); }
    bool& WasInBuyZone() override { return Real()->m_bWasInBuyZone(); }
    void WasInBuyZoneUpdated() override { Real()->m_bWasInBuyZone.NetworkStateChanged(); }
    bool& InHostageRescueZone() override { return Real()->m_bInHostageRescueZone(); }
    void InHostageRescueZoneUpdated() override { Real()->m_bInHostageRescueZone.NetworkStateChanged(); }
    bool& InBombZone() override { return Real()->m_bInBombZone(); }
    void InBombZoneUpdated() override { Real()->m_bInBombZone.NetworkStateChanged(); }
    bool& WasInHostageRescueZone() override { return Real()->m_bWasInHostageRescueZone(); }
    void WasInHostageRescueZoneUpdated() override { Real()->m_bWasInHostageRescueZone.NetworkStateChanged(); }
    int32_t& RetakesOffering() override { return Real()->m_iRetakesOffering(); }
    void RetakesOfferingUpdated() override { Real()->m_iRetakesOffering.NetworkStateChanged(); }
    int32_t& RetakesOfferingCard() override { return Real()->m_iRetakesOfferingCard(); }
    void RetakesOfferingCardUpdated() override { Real()->m_iRetakesOfferingCard.NetworkStateChanged(); }
    bool& RetakesHasDefuseKit() override { return Real()->m_bRetakesHasDefuseKit(); }
    void RetakesHasDefuseKitUpdated() override { Real()->m_bRetakesHasDefuseKit.NetworkStateChanged(); }
    bool& RetakesMVPLastRound() override { return Real()->m_bRetakesMVPLastRound(); }
    void RetakesMVPLastRoundUpdated() override { Real()->m_bRetakesMVPLastRound.NetworkStateChanged(); }
    int32_t& RetakesMVPBoostItem() override { return Real()->m_iRetakesMVPBoostItem(); }
    void RetakesMVPBoostItemUpdated() override { Real()->m_iRetakesMVPBoostItem.NetworkStateChanged(); }
    loadout_slot_t& RetakesMVPBoostExtraUtility() override { return Real()->m_RetakesMVPBoostExtraUtility(); }
    void RetakesMVPBoostExtraUtilityUpdated() override { Real()->m_RetakesMVPBoostExtraUtility.NetworkStateChanged(); }
    float& HealthShotBoostExpirationTime() override { return Real()->m_flHealthShotBoostExpirationTime(); }
    void HealthShotBoostExpirationTimeUpdated() override { Real()->m_flHealthShotBoostExpirationTime.NetworkStateChanged(); }
    float& LandingTimeSeconds() override { return Real()->m_flLandingTimeSeconds(); }
    void LandingTimeSecondsUpdated() override { Real()->m_flLandingTimeSeconds.NetworkStateChanged(); }
    bool& IsBuyMenuOpen() override { return Real()->m_bIsBuyMenuOpen(); }
    void IsBuyMenuOpenUpdated() override { Real()->m_bIsBuyMenuOpen.NetworkStateChanged(); }
    float& LastLandTime() override { return Real()->m_lastLandTime(); }
    void LastLandTimeUpdated() override { Real()->m_lastLandTime.NetworkStateChanged(); }
    bool& OnGroundLastTick() override { return Real()->m_bOnGroundLastTick(); }
    void OnGroundLastTickUpdated() override { Real()->m_bOnGroundLastTick.NetworkStateChanged(); }
    int32_t& PlayerLocked() override { return Real()->m_iPlayerLocked(); }
    void PlayerLockedUpdated() override { Real()->m_iPlayerLocked.NetworkStateChanged(); }
    float& TimeOfLastInjury() override { return Real()->m_flTimeOfLastInjury(); }
    void TimeOfLastInjuryUpdated() override { Real()->m_flTimeOfLastInjury.NetworkStateChanged(); }
    float& NextSprayDecalTime() override { return Real()->m_flNextSprayDecalTime(); }
    void NextSprayDecalTimeUpdated() override { Real()->m_flNextSprayDecalTime.NetworkStateChanged(); }
    bool& NextSprayDecalTimeExpedited() override { return Real()->m_bNextSprayDecalTimeExpedited(); }
    void NextSprayDecalTimeExpeditedUpdated() override { Real()->m_bNextSprayDecalTimeExpedited.NetworkStateChanged(); }
    int32_t& RagdollDamageBone() override { return Real()->m_nRagdollDamageBone(); }
    void RagdollDamageBoneUpdated() override { Real()->m_nRagdollDamageBone.NetworkStateChanged(); }
    Vector& RagdollDamageForce() override { return Real()->m_vRagdollDamageForce(); }
    void RagdollDamageForceUpdated() override { Real()->m_vRagdollDamageForce.NetworkStateChanged(); }
    Vector& RagdollDamagePosition() override { return Real()->m_vRagdollDamagePosition(); }
    void RagdollDamagePositionUpdated() override { Real()->m_vRagdollDamagePosition.NetworkStateChanged(); }
    char* RagdollDamageWeaponName() override { return Real()->m_szRagdollDamageWeaponName(); }
    bool& RagdollDamageHeadshot() override { return Real()->m_bRagdollDamageHeadshot(); }
    void RagdollDamageHeadshotUpdated() override { Real()->m_bRagdollDamageHeadshot.NetworkStateChanged(); }
    Vector& RagdollServerOrigin() override { return Real()->m_vRagdollServerOrigin(); }
    void RagdollServerOriginUpdated() override { Real()->m_vRagdollServerOrigin.NetworkStateChanged(); }
    CEconItemView& EconGloves() override { return Real()->m_EconGloves(); }
    void EconGlovesUpdated() override { Real()->m_EconGloves.NetworkStateChanged(); }
    uint8_t& EconGlovesChanged() override { return Real()->m_nEconGlovesChanged(); }
    void EconGlovesChangedUpdated() override { Real()->m_nEconGlovesChanged.NetworkStateChanged(); }
    QAngle& DeathEyeAngles() override { return Real()->m_qDeathEyeAngles(); }
    void DeathEyeAnglesUpdated() override { Real()->m_qDeathEyeAngles.NetworkStateChanged(); }
    bool& LeftHanded() override { return Real()->m_bLeftHanded(); }
    void LeftHandedUpdated() override { Real()->m_bLeftHanded.NetworkStateChanged(); }
    float& SwitchedHandednessTime() override { return Real()->m_fSwitchedHandednessTime(); }
    void SwitchedHandednessTimeUpdated() override { Real()->m_fSwitchedHandednessTime.NetworkStateChanged(); }
    float& ViewmodelOffsetX() override { return Real()->m_flViewmodelOffsetX(); }
    void ViewmodelOffsetXUpdated() override { Real()->m_flViewmodelOffsetX.NetworkStateChanged(); }
    float& ViewmodelOffsetY() override { return Real()->m_flViewmodelOffsetY(); }
    void ViewmodelOffsetYUpdated() override { Real()->m_flViewmodelOffsetY.NetworkStateChanged(); }
    float& ViewmodelOffsetZ() override { return Real()->m_flViewmodelOffsetZ(); }
    void ViewmodelOffsetZUpdated() override { Real()->m_flViewmodelOffsetZ.NetworkStateChanged(); }
    float& ViewmodelFOV() override { return Real()->m_flViewmodelFOV(); }
    void ViewmodelFOVUpdated() override { Real()->m_flViewmodelFOV.NetworkStateChanged(); }
    bool& IsWalking() override { return Real()->m_bIsWalking(); }
    void IsWalkingUpdated() override { Real()->m_bIsWalking.NetworkStateChanged(); }
    float& LastGivenDefuserTime() override { return Real()->m_fLastGivenDefuserTime(); }
    void LastGivenDefuserTimeUpdated() override { Real()->m_fLastGivenDefuserTime.NetworkStateChanged(); }
    float& LastGivenBombTime() override { return Real()->m_fLastGivenBombTime(); }
    void LastGivenBombTimeUpdated() override { Real()->m_fLastGivenBombTime.NetworkStateChanged(); }
    float& DealtDamageToEnemyMostRecentTimestamp() override { return Real()->m_flDealtDamageToEnemyMostRecentTimestamp(); }
    void DealtDamageToEnemyMostRecentTimestampUpdated() override { Real()->m_flDealtDamageToEnemyMostRecentTimestamp.NetworkStateChanged(); }
    uint32_t& DisplayHistoryBits() override { return Real()->m_iDisplayHistoryBits(); }
    void DisplayHistoryBitsUpdated() override { Real()->m_iDisplayHistoryBits.NetworkStateChanged(); }
    float& LastAttackedTeammate() override { return Real()->m_flLastAttackedTeammate(); }
    void LastAttackedTeammateUpdated() override { Real()->m_flLastAttackedTeammate.NetworkStateChanged(); }
    float& AllowAutoFollowTime() override { return Real()->m_allowAutoFollowTime(); }
    void AllowAutoFollowTimeUpdated() override { Real()->m_allowAutoFollowTime.NetworkStateChanged(); }
    bool& ResetArmorNextSpawn() override { return Real()->m_bResetArmorNextSpawn(); }
    void ResetArmorNextSpawnUpdated() override { Real()->m_bResetArmorNextSpawn.NetworkStateChanged(); }
    CEntityIndex& LastKillerIndex() override { return Real()->m_nLastKillerIndex(); }
    void LastKillerIndexUpdated() override { Real()->m_nLastKillerIndex.NetworkStateChanged(); }
    EntitySpottedState_t& EntitySpottedState() override { return Real()->m_entitySpottedState(); }
    void EntitySpottedStateUpdated() override { Real()->m_entitySpottedState.NetworkStateChanged(); }
    int32_t& SpotRules() override { return Real()->m_nSpotRules(); }
    void SpotRulesUpdated() override { Real()->m_nSpotRules.NetworkStateChanged(); }
    bool& IsScoped() override { return Real()->m_bIsScoped(); }
    void IsScopedUpdated() override { Real()->m_bIsScoped.NetworkStateChanged(); }
    bool& ResumeZoom() override { return Real()->m_bResumeZoom(); }
    void ResumeZoomUpdated() override { Real()->m_bResumeZoom.NetworkStateChanged(); }
    bool& IsDefusing() override { return Real()->m_bIsDefusing(); }
    void IsDefusingUpdated() override { Real()->m_bIsDefusing.NetworkStateChanged(); }
    bool& IsGrabbingHostage() override { return Real()->m_bIsGrabbingHostage(); }
    void IsGrabbingHostageUpdated() override { Real()->m_bIsGrabbingHostage.NetworkStateChanged(); }
    CSPlayerBlockingUseAction_t& BlockingUseActionInProgress() override { return Real()->m_iBlockingUseActionInProgress(); }
    void BlockingUseActionInProgressUpdated() override { Real()->m_iBlockingUseActionInProgress.NetworkStateChanged(); }
    float& EmitSoundTime() override { return Real()->m_flEmitSoundTime(); }
    void EmitSoundTimeUpdated() override { Real()->m_flEmitSoundTime.NetworkStateChanged(); }
    bool& InNoDefuseArea() override { return Real()->m_bInNoDefuseArea(); }
    void InNoDefuseAreaUpdated() override { Real()->m_bInNoDefuseArea.NetworkStateChanged(); }
    CEntityIndex& BombSiteIndex() override { return Real()->m_iBombSiteIndex(); }
    void BombSiteIndexUpdated() override { Real()->m_iBombSiteIndex.NetworkStateChanged(); }
    int32_t& WhichBombZone() override { return Real()->m_nWhichBombZone(); }
    void WhichBombZoneUpdated() override { Real()->m_nWhichBombZone.NetworkStateChanged(); }
    bool& InBombZoneTrigger() override { return Real()->m_bInBombZoneTrigger(); }
    void InBombZoneTriggerUpdated() override { Real()->m_bInBombZoneTrigger.NetworkStateChanged(); }
    bool& WasInBombZoneTrigger() override { return Real()->m_bWasInBombZoneTrigger(); }
    void WasInBombZoneTriggerUpdated() override { Real()->m_bWasInBombZoneTrigger.NetworkStateChanged(); }
    int32_t& ShotsFired() override { return Real()->m_iShotsFired(); }
    void ShotsFiredUpdated() override { Real()->m_iShotsFired.NetworkStateChanged(); }
    float& FlinchStack() override { return Real()->m_flFlinchStack(); }
    void FlinchStackUpdated() override { Real()->m_flFlinchStack.NetworkStateChanged(); }
    float& VelocityModifier() override { return Real()->m_flVelocityModifier(); }
    void VelocityModifierUpdated() override { Real()->m_flVelocityModifier.NetworkStateChanged(); }
    Vector& TotalBulletForce() override { return Real()->m_vecTotalBulletForce(); }
    void TotalBulletForceUpdated() override { Real()->m_vecTotalBulletForce.NetworkStateChanged(); }
    bool& WaitForNoAttack() override { return Real()->m_bWaitForNoAttack(); }
    void WaitForNoAttackUpdated() override { Real()->m_bWaitForNoAttack.NetworkStateChanged(); }
    float& IgnoreLadderJumpTime() override { return Real()->m_ignoreLadderJumpTime(); }
    void IgnoreLadderJumpTimeUpdated() override { Real()->m_ignoreLadderJumpTime.NetworkStateChanged(); }
    bool& KilledByHeadshot() override { return Real()->m_bKilledByHeadshot(); }
    void KilledByHeadshotUpdated() override { Real()->m_bKilledByHeadshot.NetworkStateChanged(); }
    int32_t& LastHitBox() override { return Real()->m_LastHitBox(); }
    void LastHitBoxUpdated() override { Real()->m_LastHitBox.NetworkStateChanged(); }
    CCSBot*& Bot() override { return Real()->m_pBot(); }
    void BotUpdated() override { Real()->m_pBot.NetworkStateChanged(); }
    bool& BotAllowActive() override { return Real()->m_bBotAllowActive(); }
    void BotAllowActiveUpdated() override { Real()->m_bBotAllowActive.NetworkStateChanged(); }
    int32_t& LastPickupPriority() override { return Real()->m_nLastPickupPriority(); }
    void LastPickupPriorityUpdated() override { Real()->m_nLastPickupPriority.NetworkStateChanged(); }
    float& LastPickupPriorityTime() override { return Real()->m_flLastPickupPriorityTime(); }
    void LastPickupPriorityTimeUpdated() override { Real()->m_flLastPickupPriorityTime.NetworkStateChanged(); }
    int32_t& ArmorValue() override { return Real()->m_ArmorValue(); }
    void ArmorValueUpdated() override { Real()->m_ArmorValue.NetworkStateChanged(); }
    uint16_t& CurrentEquipmentValue() override { return Real()->m_unCurrentEquipmentValue(); }
    void CurrentEquipmentValueUpdated() override { Real()->m_unCurrentEquipmentValue.NetworkStateChanged(); }
    uint16_t& RoundStartEquipmentValue() override { return Real()->m_unRoundStartEquipmentValue(); }
    void RoundStartEquipmentValueUpdated() override { Real()->m_unRoundStartEquipmentValue.NetworkStateChanged(); }
    uint16_t& FreezetimeEndEquipmentValue() override { return Real()->m_unFreezetimeEndEquipmentValue(); }
    void FreezetimeEndEquipmentValueUpdated() override { Real()->m_unFreezetimeEndEquipmentValue.NetworkStateChanged(); }
    int32_t& LastWeaponFireUsercmd() override { return Real()->m_iLastWeaponFireUsercmd(); }
    void LastWeaponFireUsercmdUpdated() override { Real()->m_iLastWeaponFireUsercmd.NetworkStateChanged(); }
    bool& IsSpawning() override { return Real()->m_bIsSpawning(); }
    void IsSpawningUpdated() override { Real()->m_bIsSpawning.NetworkStateChanged(); }
    int32_t& DeathFlags() override { return Real()->m_iDeathFlags(); }
    void DeathFlagsUpdated() override { Real()->m_iDeathFlags.NetworkStateChanged(); }
    bool& HasDeathInfo() override { return Real()->m_bHasDeathInfo(); }
    void HasDeathInfoUpdated() override { Real()->m_bHasDeathInfo.NetworkStateChanged(); }
    float& DeathInfoTime() override { return Real()->m_flDeathInfoTime(); }
    void DeathInfoTimeUpdated() override { Real()->m_flDeathInfoTime.NetworkStateChanged(); }
    Vector& DeathInfoOrigin() override { return Real()->m_vecDeathInfoOrigin(); }
    void DeathInfoOriginUpdated() override { Real()->m_vecDeathInfoOrigin.NetworkStateChanged(); }
    uint32_t* PlayerPatchEconIndices() override { return Real()->m_vecPlayerPatchEconIndices(); }
    Color& GunGameImmunityColor() override { return Real()->m_GunGameImmunityColor(); }
    void GunGameImmunityColorUpdated() override { Real()->m_GunGameImmunityColor.NetworkStateChanged(); }
    float& GrenadeParameterStashTime() override { return Real()->m_grenadeParameterStashTime(); }
    void GrenadeParameterStashTimeUpdated() override { Real()->m_grenadeParameterStashTime.NetworkStateChanged(); }
    bool& GrenadeParametersStashed() override { return Real()->m_bGrenadeParametersStashed(); }
    void GrenadeParametersStashedUpdated() override { Real()->m_bGrenadeParametersStashed.NetworkStateChanged(); }
    QAngle& StashedShootAngles() override { return Real()->m_angStashedShootAngles(); }
    void StashedShootAnglesUpdated() override { Real()->m_angStashedShootAngles.NetworkStateChanged(); }
    Vector& StashedGrenadeThrowPosition() override { return Real()->m_vecStashedGrenadeThrowPosition(); }
    void StashedGrenadeThrowPositionUpdated() override { Real()->m_vecStashedGrenadeThrowPosition.NetworkStateChanged(); }
    Vector& StashedVelocity() override { return Real()->m_vecStashedVelocity(); }
    void StashedVelocityUpdated() override { Real()->m_vecStashedVelocity.NetworkStateChanged(); }
    QAngle* ShootAngleHistory() override { return Real()->m_angShootAngleHistory(); }
    Vector* ThrowPositionHistory() override { return Real()->m_vecThrowPositionHistory(); }
    Vector* VelocityHistory() override { return Real()->m_vecVelocityHistory(); }
    bool& CommittingSuicideOnTeamChange() override { return Real()->m_bCommittingSuicideOnTeamChange(); }
    void CommittingSuicideOnTeamChangeUpdated() override { Real()->m_bCommittingSuicideOnTeamChange.NetworkStateChanged(); }
    bool& WasNotKilledNaturally() override { return Real()->m_wasNotKilledNaturally(); }
    void WasNotKilledNaturallyUpdated() override { Real()->m_wasNotKilledNaturally.NetworkStateChanged(); }
    float& ImmuneToGunGameDamageTime() override { return Real()->m_fImmuneToGunGameDamageTime(); }
    void ImmuneToGunGameDamageTimeUpdated() override { Real()->m_fImmuneToGunGameDamageTime.NetworkStateChanged(); }
    bool& GunGameImmunity() override { return Real()->m_bGunGameImmunity(); }
    void GunGameImmunityUpdated() override { Real()->m_bGunGameImmunity.NetworkStateChanged(); }
    float& MolotovDamageTime() override { return Real()->m_fMolotovDamageTime(); }
    void MolotovDamageTimeUpdated() override { Real()->m_fMolotovDamageTime.NetworkStateChanged(); }
    QAngle& EyeAngles() override { return Real()->m_angEyeAngles(); }
    void EyeAnglesUpdated() override { Real()->m_angEyeAngles.NetworkStateChanged(); }
};

#endif // _INCLUDE_CCSPLAYERPAWNIMPL_H
