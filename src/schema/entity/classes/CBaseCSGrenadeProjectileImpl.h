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

#ifndef _INCLUDE_CBASECSGRENADEPROJECTILEIMPL_H
#define _INCLUDE_CBASECSGRENADEPROJECTILEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBaseCSGrenadeProjectile.h"
#include "schema/entity/classes/CBaseCSGrenadeProjectile.h"
#include "CBaseGrenadeImpl.h"

class CBaseCSGrenadeProjectileImpl : public CBaseGrenadeImpl, public IBaseCSGrenadeProjectile
{

public:
    explicit CBaseCSGrenadeProjectileImpl(CBaseCSGrenadeProjectile* p) : CBaseGrenadeImpl(p) {}

private:
    CBaseCSGrenadeProjectile* Real() { return static_cast<CBaseCSGrenadeProjectile*>(m_pReal); }

public:
    Vector& InitialPosition() override { return Real()->m_vInitialPosition(); }
    void InitialPositionUpdated() override { Real()->m_vInitialPosition.NetworkStateChanged(); }
    Vector& InitialVelocity() override { return Real()->m_vInitialVelocity(); }
    void InitialVelocityUpdated() override { Real()->m_vInitialVelocity.NetworkStateChanged(); }
    int32_t& Bounces() override { return Real()->m_nBounces(); }
    void BouncesUpdated() override { Real()->m_nBounces.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIParticleSystemDefinition>& ExplodeEffectIndex() override { return Real()->m_nExplodeEffectIndex(); }
    void ExplodeEffectIndexUpdated() override { Real()->m_nExplodeEffectIndex.NetworkStateChanged(); }
    int32_t& ExplodeEffectTickBegin() override { return Real()->m_nExplodeEffectTickBegin(); }
    void ExplodeEffectTickBeginUpdated() override { Real()->m_nExplodeEffectTickBegin.NetworkStateChanged(); }
    Vector& ExplodeEffectOrigin() override { return Real()->m_vecExplodeEffectOrigin(); }
    void ExplodeEffectOriginUpdated() override { Real()->m_vecExplodeEffectOrigin.NetworkStateChanged(); }
    float& SpawnTime() override { return Real()->m_flSpawnTime(); }
    void SpawnTimeUpdated() override { Real()->m_flSpawnTime.NetworkStateChanged(); }
    uint8_t& OGSExtraFlags() override { return Real()->m_unOGSExtraFlags(); }
    void OGSExtraFlagsUpdated() override { Real()->m_unOGSExtraFlags.NetworkStateChanged(); }
    bool& DetonationRecorded() override { return Real()->m_bDetonationRecorded(); }
    void DetonationRecordedUpdated() override { Real()->m_bDetonationRecorded.NetworkStateChanged(); }
    uint16_t& ItemIndex() override { return Real()->m_nItemIndex(); }
    void ItemIndexUpdated() override { Real()->m_nItemIndex.NetworkStateChanged(); }
    Vector& OriginalSpawnLocation() override { return Real()->m_vecOriginalSpawnLocation(); }
    void OriginalSpawnLocationUpdated() override { Real()->m_vecOriginalSpawnLocation.NetworkStateChanged(); }
    float& LastBounceSoundTime() override { return Real()->m_flLastBounceSoundTime(); }
    void LastBounceSoundTimeUpdated() override { Real()->m_flLastBounceSoundTime.NetworkStateChanged(); }
    RotationVector& GrenadeSpin() override { return Real()->m_vecGrenadeSpin(); }
    void GrenadeSpinUpdated() override { Real()->m_vecGrenadeSpin.NetworkStateChanged(); }
    Vector& LastHitSurfaceNormal() override { return Real()->m_vecLastHitSurfaceNormal(); }
    void LastHitSurfaceNormalUpdated() override { Real()->m_vecLastHitSurfaceNormal.NetworkStateChanged(); }
    int32_t& TicksAtZeroVelocity() override { return Real()->m_nTicksAtZeroVelocity(); }
    void TicksAtZeroVelocityUpdated() override { Real()->m_nTicksAtZeroVelocity.NetworkStateChanged(); }
    bool& HasEverHitEnemy() override { return Real()->m_bHasEverHitEnemy(); }
    void HasEverHitEnemyUpdated() override { Real()->m_bHasEverHitEnemy.NetworkStateChanged(); }
};

#endif // _INCLUDE_CBASECSGRENADEPROJECTILEIMPL_H
