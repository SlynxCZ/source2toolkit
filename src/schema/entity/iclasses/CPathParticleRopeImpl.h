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

#ifndef _INCLUDE_CPATHPARTICLEROPEIMPL_H
#define _INCLUDE_CPATHPARTICLEROPEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IPathParticleRope.h"
#include "schema/entity/classes/CPathParticleRope.h"
#include "CBaseEntityImpl.h"

class CPathParticleRopeImpl : public CBaseEntityImpl, public IPathParticleRope
{

public:
    explicit CPathParticleRopeImpl(CPathParticleRope* p) : CBaseEntityImpl(p) {}

private:
    CPathParticleRope* Real() { return static_cast<CPathParticleRope*>(m_pReal); }

public:
    bool& StartActive() override { return Real()->m_bStartActive(); }
    void StartActiveUpdated() override { Real()->m_bStartActive.NetworkStateChanged(); }
    float& MaxSimulationTime() override { return Real()->m_flMaxSimulationTime(); }
    void MaxSimulationTimeUpdated() override { Real()->m_flMaxSimulationTime.NetworkStateChanged(); }
    CUtlSymbolLarge& EffectName() override { return Real()->m_iszEffectName(); }
    void EffectNameUpdated() override { Real()->m_iszEffectName.NetworkStateChanged(); }
    CUtlVector<CUtlSymbolLarge>& PathNodes_Name() override { return Real()->m_PathNodes_Name(); }
    void PathNodes_NameUpdated() override { Real()->m_PathNodes_Name.NetworkStateChanged(); }
    float& ParticleSpacing() override { return Real()->m_flParticleSpacing(); }
    void ParticleSpacingUpdated() override { Real()->m_flParticleSpacing.NetworkStateChanged(); }
    float& Slack() override { return Real()->m_flSlack(); }
    void SlackUpdated() override { Real()->m_flSlack.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_flRadius(); }
    void RadiusUpdated() override { Real()->m_flRadius.NetworkStateChanged(); }
    Color& ColorTint() override { return Real()->m_ColorTint(); }
    void ColorTintUpdated() override { Real()->m_ColorTint.NetworkStateChanged(); }
    int32_t& EffectState() override { return Real()->m_nEffectState(); }
    void EffectStateUpdated() override { Real()->m_nEffectState.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIParticleSystemDefinition>& EffectIndex() override { return Real()->m_iEffectIndex(); }
    void EffectIndexUpdated() override { Real()->m_iEffectIndex.NetworkStateChanged(); }
    CUtlVector<Vector>& PathNodes_Position() override { return Real()->m_PathNodes_Position(); }
    void PathNodes_PositionUpdated() override { Real()->m_PathNodes_Position.NetworkStateChanged(); }
    CUtlVector<Vector>& PathNodes_TangentIn() override { return Real()->m_PathNodes_TangentIn(); }
    void PathNodes_TangentInUpdated() override { Real()->m_PathNodes_TangentIn.NetworkStateChanged(); }
    CUtlVector<Vector>& PathNodes_TangentOut() override { return Real()->m_PathNodes_TangentOut(); }
    void PathNodes_TangentOutUpdated() override { Real()->m_PathNodes_TangentOut.NetworkStateChanged(); }
    CUtlVector<Vector>& PathNodes_Color() override { return Real()->m_PathNodes_Color(); }
    void PathNodes_ColorUpdated() override { Real()->m_PathNodes_Color.NetworkStateChanged(); }
    CUtlVector<bool>& PathNodes_PinEnabled() override { return Real()->m_PathNodes_PinEnabled(); }
    void PathNodes_PinEnabledUpdated() override { Real()->m_PathNodes_PinEnabled.NetworkStateChanged(); }
    CUtlVector<float>& PathNodes_RadiusScale() override { return Real()->m_PathNodes_RadiusScale(); }
    void PathNodes_RadiusScaleUpdated() override { Real()->m_PathNodes_RadiusScale.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPATHPARTICLEROPEIMPL_H
