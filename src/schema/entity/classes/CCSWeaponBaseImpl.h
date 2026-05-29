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

#ifndef _INCLUDE_CCSWEAPONBASEIMPL_H
#define _INCLUDE_CCSWEAPONBASEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSWeaponBase.h"
#include "schema/entity/classes/CCSWeaponBase.h"
#include "CBasePlayerWeaponImpl.h"

class CCSWeaponBaseImpl : public CBasePlayerWeaponImpl, public ICSWeaponBase
{

public:
    explicit CCSWeaponBaseImpl(CCSWeaponBase* p) : CBasePlayerWeaponImpl(p) {}

private:
    CCSWeaponBase* Real() { return static_cast<CCSWeaponBase*>(m_pReal); }
    CCSWeaponBase* Real() const { return static_cast<CCSWeaponBase*>(m_pReal); }

public:
    CCSWeaponBase* GetOriginal() const override { return Real(); }
    bool& Removeable() override { return Real()->m_bRemoveable(); }
    void RemoveableUpdated() override { Real()->m_bRemoveable.NetworkStateChanged(); }
    bool& PlayerAmmoStockOnPickup() override { return Real()->m_bPlayerAmmoStockOnPickup(); }
    void PlayerAmmoStockOnPickupUpdated() override { Real()->m_bPlayerAmmoStockOnPickup.NetworkStateChanged(); }
    bool& RequireUseToTouch() override { return Real()->m_bRequireUseToTouch(); }
    void RequireUseToTouchUpdated() override { Real()->m_bRequireUseToTouch.NetworkStateChanged(); }
    ::WeaponGameplayAnimState& WeaponGameplayAnimState() override { return Real()->m_iWeaponGameplayAnimState(); }
    void WeaponGameplayAnimStateUpdated() override { Real()->m_iWeaponGameplayAnimState.NetworkStateChanged(); }
    float& WeaponGameplayAnimStateTimestamp() override { return Real()->m_flWeaponGameplayAnimStateTimestamp(); }
    void WeaponGameplayAnimStateTimestampUpdated() override { Real()->m_flWeaponGameplayAnimStateTimestamp.NetworkStateChanged(); }
    float& InspectCancelCompleteTime() override { return Real()->m_flInspectCancelCompleteTime(); }
    void InspectCancelCompleteTimeUpdated() override { Real()->m_flInspectCancelCompleteTime.NetworkStateChanged(); }
    bool& InspectPending() override { return Real()->m_bInspectPending(); }
    void InspectPendingUpdated() override { Real()->m_bInspectPending.NetworkStateChanged(); }
    bool& InspectShouldLoop() override { return Real()->m_bInspectShouldLoop(); }
    void InspectShouldLoopUpdated() override { Real()->m_bInspectShouldLoop.NetworkStateChanged(); }
    int32_t& LastEmptySoundCmdNum() override { return Real()->m_nLastEmptySoundCmdNum(); }
    void LastEmptySoundCmdNumUpdated() override { Real()->m_nLastEmptySoundCmdNum.NetworkStateChanged(); }
    bool& FireOnEmpty() override { return Real()->m_bFireOnEmpty(); }
    void FireOnEmptyUpdated() override { Real()->m_bFireOnEmpty.NetworkStateChanged(); }
    ::CEntityIOOutput& OnPlayerPickup() override { return Real()->m_OnPlayerPickup(); }
    void OnPlayerPickupUpdated() override { Real()->m_OnPlayerPickup.NetworkStateChanged(); }
    ::CSWeaponMode& WeaponMode() override { return Real()->m_weaponMode(); }
    void WeaponModeUpdated() override { Real()->m_weaponMode.NetworkStateChanged(); }
    float& TurningInaccuracyDelta() override { return Real()->m_flTurningInaccuracyDelta(); }
    void TurningInaccuracyDeltaUpdated() override { Real()->m_flTurningInaccuracyDelta.NetworkStateChanged(); }
    Vector& TurningInaccuracyEyeDirLast() override { return Real()->m_vecTurningInaccuracyEyeDirLast(); }
    void TurningInaccuracyEyeDirLastUpdated() override { Real()->m_vecTurningInaccuracyEyeDirLast.NetworkStateChanged(); }
    float& TurningInaccuracy() override { return Real()->m_flTurningInaccuracy(); }
    void TurningInaccuracyUpdated() override { Real()->m_flTurningInaccuracy.NetworkStateChanged(); }
    float& AccuracyPenalty() override { return Real()->m_fAccuracyPenalty(); }
    void AccuracyPenaltyUpdated() override { Real()->m_fAccuracyPenalty.NetworkStateChanged(); }
    float& LastAccuracyUpdateTime() override { return Real()->m_flLastAccuracyUpdateTime(); }
    void LastAccuracyUpdateTimeUpdated() override { Real()->m_flLastAccuracyUpdateTime.NetworkStateChanged(); }
    float& AccuracySmoothedForZoom() override { return Real()->m_fAccuracySmoothedForZoom(); }
    void AccuracySmoothedForZoomUpdated() override { Real()->m_fAccuracySmoothedForZoom.NetworkStateChanged(); }
    int32_t& RecoilIndex() override { return Real()->m_iRecoilIndex(); }
    void RecoilIndexUpdated() override { Real()->m_iRecoilIndex.NetworkStateChanged(); }
    float& RecoilIndex() override { return Real()->m_flRecoilIndex(); }
    void RecoilIndexUpdated() override { Real()->m_flRecoilIndex.NetworkStateChanged(); }
    bool& BurstMode() override { return Real()->m_bBurstMode(); }
    void BurstModeUpdated() override { Real()->m_bBurstMode.NetworkStateChanged(); }
    int32_t& PostponeFireReadyTicks() override { return Real()->m_nPostponeFireReadyTicks(); }
    void PostponeFireReadyTicksUpdated() override { Real()->m_nPostponeFireReadyTicks.NetworkStateChanged(); }
    float& PostponeFireReadyFrac() override { return Real()->m_flPostponeFireReadyFrac(); }
    void PostponeFireReadyFracUpdated() override { Real()->m_flPostponeFireReadyFrac.NetworkStateChanged(); }
    bool& InReload() override { return Real()->m_bInReload(); }
    void InReloadUpdated() override { Real()->m_bInReload.NetworkStateChanged(); }
    int32_t& DeployTick() override { return Real()->m_nDeployTick(); }
    void DeployTickUpdated() override { Real()->m_nDeployTick.NetworkStateChanged(); }
    float& DroppedAtTime() override { return Real()->m_flDroppedAtTime(); }
    void DroppedAtTimeUpdated() override { Real()->m_flDroppedAtTime.NetworkStateChanged(); }
    bool& IsHauledBack() override { return Real()->m_bIsHauledBack(); }
    void IsHauledBackUpdated() override { Real()->m_bIsHauledBack.NetworkStateChanged(); }
    bool& SilencerOn() override { return Real()->m_bSilencerOn(); }
    void SilencerOnUpdated() override { Real()->m_bSilencerOn.NetworkStateChanged(); }
    float& TimeSilencerSwitchComplete() override { return Real()->m_flTimeSilencerSwitchComplete(); }
    void TimeSilencerSwitchCompleteUpdated() override { Real()->m_flTimeSilencerSwitchComplete.NetworkStateChanged(); }
    float& WeaponActionPlaybackRate() override { return Real()->m_flWeaponActionPlaybackRate(); }
    void WeaponActionPlaybackRateUpdated() override { Real()->m_flWeaponActionPlaybackRate.NetworkStateChanged(); }
    int32_t& OriginalTeamNumber() override { return Real()->m_iOriginalTeamNumber(); }
    void OriginalTeamNumberUpdated() override { Real()->m_iOriginalTeamNumber.NetworkStateChanged(); }
    int32_t& MostRecentTeamNumber() override { return Real()->m_iMostRecentTeamNumber(); }
    void MostRecentTeamNumberUpdated() override { Real()->m_iMostRecentTeamNumber.NetworkStateChanged(); }
    bool& DroppedNearBuyZone() override { return Real()->m_bDroppedNearBuyZone(); }
    void DroppedNearBuyZoneUpdated() override { Real()->m_bDroppedNearBuyZone.NetworkStateChanged(); }
    float& NextAttackRenderTimeOffset() override { return Real()->m_flNextAttackRenderTimeOffset(); }
    void NextAttackRenderTimeOffsetUpdated() override { Real()->m_flNextAttackRenderTimeOffset.NetworkStateChanged(); }
    bool& CanBePickedUp() override { return Real()->m_bCanBePickedUp(); }
    void CanBePickedUpUpdated() override { Real()->m_bCanBePickedUp.NetworkStateChanged(); }
    bool& UseCanOverrideNextOwnerTouchTime() override { return Real()->m_bUseCanOverrideNextOwnerTouchTime(); }
    void UseCanOverrideNextOwnerTouchTimeUpdated() override { Real()->m_bUseCanOverrideNextOwnerTouchTime.NetworkStateChanged(); }
    float& NextOwnerTouchTime() override { return Real()->m_nextOwnerTouchTime(); }
    void NextOwnerTouchTimeUpdated() override { Real()->m_nextOwnerTouchTime.NetworkStateChanged(); }
    float& NextPrevOwnerTouchTime() override { return Real()->m_nextPrevOwnerTouchTime(); }
    void NextPrevOwnerTouchTimeUpdated() override { Real()->m_nextPrevOwnerTouchTime.NetworkStateChanged(); }
    float& NextPrevOwnerUseTime() override { return Real()->m_nextPrevOwnerUseTime(); }
    void NextPrevOwnerUseTimeUpdated() override { Real()->m_nextPrevOwnerUseTime.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& PrevOwner() override { return Real()->m_hPrevOwner(); }
    void PrevOwnerUpdated() override { Real()->m_hPrevOwner.NetworkStateChanged(); }
    int32_t& DropTick() override { return Real()->m_nDropTick(); }
    void DropTickUpdated() override { Real()->m_nDropTick.NetworkStateChanged(); }
    bool& WasActiveWeaponWhenDropped() override { return Real()->m_bWasActiveWeaponWhenDropped(); }
    void WasActiveWeaponWhenDroppedUpdated() override { Real()->m_bWasActiveWeaponWhenDropped.NetworkStateChanged(); }
    bool& Donated() override { return Real()->m_donated(); }
    void DonatedUpdated() override { Real()->m_donated.NetworkStateChanged(); }
    float& LastShotTime() override { return Real()->m_fLastShotTime(); }
    void LastShotTimeUpdated() override { Real()->m_fLastShotTime.NetworkStateChanged(); }
    bool& WasOwnedByCT() override { return Real()->m_bWasOwnedByCT(); }
    void WasOwnedByCTUpdated() override { Real()->m_bWasOwnedByCT.NetworkStateChanged(); }
    bool& WasOwnedByTerrorist() override { return Real()->m_bWasOwnedByTerrorist(); }
    void WasOwnedByTerroristUpdated() override { Real()->m_bWasOwnedByTerrorist.NetworkStateChanged(); }
    int32_t& NumRemoveUnownedWeaponThink() override { return Real()->m_numRemoveUnownedWeaponThink(); }
    void NumRemoveUnownedWeaponThinkUpdated() override { Real()->m_numRemoveUnownedWeaponThink.NetworkStateChanged(); }
    ::CIronSightController& IronSightController() override { return Real()->m_IronSightController(); }
    void IronSightControllerUpdated() override { Real()->m_IronSightController.NetworkStateChanged(); }
    int32_t& IronSightMode() override { return Real()->m_iIronSightMode(); }
    void IronSightModeUpdated() override { Real()->m_iIronSightMode.NetworkStateChanged(); }
    float& LastLOSTraceFailureTime() override { return Real()->m_flLastLOSTraceFailureTime(); }
    void LastLOSTraceFailureTimeUpdated() override { Real()->m_flLastLOSTraceFailureTime.NetworkStateChanged(); }
    float& WatTickOffset() override { return Real()->m_flWatTickOffset(); }
    void WatTickOffsetUpdated() override { Real()->m_flWatTickOffset.NetworkStateChanged(); }
    float& LastShakeTime() override { return Real()->m_flLastShakeTime(); }
    void LastShakeTimeUpdated() override { Real()->m_flLastShakeTime.NetworkStateChanged(); }
};

inline ICSWeaponBase* CCSWeaponBase::ToInterface() { return new CCSWeaponBaseImpl(this); }
inline ICSWeaponBase* ICSWeaponBase::FromOriginal(CCSWeaponBase* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSWEAPONBASEIMPL_H
