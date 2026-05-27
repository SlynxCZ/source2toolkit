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

#ifndef _INCLUDE_CBASECSGRENADEIMPL_H
#define _INCLUDE_CBASECSGRENADEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IBaseCSGrenade.h"
#include "schema/entity/classes/CBaseCSGrenade.h"
#include "CCSWeaponBaseImpl.h"

class CBaseCSGrenadeImpl : public CCSWeaponBaseImpl, public IBaseCSGrenade
{

public:
    explicit CBaseCSGrenadeImpl(CBaseCSGrenade* p) : CCSWeaponBaseImpl(p) {}

private:
    CBaseCSGrenade* Real() { return static_cast<CBaseCSGrenade*>(m_pReal); }

public:
    bool& Redraw() override { return Real()->m_bRedraw(); }
    void RedrawUpdated() override { Real()->m_bRedraw.NetworkStateChanged(); }
    bool& IsHeldByPlayer() override { return Real()->m_bIsHeldByPlayer(); }
    void IsHeldByPlayerUpdated() override { Real()->m_bIsHeldByPlayer.NetworkStateChanged(); }
    bool& PinPulled() override { return Real()->m_bPinPulled(); }
    void PinPulledUpdated() override { Real()->m_bPinPulled.NetworkStateChanged(); }
    bool& JumpThrow() override { return Real()->m_bJumpThrow(); }
    void JumpThrowUpdated() override { Real()->m_bJumpThrow.NetworkStateChanged(); }
    bool& ThrowAnimating() override { return Real()->m_bThrowAnimating(); }
    void ThrowAnimatingUpdated() override { Real()->m_bThrowAnimating.NetworkStateChanged(); }
    float& ThrowTime() override { return Real()->m_fThrowTime(); }
    void ThrowTimeUpdated() override { Real()->m_fThrowTime.NetworkStateChanged(); }
    float& ThrowStrength() override { return Real()->m_flThrowStrength(); }
    void ThrowStrengthUpdated() override { Real()->m_flThrowStrength.NetworkStateChanged(); }
    float& DropTime() override { return Real()->m_fDropTime(); }
    void DropTimeUpdated() override { Real()->m_fDropTime.NetworkStateChanged(); }
    float& PinPullTime() override { return Real()->m_fPinPullTime(); }
    void PinPullTimeUpdated() override { Real()->m_fPinPullTime.NetworkStateChanged(); }
    bool& JustPulledPin() override { return Real()->m_bJustPulledPin(); }
    void JustPulledPinUpdated() override { Real()->m_bJustPulledPin.NetworkStateChanged(); }
    int32_t& NextHoldTick() override { return Real()->m_nNextHoldTick(); }
    void NextHoldTickUpdated() override { Real()->m_nNextHoldTick.NetworkStateChanged(); }
    float& NextHoldFrac() override { return Real()->m_flNextHoldFrac(); }
    void NextHoldFracUpdated() override { Real()->m_flNextHoldFrac.NetworkStateChanged(); }
    CHandle<CCSWeaponBase>& SwitchToWeaponAfterThrow() override { return Real()->m_hSwitchToWeaponAfterThrow(); }
    void SwitchToWeaponAfterThrowUpdated() override { Real()->m_hSwitchToWeaponAfterThrow.NetworkStateChanged(); }
};

#endif // _INCLUDE_CBASECSGRENADEIMPL_H
