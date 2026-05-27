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

#ifndef _INCLUDE_CENVEXPLOSIONIMPL_H
#define _INCLUDE_CENVEXPLOSIONIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvExplosion.h"
#include "schema/entity/classes/CEnvExplosion.h"
#include "CModelPointEntityImpl.h"

class CEnvExplosionImpl : public CModelPointEntityImpl, public IEnvExplosion
{

public:
    explicit CEnvExplosionImpl(CEnvExplosion* p) : CModelPointEntityImpl(p) {}

private:
    CEnvExplosion* Real() { return static_cast<CEnvExplosion*>(m_pReal); }

public:
    int32_t& Magnitude() override { return Real()->m_iMagnitude(); }
    void MagnitudeUpdated() override { Real()->m_iMagnitude.NetworkStateChanged(); }
    float& PlayerDamage() override { return Real()->m_flPlayerDamage(); }
    void PlayerDamageUpdated() override { Real()->m_flPlayerDamage.NetworkStateChanged(); }
    int32_t& RadiusOverride() override { return Real()->m_iRadiusOverride(); }
    void RadiusOverrideUpdated() override { Real()->m_iRadiusOverride.NetworkStateChanged(); }
    float& InnerRadius() override { return Real()->m_flInnerRadius(); }
    void InnerRadiusUpdated() override { Real()->m_flInnerRadius.NetworkStateChanged(); }
    float& DamageForce() override { return Real()->m_flDamageForce(); }
    void DamageForceUpdated() override { Real()->m_flDamageForce.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Inflictor() override { return Real()->m_hInflictor(); }
    void InflictorUpdated() override { Real()->m_hInflictor.NetworkStateChanged(); }
    DamageTypes_t& CustomDamageType() override { return Real()->m_iCustomDamageType(); }
    void CustomDamageTypeUpdated() override { Real()->m_iCustomDamageType.NetworkStateChanged(); }
    bool& CreateDebris() override { return Real()->m_bCreateDebris(); }
    void CreateDebrisUpdated() override { Real()->m_bCreateDebris.NetworkStateChanged(); }
    CUtlSymbolLarge& CustomEffectName() override { return Real()->m_iszCustomEffectName(); }
    void CustomEffectNameUpdated() override { Real()->m_iszCustomEffectName.NetworkStateChanged(); }
    CUtlSymbolLarge& CustomSoundName() override { return Real()->m_iszCustomSoundName(); }
    void CustomSoundNameUpdated() override { Real()->m_iszCustomSoundName.NetworkStateChanged(); }
    bool& SuppressParticleImpulse() override { return Real()->m_bSuppressParticleImpulse(); }
    void SuppressParticleImpulseUpdated() override { Real()->m_bSuppressParticleImpulse.NetworkStateChanged(); }
    Class_T& ClassIgnore() override { return Real()->m_iClassIgnore(); }
    void ClassIgnoreUpdated() override { Real()->m_iClassIgnore.NetworkStateChanged(); }
    Class_T& ClassIgnore2() override { return Real()->m_iClassIgnore2(); }
    void ClassIgnore2Updated() override { Real()->m_iClassIgnore2.NetworkStateChanged(); }
    CUtlSymbolLarge& EntityIgnoreName() override { return Real()->m_iszEntityIgnoreName(); }
    void EntityIgnoreNameUpdated() override { Real()->m_iszEntityIgnoreName.NetworkStateChanged(); }
    CHandle<CBaseEntity>& EntityIgnore() override { return Real()->m_hEntityIgnore(); }
    void EntityIgnoreUpdated() override { Real()->m_hEntityIgnore.NetworkStateChanged(); }
};

#endif // _INCLUDE_CENVEXPLOSIONIMPL_H
