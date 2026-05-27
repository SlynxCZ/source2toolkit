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

#ifndef _INCLUDE_CBASEPLAYERWEAPONVDATAIMPL_H
#define _INCLUDE_CBASEPLAYERWEAPONVDATAIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBasePlayerWeaponVData.h"
#include "schema/entity/classes/CBasePlayerWeaponVData.h"
#include "CEntitySubclassVDataBaseImpl.h"

class CBasePlayerWeaponVDataImpl : public CEntitySubclassVDataBaseImpl, public IBasePlayerWeaponVData
{

public:
    explicit CBasePlayerWeaponVDataImpl(CBasePlayerWeaponVData* p) : CEntitySubclassVDataBaseImpl(p) {}

private:
    CBasePlayerWeaponVData* Real() { return static_cast<CBasePlayerWeaponVData*>(m_pReal); }

public:
    bool& BuiltRightHanded() override { return Real()->m_bBuiltRightHanded(); }
    void BuiltRightHandedUpdated() override { Real()->m_bBuiltRightHanded.NetworkStateChanged(); }
    bool& AllowFlipping() override { return Real()->m_bAllowFlipping(); }
    void AllowFlippingUpdated() override { Real()->m_bAllowFlipping.NetworkStateChanged(); }
    CUtlString& MuzzleFlashParticleConfig() override { return Real()->m_szMuzzleFlashParticleConfig(); }
    void MuzzleFlashParticleConfigUpdated() override { Real()->m_szMuzzleFlashParticleConfig.NetworkStateChanged(); }
    uint8_t& MuzzleSmokeShotThreshold() override { return Real()->m_nMuzzleSmokeShotThreshold(); }
    void MuzzleSmokeShotThresholdUpdated() override { Real()->m_nMuzzleSmokeShotThreshold.NetworkStateChanged(); }
    float& MuzzleSmokeTimeout() override { return Real()->m_flMuzzleSmokeTimeout(); }
    void MuzzleSmokeTimeoutUpdated() override { Real()->m_flMuzzleSmokeTimeout.NetworkStateChanged(); }
    float& MuzzleSmokeDecrementRate() override { return Real()->m_flMuzzleSmokeDecrementRate(); }
    void MuzzleSmokeDecrementRateUpdated() override { Real()->m_flMuzzleSmokeDecrementRate.NetworkStateChanged(); }
    bool& GenerateMuzzleLight() override { return Real()->m_bGenerateMuzzleLight(); }
    void GenerateMuzzleLightUpdated() override { Real()->m_bGenerateMuzzleLight.NetworkStateChanged(); }
    bool& LinkedCooldowns() override { return Real()->m_bLinkedCooldowns(); }
    void LinkedCooldownsUpdated() override { Real()->m_bLinkedCooldowns.NetworkStateChanged(); }
    ItemFlagTypes_t& Flags() override { return Real()->m_iFlags(); }
    void FlagsUpdated() override { Real()->m_iFlags.NetworkStateChanged(); }
    int32_t& Weight() override { return Real()->m_iWeight(); }
    void WeightUpdated() override { Real()->m_iWeight.NetworkStateChanged(); }
    bool& AutoSwitchTo() override { return Real()->m_bAutoSwitchTo(); }
    void AutoSwitchToUpdated() override { Real()->m_bAutoSwitchTo.NetworkStateChanged(); }
    bool& AutoSwitchFrom() override { return Real()->m_bAutoSwitchFrom(); }
    void AutoSwitchFromUpdated() override { Real()->m_bAutoSwitchFrom.NetworkStateChanged(); }
    uint8_t& PrimaryAmmoType() override { return Real()->m_nPrimaryAmmoType(); }
    void PrimaryAmmoTypeUpdated() override { Real()->m_nPrimaryAmmoType.NetworkStateChanged(); }
    uint8_t& SecondaryAmmoType() override { return Real()->m_nSecondaryAmmoType(); }
    void SecondaryAmmoTypeUpdated() override { Real()->m_nSecondaryAmmoType.NetworkStateChanged(); }
    int32_t& MaxClip1() override { return Real()->m_iMaxClip1(); }
    void MaxClip1Updated() override { Real()->m_iMaxClip1.NetworkStateChanged(); }
    int32_t& MaxClip2() override { return Real()->m_iMaxClip2(); }
    void MaxClip2Updated() override { Real()->m_iMaxClip2.NetworkStateChanged(); }
    int32_t& DefaultClip1() override { return Real()->m_iDefaultClip1(); }
    void DefaultClip1Updated() override { Real()->m_iDefaultClip1.NetworkStateChanged(); }
    int32_t& DefaultClip2() override { return Real()->m_iDefaultClip2(); }
    void DefaultClip2Updated() override { Real()->m_iDefaultClip2.NetworkStateChanged(); }
    bool& ReserveAmmoAsClips() override { return Real()->m_bReserveAmmoAsClips(); }
    void ReserveAmmoAsClipsUpdated() override { Real()->m_bReserveAmmoAsClips.NetworkStateChanged(); }
    bool& TreatAsSingleClip() override { return Real()->m_bTreatAsSingleClip(); }
    void TreatAsSingleClipUpdated() override { Real()->m_bTreatAsSingleClip.NetworkStateChanged(); }
    bool& KeepLoadedAmmo() override { return Real()->m_bKeepLoadedAmmo(); }
    void KeepLoadedAmmoUpdated() override { Real()->m_bKeepLoadedAmmo.NetworkStateChanged(); }
    RumbleEffect_t& RumbleEffect() override { return Real()->m_iRumbleEffect(); }
    void RumbleEffectUpdated() override { Real()->m_iRumbleEffect.NetworkStateChanged(); }
    float& DropSpeed() override { return Real()->m_flDropSpeed(); }
    void DropSpeedUpdated() override { Real()->m_flDropSpeed.NetworkStateChanged(); }
    int32_t& Slot() override { return Real()->m_iSlot(); }
    void SlotUpdated() override { Real()->m_iSlot.NetworkStateChanged(); }
    int32_t& Position() override { return Real()->m_iPosition(); }
    void PositionUpdated() override { Real()->m_iPosition.NetworkStateChanged(); }
};

#endif // _INCLUDE_CBASEPLAYERWEAPONVDATAIMPL_H
