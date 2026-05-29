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

#ifndef _INCLUDE_CBASEPLAYERWEAPONIMPL_H
#define _INCLUDE_CBASEPLAYERWEAPONIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBasePlayerWeapon.h"
#include "schema/entity/classes/CBasePlayerWeapon.h"
#include "CEconEntityImpl.h"

class CBasePlayerWeaponImpl : public CEconEntityImpl, public IBasePlayerWeapon
{

public:
    explicit CBasePlayerWeaponImpl(CBasePlayerWeapon* p) : CEconEntityImpl(p) {}

private:
    CBasePlayerWeapon* Real() { return static_cast<CBasePlayerWeapon*>(m_pReal); }
    CBasePlayerWeapon* Real() const { return static_cast<CBasePlayerWeapon*>(m_pReal); }

public:
    CBasePlayerWeapon* GetOriginal() const override { return Real(); }
    int32_t& NextPrimaryAttackTick() override { return Real()->m_nNextPrimaryAttackTick(); }
    void NextPrimaryAttackTickUpdated() override { Real()->m_nNextPrimaryAttackTick.NetworkStateChanged(); }
    float& NextPrimaryAttackTickRatio() override { return Real()->m_flNextPrimaryAttackTickRatio(); }
    void NextPrimaryAttackTickRatioUpdated() override { Real()->m_flNextPrimaryAttackTickRatio.NetworkStateChanged(); }
    int32_t& NextSecondaryAttackTick() override { return Real()->m_nNextSecondaryAttackTick(); }
    void NextSecondaryAttackTickUpdated() override { Real()->m_nNextSecondaryAttackTick.NetworkStateChanged(); }
    float& NextSecondaryAttackTickRatio() override { return Real()->m_flNextSecondaryAttackTickRatio(); }
    void NextSecondaryAttackTickRatioUpdated() override { Real()->m_flNextSecondaryAttackTickRatio.NetworkStateChanged(); }
    int32_t& Clip1() override { return Real()->m_iClip1(); }
    void Clip1Updated() override { Real()->m_iClip1.NetworkStateChanged(); }
    int32_t& Clip2() override { return Real()->m_iClip2(); }
    void Clip2Updated() override { Real()->m_iClip2.NetworkStateChanged(); }
    int32_t* ReserveAmmo() override { return Real()->m_pReserveAmmo(); }
    CEntityIOOutput& OnPlayerUse() override { return Real()->m_OnPlayerUse(); }
    void OnPlayerUseUpdated() override { Real()->m_OnPlayerUse.NetworkStateChanged(); }

    ICSWeaponBaseVData* GetWeaponVData() override { return Real()->GetWeaponVData(); }
    const char* GetWeaponClassname() override { return Real()->GetWeaponClassname(); }
};

#endif // _INCLUDE_CBASEPLAYERWEAPONIMPL_H
