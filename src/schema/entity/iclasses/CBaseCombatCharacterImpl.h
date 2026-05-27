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

#ifndef _INCLUDE_CBASECOMBATCHARACTERIMPL_H
#define _INCLUDE_CBASECOMBATCHARACTERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IBaseCombatCharacter.h"
#include "schema/entity/classes/CBaseCombatCharacter.h"
#include "CBaseAnimGraphImpl.h"

class CBaseCombatCharacterImpl : public CBaseAnimGraphImpl, public IBaseCombatCharacter
{

public:
    explicit CBaseCombatCharacterImpl(CBaseCombatCharacter* p) : CBaseAnimGraphImpl(p) {}

private:
    CBaseCombatCharacter* Real() { return static_cast<CBaseCombatCharacter*>(m_pReal); }

public:
    bool& ForceServerRagdoll() override { return Real()->m_bForceServerRagdoll(); }
    void ForceServerRagdollUpdated() override { Real()->m_bForceServerRagdoll.NetworkStateChanged(); }
    CUtlVector<CHandle<CEconWearable>>& MyWearables() override { return Real()->m_hMyWearables(); }
    void MyWearablesUpdated() override { Real()->m_hMyWearables.NetworkStateChanged(); }
    float& ImpactEnergyScale() override { return Real()->m_impactEnergyScale(); }
    void ImpactEnergyScaleUpdated() override { Real()->m_impactEnergyScale.NetworkStateChanged(); }
    bool& ApplyStressDamage() override { return Real()->m_bApplyStressDamage(); }
    void ApplyStressDamageUpdated() override { Real()->m_bApplyStressDamage.NetworkStateChanged(); }
    bool& DeathEventsDispatched() override { return Real()->m_bDeathEventsDispatched(); }
    void DeathEventsDispatchedUpdated() override { Real()->m_bDeathEventsDispatched.NetworkStateChanged(); }
    CUtlVector<RelationshipOverride_t>*& VecRelationships() override { return Real()->m_pVecRelationships(); }
    void VecRelationshipsUpdated() override { Real()->m_pVecRelationships.NetworkStateChanged(); }
    CUtlSymbolLarge& StrRelationships() override { return Real()->m_strRelationships(); }
    void StrRelationshipsUpdated() override { Real()->m_strRelationships.NetworkStateChanged(); }
    Hull_t& Hull() override { return Real()->m_eHull(); }
    void HullUpdated() override { Real()->m_eHull.NetworkStateChanged(); }
    uint32_t& NavHullIdx() override { return Real()->m_nNavHullIdx(); }
    void NavHullIdxUpdated() override { Real()->m_nNavHullIdx.NetworkStateChanged(); }
    CMovementStatsProperty& MovementStats() override { return Real()->m_movementStats(); }
    void MovementStatsUpdated() override { Real()->m_movementStats.NetworkStateChanged(); }
};

#endif // _INCLUDE_CBASECOMBATCHARACTERIMPL_H
