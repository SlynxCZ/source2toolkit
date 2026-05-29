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

#ifndef _INCLUDE_CBASEGRENADEIMPL_H
#define _INCLUDE_CBASEGRENADEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBaseGrenade.h"
#include "schema/entity/classes/CBaseGrenade.h"
#include "CBaseAnimGraphImpl.h"

class CBaseGrenadeImpl : public CBaseAnimGraphImpl, public IBaseGrenade
{

public:
    explicit CBaseGrenadeImpl(CBaseGrenade* p) : CBaseAnimGraphImpl(p) {}

private:
    CBaseGrenade* Real() { return static_cast<CBaseGrenade*>(m_pReal); }
    CBaseGrenade* Real() const { return static_cast<CBaseGrenade*>(m_pReal); }

public:
    CBaseGrenade* GetOriginal() const override { return Real(); }
    ::CEntityIOOutput& OnPlayerPickup() override { return Real()->m_OnPlayerPickup(); }
    void OnPlayerPickupUpdated() override { Real()->m_OnPlayerPickup.NetworkStateChanged(); }
    ::CEntityIOOutput& OnExplode() override { return Real()->m_OnExplode(); }
    void OnExplodeUpdated() override { Real()->m_OnExplode.NetworkStateChanged(); }
    bool& HasWarnedAI() override { return Real()->m_bHasWarnedAI(); }
    void HasWarnedAIUpdated() override { Real()->m_bHasWarnedAI.NetworkStateChanged(); }
    bool& IsSmokeGrenade() override { return Real()->m_bIsSmokeGrenade(); }
    void IsSmokeGrenadeUpdated() override { Real()->m_bIsSmokeGrenade.NetworkStateChanged(); }
    bool& IsLive() override { return Real()->m_bIsLive(); }
    void IsLiveUpdated() override { Real()->m_bIsLive.NetworkStateChanged(); }
    float& DmgRadius() override { return Real()->m_DmgRadius(); }
    void DmgRadiusUpdated() override { Real()->m_DmgRadius.NetworkStateChanged(); }
    float& DetonateTime() override { return Real()->m_flDetonateTime(); }
    void DetonateTimeUpdated() override { Real()->m_flDetonateTime.NetworkStateChanged(); }
    float& WarnAITime() override { return Real()->m_flWarnAITime(); }
    void WarnAITimeUpdated() override { Real()->m_flWarnAITime.NetworkStateChanged(); }
    float& Damage() override { return Real()->m_flDamage(); }
    void DamageUpdated() override { Real()->m_flDamage.NetworkStateChanged(); }
    CUtlSymbolLarge& BounceSound() override { return Real()->m_iszBounceSound(); }
    void BounceSoundUpdated() override { Real()->m_iszBounceSound.NetworkStateChanged(); }
    CUtlString& ExplosionSound() override { return Real()->m_ExplosionSound(); }
    void ExplosionSoundUpdated() override { Real()->m_ExplosionSound.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& Thrower() override { return Real()->m_hThrower(); }
    void ThrowerUpdated() override { Real()->m_hThrower.NetworkStateChanged(); }
    float& NextAttack() override { return Real()->m_flNextAttack(); }
    void NextAttackUpdated() override { Real()->m_flNextAttack.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& OriginalThrower() override { return Real()->m_hOriginalThrower(); }
    void OriginalThrowerUpdated() override { Real()->m_hOriginalThrower.NetworkStateChanged(); }
};

inline IBaseGrenade* CBaseGrenade::ToInterface() { return new CBaseGrenadeImpl(this); }
inline IBaseGrenade* IBaseGrenade::FromOriginal(CBaseGrenade* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBASEGRENADEIMPL_H
