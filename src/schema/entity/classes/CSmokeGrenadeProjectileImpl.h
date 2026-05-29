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

#ifndef _INCLUDE_CSMOKEGRENADEPROJECTILEIMPL_H
#define _INCLUDE_CSMOKEGRENADEPROJECTILEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISmokeGrenadeProjectile.h"
#include "schema/entity/classes/CSmokeGrenadeProjectile.h"
#include "CBaseCSGrenadeProjectileImpl.h"

class CSmokeGrenadeProjectileImpl : public CBaseCSGrenadeProjectileImpl, public virtual ISmokeGrenadeProjectile
{

public:
    explicit CSmokeGrenadeProjectileImpl(CSmokeGrenadeProjectile* p) : CBaseCSGrenadeProjectileImpl(p) {}

private:
    CSmokeGrenadeProjectile* Real() { return static_cast<CSmokeGrenadeProjectile*>(m_pReal); }
    CSmokeGrenadeProjectile* Real() const { return static_cast<CSmokeGrenadeProjectile*>(m_pReal); }

public:
    CSmokeGrenadeProjectile* GetOriginal() const override { return Real(); }
    int32_t& SmokeEffectTickBegin() override { return Real()->m_nSmokeEffectTickBegin(); }
    void SmokeEffectTickBeginUpdated() override { Real()->m_nSmokeEffectTickBegin.NetworkStateChanged(); }
    bool& DidSmokeEffect() override { return Real()->m_bDidSmokeEffect(); }
    void DidSmokeEffectUpdated() override { Real()->m_bDidSmokeEffect.NetworkStateChanged(); }
    int32_t& RandomSeed() override { return Real()->m_nRandomSeed(); }
    void RandomSeedUpdated() override { Real()->m_nRandomSeed.NetworkStateChanged(); }
    Vector& SmokeColor() override { return Real()->m_vSmokeColor(); }
    void SmokeColorUpdated() override { Real()->m_vSmokeColor.NetworkStateChanged(); }
    Vector& SmokeDetonationPos() override { return Real()->m_vSmokeDetonationPos(); }
    void SmokeDetonationPosUpdated() override { Real()->m_vSmokeDetonationPos.NetworkStateChanged(); }
    CUtlVector<uint8_t>& VoxelFrameData() override { return Real()->m_VoxelFrameData(); }
    void VoxelFrameDataUpdated() override { Real()->m_VoxelFrameData.NetworkStateChanged(); }
    int32_t& VoxelFrameDataSize() override { return Real()->m_nVoxelFrameDataSize(); }
    void VoxelFrameDataSizeUpdated() override { Real()->m_nVoxelFrameDataSize.NetworkStateChanged(); }
    int32_t& VoxelUpdate() override { return Real()->m_nVoxelUpdate(); }
    void VoxelUpdateUpdated() override { Real()->m_nVoxelUpdate.NetworkStateChanged(); }
    float& LastBounce() override { return Real()->m_flLastBounce(); }
    void LastBounceUpdated() override { Real()->m_flLastBounce.NetworkStateChanged(); }
    float& FllastSimulationTime() override { return Real()->m_fllastSimulationTime(); }
    void FllastSimulationTimeUpdated() override { Real()->m_fllastSimulationTime.NetworkStateChanged(); }
    bool& ExplodeFromInferno() override { return Real()->m_bExplodeFromInferno(); }
    void ExplodeFromInfernoUpdated() override { Real()->m_bExplodeFromInferno.NetworkStateChanged(); }
    bool& DidGroundScorch() override { return Real()->m_bDidGroundScorch(); }
    void DidGroundScorchUpdated() override { Real()->m_bDidGroundScorch.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline ISmokeGrenadeProjectile* CSmokeGrenadeProjectile::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ISmokeGrenadeProjectile*>(tagIt->second.ptr_for_return);
    auto* impl = new CSmokeGrenadeProjectileImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ISmokeGrenadeProjectile*>(impl));
    return impl;
}
inline ISmokeGrenadeProjectile* ISmokeGrenadeProjectile::FromRaw(CEntityInstance* p) { return p ? static_cast<CSmokeGrenadeProjectile*>(p)->ToInterface() : nullptr; }
inline ISmokeGrenadeProjectile* ISmokeGrenadeProjectile::FromOriginal(CSmokeGrenadeProjectile* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CSMOKEGRENADEPROJECTILEIMPL_H
