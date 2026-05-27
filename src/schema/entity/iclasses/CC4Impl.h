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

#ifndef _INCLUDE_CC4IMPL_H
#define _INCLUDE_CC4IMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IC4.h"
#include "schema/entity/classes/CC4.h"
#include "CCSWeaponBaseImpl.h"

class CC4Impl : public CCSWeaponBaseImpl, public IC4
{

public:
    explicit CC4Impl(CC4* p) : CCSWeaponBaseImpl(p) {}

private:
    CC4* Real() { return static_cast<CC4*>(m_pReal); }

public:
    Vector& LastValidPlayerHeldPosition() override { return Real()->m_vecLastValidPlayerHeldPosition(); }
    void LastValidPlayerHeldPositionUpdated() override { Real()->m_vecLastValidPlayerHeldPosition.NetworkStateChanged(); }
    Vector& LastValidDroppedPosition() override { return Real()->m_vecLastValidDroppedPosition(); }
    void LastValidDroppedPositionUpdated() override { Real()->m_vecLastValidDroppedPosition.NetworkStateChanged(); }
    bool& DoValidDroppedPositionCheck() override { return Real()->m_bDoValidDroppedPositionCheck(); }
    void DoValidDroppedPositionCheckUpdated() override { Real()->m_bDoValidDroppedPositionCheck.NetworkStateChanged(); }
    bool& StartedArming() override { return Real()->m_bStartedArming(); }
    void StartedArmingUpdated() override { Real()->m_bStartedArming.NetworkStateChanged(); }
    float& ArmedTime() override { return Real()->m_fArmedTime(); }
    void ArmedTimeUpdated() override { Real()->m_fArmedTime.NetworkStateChanged(); }
    bool& BombPlacedAnimation() override { return Real()->m_bBombPlacedAnimation(); }
    void BombPlacedAnimationUpdated() override { Real()->m_bBombPlacedAnimation.NetworkStateChanged(); }
    bool& IsPlantingViaUse() override { return Real()->m_bIsPlantingViaUse(); }
    void IsPlantingViaUseUpdated() override { Real()->m_bIsPlantingViaUse.NetworkStateChanged(); }
    EntitySpottedState_t& EntitySpottedState() override { return Real()->m_entitySpottedState(); }
    void EntitySpottedStateUpdated() override { Real()->m_entitySpottedState.NetworkStateChanged(); }
    int32_t& SpotRules() override { return Real()->m_nSpotRules(); }
    void SpotRulesUpdated() override { Real()->m_nSpotRules.NetworkStateChanged(); }
    bool* PlayedArmingBeeps() override { return Real()->m_bPlayedArmingBeeps(); }
    bool& BombPlanted() override { return Real()->m_bBombPlanted(); }
    void BombPlantedUpdated() override { Real()->m_bBombPlanted.NetworkStateChanged(); }
};

#endif // _INCLUDE_CC4IMPL_H
