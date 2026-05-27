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

#ifndef _INCLUDE_CBREAKABLEPROPIMPL_H
#define _INCLUDE_CBREAKABLEPROPIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IBreakableProp.h"
#include "schema/entity/classes/CBreakableProp.h"
#include "CBasePropImpl.h"

class CBreakablePropImpl : public CBasePropImpl, public IBreakableProp
{

public:
    explicit CBreakablePropImpl(CBreakableProp* p) : CBasePropImpl(p) {}

private:
    CBreakableProp* Real() { return static_cast<CBreakableProp*>(m_pReal); }

public:
    CPropDataComponent& CPropDataComponent() override { return Real()->m_CPropDataComponent(); }
    void CPropDataComponentUpdated() override { Real()->m_CPropDataComponent.NetworkStateChanged(); }
    CEntityIOOutput& OnStartDeath() override { return Real()->m_OnStartDeath(); }
    void OnStartDeathUpdated() override { Real()->m_OnStartDeath.NetworkStateChanged(); }
    CEntityIOOutput& OnBreak() override { return Real()->m_OnBreak(); }
    void OnBreakUpdated() override { Real()->m_OnBreak.NetworkStateChanged(); }
    CEntityIOOutput& OnTakeDamage() override { return Real()->m_OnTakeDamage(); }
    void OnTakeDamageUpdated() override { Real()->m_OnTakeDamage.NetworkStateChanged(); }
    float& ImpactEnergyScale() override { return Real()->m_impactEnergyScale(); }
    void ImpactEnergyScaleUpdated() override { Real()->m_impactEnergyScale.NetworkStateChanged(); }
    int32_t& MinHealthDmg() override { return Real()->m_iMinHealthDmg(); }
    void MinHealthDmgUpdated() override { Real()->m_iMinHealthDmg.NetworkStateChanged(); }
    QAngle& PreferredCarryAngles() override { return Real()->m_preferredCarryAngles(); }
    void PreferredCarryAnglesUpdated() override { Real()->m_preferredCarryAngles.NetworkStateChanged(); }
    float& PressureDelay() override { return Real()->m_flPressureDelay(); }
    void PressureDelayUpdated() override { Real()->m_flPressureDelay.NetworkStateChanged(); }
    float& DefBurstScale() override { return Real()->m_flDefBurstScale(); }
    void DefBurstScaleUpdated() override { Real()->m_flDefBurstScale.NetworkStateChanged(); }
    Vector& DefBurstOffset() override { return Real()->m_vDefBurstOffset(); }
    void DefBurstOffsetUpdated() override { Real()->m_vDefBurstOffset.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Breaker() override { return Real()->m_hBreaker(); }
    void BreakerUpdated() override { Real()->m_hBreaker.NetworkStateChanged(); }
    PerformanceMode_t& PerformanceMode() override { return Real()->m_PerformanceMode(); }
    void PerformanceModeUpdated() override { Real()->m_PerformanceMode.NetworkStateChanged(); }
    float& PreventDamageBeforeTime() override { return Real()->m_flPreventDamageBeforeTime(); }
    void PreventDamageBeforeTimeUpdated() override { Real()->m_flPreventDamageBeforeTime.NetworkStateChanged(); }
    BreakableContentsType_t& BreakableContentsType() override { return Real()->m_BreakableContentsType(); }
    void BreakableContentsTypeUpdated() override { Real()->m_BreakableContentsType.NetworkStateChanged(); }
    CUtlString& StrBreakableContentsPropGroupOverride() override { return Real()->m_strBreakableContentsPropGroupOverride(); }
    void StrBreakableContentsPropGroupOverrideUpdated() override { Real()->m_strBreakableContentsPropGroupOverride.NetworkStateChanged(); }
    CUtlString& StrBreakableContentsParticleOverride() override { return Real()->m_strBreakableContentsParticleOverride(); }
    void StrBreakableContentsParticleOverrideUpdated() override { Real()->m_strBreakableContentsParticleOverride.NetworkStateChanged(); }
    bool& HasBreakPiecesOrCommands() override { return Real()->m_bHasBreakPiecesOrCommands(); }
    void HasBreakPiecesOrCommandsUpdated() override { Real()->m_bHasBreakPiecesOrCommands.NetworkStateChanged(); }
    float& ExplodeDamage() override { return Real()->m_explodeDamage(); }
    void ExplodeDamageUpdated() override { Real()->m_explodeDamage.NetworkStateChanged(); }
    float& ExplodeRadius() override { return Real()->m_explodeRadius(); }
    void ExplodeRadiusUpdated() override { Real()->m_explodeRadius.NetworkStateChanged(); }
    CGlobalSymbol& ExplosionType() override { return Real()->m_sExplosionType(); }
    void ExplosionTypeUpdated() override { Real()->m_sExplosionType.NetworkStateChanged(); }
    float& ExplosionDelay() override { return Real()->m_explosionDelay(); }
    void ExplosionDelayUpdated() override { Real()->m_explosionDelay.NetworkStateChanged(); }
    CUtlSymbolLarge& ExplosionBuildupSound() override { return Real()->m_explosionBuildupSound(); }
    void ExplosionBuildupSoundUpdated() override { Real()->m_explosionBuildupSound.NetworkStateChanged(); }
    CUtlSymbolLarge& ExplosionCustomEffect() override { return Real()->m_explosionCustomEffect(); }
    void ExplosionCustomEffectUpdated() override { Real()->m_explosionCustomEffect.NetworkStateChanged(); }
    CUtlSymbolLarge& ExplosionCustomSound() override { return Real()->m_explosionCustomSound(); }
    void ExplosionCustomSoundUpdated() override { Real()->m_explosionCustomSound.NetworkStateChanged(); }
    CUtlSymbolLarge& ExplosionModifier() override { return Real()->m_explosionModifier(); }
    void ExplosionModifierUpdated() override { Real()->m_explosionModifier.NetworkStateChanged(); }
    CHandle<CBasePlayerPawn>& PhysicsAttacker() override { return Real()->m_hPhysicsAttacker(); }
    void PhysicsAttackerUpdated() override { Real()->m_hPhysicsAttacker.NetworkStateChanged(); }
    float& LastPhysicsInfluenceTime() override { return Real()->m_flLastPhysicsInfluenceTime(); }
    void LastPhysicsInfluenceTimeUpdated() override { Real()->m_flLastPhysicsInfluenceTime.NetworkStateChanged(); }
    float& DefaultFadeScale() override { return Real()->m_flDefaultFadeScale(); }
    void DefaultFadeScaleUpdated() override { Real()->m_flDefaultFadeScale.NetworkStateChanged(); }
    CHandle<CBaseEntity>& LastAttacker() override { return Real()->m_hLastAttacker(); }
    void LastAttackerUpdated() override { Real()->m_hLastAttacker.NetworkStateChanged(); }
    CUtlSymbolLarge& PuntSound() override { return Real()->m_iszPuntSound(); }
    void PuntSoundUpdated() override { Real()->m_iszPuntSound.NetworkStateChanged(); }
    bool& UsePuntSound() override { return Real()->m_bUsePuntSound(); }
    void UsePuntSoundUpdated() override { Real()->m_bUsePuntSound.NetworkStateChanged(); }
    bool& OriginalBlockLOS() override { return Real()->m_bOriginalBlockLOS(); }
    void OriginalBlockLOSUpdated() override { Real()->m_bOriginalBlockLOS.NetworkStateChanged(); }
};

#endif // _INCLUDE_CBREAKABLEPROPIMPL_H
