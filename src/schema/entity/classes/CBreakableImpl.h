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

#ifndef _INCLUDE_CBREAKABLEIMPL_H
#define _INCLUDE_CBREAKABLEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBreakable.h"
#include "schema/entity/classes/CBreakable.h"
#include "CBaseModelEntityImpl.h"

class CBreakableImpl : public CBaseModelEntityImpl, public IBreakable
{

public:
    explicit CBreakableImpl(CBreakable* p) : CBaseModelEntityImpl(p) {}

private:
    CBreakable* Real() { return static_cast<CBreakable*>(m_pReal); }
    CBreakable* Real() const { return static_cast<CBreakable*>(m_pReal); }

public:
    CBreakable* GetOriginal() const override { return Real(); }
    ::CPropDataComponent& PropDataComponent() override { return Real()->m_CPropDataComponent(); }
    void PropDataComponentUpdated() override { Real()->m_CPropDataComponent.NetworkStateChanged(); }
    ::Materials& Material() override { return Real()->m_Material(); }
    void MaterialUpdated() override { Real()->m_Material.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Breaker() override { return Real()->m_hBreaker(); }
    void BreakerUpdated() override { Real()->m_hBreaker.NetworkStateChanged(); }
    ::Explosions& Explosion() override { return Real()->m_Explosion(); }
    void ExplosionUpdated() override { Real()->m_Explosion.NetworkStateChanged(); }
    CUtlSymbolLarge& SpawnObject() override { return Real()->m_iszSpawnObject(); }
    void SpawnObjectUpdated() override { Real()->m_iszSpawnObject.NetworkStateChanged(); }
    float& PressureDelay() override { return Real()->m_flPressureDelay(); }
    void PressureDelayUpdated() override { Real()->m_flPressureDelay.NetworkStateChanged(); }
    int32_t& MinHealthDmg() override { return Real()->m_iMinHealthDmg(); }
    void MinHealthDmgUpdated() override { Real()->m_iMinHealthDmg.NetworkStateChanged(); }
    CUtlSymbolLarge& PropData() override { return Real()->m_iszPropData(); }
    void PropDataUpdated() override { Real()->m_iszPropData.NetworkStateChanged(); }
    float& ImpactEnergyScale() override { return Real()->m_impactEnergyScale(); }
    void ImpactEnergyScaleUpdated() override { Real()->m_impactEnergyScale.NetworkStateChanged(); }
    ::EOverrideBlockLOS_t& OverrideBlockLOS() override { return Real()->m_nOverrideBlockLOS(); }
    void OverrideBlockLOSUpdated() override { Real()->m_nOverrideBlockLOS.NetworkStateChanged(); }
    ::CEntityIOOutput& OnStartDeath() override { return Real()->m_OnStartDeath(); }
    void OnStartDeathUpdated() override { Real()->m_OnStartDeath.NetworkStateChanged(); }
    ::CEntityIOOutput& OnBreak() override { return Real()->m_OnBreak(); }
    void OnBreakUpdated() override { Real()->m_OnBreak.NetworkStateChanged(); }
    ::PerformanceMode_t& PerformanceMode() override { return Real()->m_PerformanceMode(); }
    void PerformanceModeUpdated() override { Real()->m_PerformanceMode.NetworkStateChanged(); }
    CHandle<CBasePlayerPawn>& PhysicsAttacker() override { return Real()->m_hPhysicsAttacker(); }
    void PhysicsAttackerUpdated() override { Real()->m_hPhysicsAttacker.NetworkStateChanged(); }
    float& LastPhysicsInfluenceTime() override { return Real()->m_flLastPhysicsInfluenceTime(); }
    void LastPhysicsInfluenceTimeUpdated() override { Real()->m_flLastPhysicsInfluenceTime.NetworkStateChanged(); }
};

inline IBreakable* CBreakable::ToInterface() { return new CBreakableImpl(this); }
inline IBreakable* IBreakable::FromOriginal(CBreakable* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBREAKABLEIMPL_H
