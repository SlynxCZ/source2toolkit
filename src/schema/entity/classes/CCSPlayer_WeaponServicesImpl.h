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

#ifndef _INCLUDE_CCSPLAYER_WEAPONSERVICESIMPL_H
#define _INCLUDE_CCSPLAYER_WEAPONSERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayer_WeaponServices.h"
#include "schema/entity/classes/CCSPlayer_WeaponServices.h"
#include "CPlayer_WeaponServicesImpl.h"

class CCSPlayer_WeaponServicesImpl : public CPlayer_WeaponServicesImpl, public virtual ICSPlayer_WeaponServices
{

public:
    explicit CCSPlayer_WeaponServicesImpl(CCSPlayer_WeaponServices* p) : CPlayer_WeaponServicesImpl(p) {}

private:
    CCSPlayer_WeaponServices* Real() { return static_cast<CCSPlayer_WeaponServices*>(m_pReal); }
    CCSPlayer_WeaponServices* Real() const { return static_cast<CCSPlayer_WeaponServices*>(m_pReal); }

public:
    CCSPlayer_WeaponServices* GetOriginal() const override { return Real(); }
    float& NextAttack() override { return Real()->m_flNextAttack(); }
    void NextAttackUpdated() override { Real()->m_flNextAttack.NetworkStateChanged(); }
    CHandle<CBasePlayerWeapon>& SavedWeapon() override { return Real()->m_hSavedWeapon(); }
    void SavedWeaponUpdated() override { Real()->m_hSavedWeapon.NetworkStateChanged(); }
    int32_t& TimeToMelee() override { return Real()->m_nTimeToMelee(); }
    void TimeToMeleeUpdated() override { Real()->m_nTimeToMelee.NetworkStateChanged(); }
    int32_t& TimeToSecondary() override { return Real()->m_nTimeToSecondary(); }
    void TimeToSecondaryUpdated() override { Real()->m_nTimeToSecondary.NetworkStateChanged(); }
    int32_t& TimeToPrimary() override { return Real()->m_nTimeToPrimary(); }
    void TimeToPrimaryUpdated() override { Real()->m_nTimeToPrimary.NetworkStateChanged(); }
    int32_t& TimeToSniperRifle() override { return Real()->m_nTimeToSniperRifle(); }
    void TimeToSniperRifleUpdated() override { Real()->m_nTimeToSniperRifle.NetworkStateChanged(); }
    bool& IsBeingGivenItem() override { return Real()->m_bIsBeingGivenItem(); }
    void IsBeingGivenItemUpdated() override { Real()->m_bIsBeingGivenItem.NetworkStateChanged(); }
    bool& IsPickingUpItemWithUse() override { return Real()->m_bIsPickingUpItemWithUse(); }
    void IsPickingUpItemWithUseUpdated() override { Real()->m_bIsPickingUpItemWithUse.NetworkStateChanged(); }
    bool& PickedUpWeapon() override { return Real()->m_bPickedUpWeapon(); }
    void PickedUpWeaponUpdated() override { Real()->m_bPickedUpWeapon.NetworkStateChanged(); }
    bool& DisableAutoDeploy() override { return Real()->m_bDisableAutoDeploy(); }
    void DisableAutoDeployUpdated() override { Real()->m_bDisableAutoDeploy.NetworkStateChanged(); }
    bool& IsPickingUpGroundWeapon() override { return Real()->m_bIsPickingUpGroundWeapon(); }
    void IsPickingUpGroundWeaponUpdated() override { Real()->m_bIsPickingUpGroundWeapon.NetworkStateChanged(); }
    CUtlVector<uint8_t>& NetworkAnimTiming() override { return Real()->m_networkAnimTiming(); }
    void NetworkAnimTimingUpdated() override { Real()->m_networkAnimTiming.NetworkStateChanged(); }
    bool& BlockInspectUntilNextGraphUpdate() override { return Real()->m_bBlockInspectUntilNextGraphUpdate(); }
    void BlockInspectUntilNextGraphUpdateUpdated() override { Real()->m_bBlockInspectUntilNextGraphUpdate.NetworkStateChanged(); }

    void DropWeapon(IBasePlayerWeapon *pWeapon, Vector *pVecTarget, Vector *pVelocity) override { Real()->DropWeapon(pWeapon, pVecTarget, pVelocity); }
    void SelectWeapon(IBasePlayerWeapon *pWeapon, int unk1) override { Real()->SelectWeapon(pWeapon, unk1); }
};

#endif // _INCLUDE_CCSPLAYER_WEAPONSERVICESIMPL_H
