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

#ifndef _INCLUDE_CPARTICLESYSTEMIMPL_H
#define _INCLUDE_CPARTICLESYSTEMIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IParticleSystem.h"
#include "schema/entity/classes/CParticleSystem.h"
#include "CBaseModelEntityImpl.h"

class CParticleSystemImpl : public CBaseModelEntityImpl, public IParticleSystem
{

public:
    explicit CParticleSystemImpl(CParticleSystem* p) : CBaseModelEntityImpl(p) {}

private:
    CParticleSystem* Real() { return static_cast<CParticleSystem*>(m_pReal); }

public:
    char* SnapshotFileName() override { return Real()->m_szSnapshotFileName(); }
    bool& Active() override { return Real()->m_bActive(); }
    void ActiveUpdated() override { Real()->m_bActive.NetworkStateChanged(); }
    bool& Frozen() override { return Real()->m_bFrozen(); }
    void FrozenUpdated() override { Real()->m_bFrozen.NetworkStateChanged(); }
    float& FreezeTransitionDuration() override { return Real()->m_flFreezeTransitionDuration(); }
    void FreezeTransitionDurationUpdated() override { Real()->m_flFreezeTransitionDuration.NetworkStateChanged(); }
    int32_t& StopType() override { return Real()->m_nStopType(); }
    void StopTypeUpdated() override { Real()->m_nStopType.NetworkStateChanged(); }
    bool& AnimateDuringGameplayPause() override { return Real()->m_bAnimateDuringGameplayPause(); }
    void AnimateDuringGameplayPauseUpdated() override { Real()->m_bAnimateDuringGameplayPause.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIParticleSystemDefinition>& EffectIndex() override { return Real()->m_iEffectIndex(); }
    void EffectIndexUpdated() override { Real()->m_iEffectIndex.NetworkStateChanged(); }
    float& StartTime() override { return Real()->m_flStartTime(); }
    void StartTimeUpdated() override { Real()->m_flStartTime.NetworkStateChanged(); }
    float& PreSimTime() override { return Real()->m_flPreSimTime(); }
    void PreSimTimeUpdated() override { Real()->m_flPreSimTime.NetworkStateChanged(); }
    Vector* ServerControlPoints() override { return Real()->m_vServerControlPoints(); }
    uint8_t* ServerControlPointAssignments() override { return Real()->m_iServerControlPointAssignments(); }
    CHandle<CBaseEntity>* ControlPointEnts() override { return Real()->m_hControlPointEnts(); }
    bool& NoSave() override { return Real()->m_bNoSave(); }
    void NoSaveUpdated() override { Real()->m_bNoSave.NetworkStateChanged(); }
    bool& NoFreeze() override { return Real()->m_bNoFreeze(); }
    void NoFreezeUpdated() override { Real()->m_bNoFreeze.NetworkStateChanged(); }
    bool& NoRamp() override { return Real()->m_bNoRamp(); }
    void NoRampUpdated() override { Real()->m_bNoRamp.NetworkStateChanged(); }
    bool& StartActive() override { return Real()->m_bStartActive(); }
    void StartActiveUpdated() override { Real()->m_bStartActive.NetworkStateChanged(); }
    CUtlSymbolLarge& EffectName() override { return Real()->m_iszEffectName(); }
    void EffectNameUpdated() override { Real()->m_iszEffectName.NetworkStateChanged(); }
    CUtlSymbolLarge* ControlPointNames() override { return Real()->m_iszControlPointNames(); }
    int32_t& DataCP() override { return Real()->m_nDataCP(); }
    void DataCPUpdated() override { Real()->m_nDataCP.NetworkStateChanged(); }
    Vector& DataCPValue() override { return Real()->m_vecDataCPValue(); }
    void DataCPValueUpdated() override { Real()->m_vecDataCPValue.NetworkStateChanged(); }
    int32_t& TintCP() override { return Real()->m_nTintCP(); }
    void TintCPUpdated() override { Real()->m_nTintCP.NetworkStateChanged(); }
    Color& Tint() override { return Real()->m_clrTint(); }
    void TintUpdated() override { Real()->m_clrTint.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPARTICLESYSTEMIMPL_H
