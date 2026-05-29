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

#ifndef _INCLUDE_CDYNAMICPROPIMPL_H
#define _INCLUDE_CDYNAMICPROPIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IDynamicProp.h"
#include "schema/entity/classes/CDynamicProp.h"
#include "CBreakablePropImpl.h"

class CDynamicPropImpl : public CBreakablePropImpl, public IDynamicProp
{

public:
    explicit CDynamicPropImpl(CDynamicProp* p) : CBreakablePropImpl(p) {}

private:
    CDynamicProp* Real() { return static_cast<CDynamicProp*>(m_pReal); }
    CDynamicProp* Real() const { return static_cast<CDynamicProp*>(m_pReal); }

public:
    CDynamicProp* GetOriginal() const override { return Real(); }
    bool& CreateNavObstacle() override { return Real()->m_bCreateNavObstacle(); }
    void CreateNavObstacleUpdated() override { Real()->m_bCreateNavObstacle.NetworkStateChanged(); }
    bool& NavObstacleUpdatesOverridden() override { return Real()->m_bNavObstacleUpdatesOverridden(); }
    void NavObstacleUpdatesOverriddenUpdated() override { Real()->m_bNavObstacleUpdatesOverridden.NetworkStateChanged(); }
    bool& UseHitboxesForRenderBox() override { return Real()->m_bUseHitboxesForRenderBox(); }
    void UseHitboxesForRenderBoxUpdated() override { Real()->m_bUseHitboxesForRenderBox.NetworkStateChanged(); }
    bool& UseAnimGraph() override { return Real()->m_bUseAnimGraph(); }
    void UseAnimGraphUpdated() override { Real()->m_bUseAnimGraph.NetworkStateChanged(); }
    CEntityIOOutput& OutputAnimBegun() override { return Real()->m_pOutputAnimBegun(); }
    void OutputAnimBegunUpdated() override { Real()->m_pOutputAnimBegun.NetworkStateChanged(); }
    CEntityIOOutput& OutputAnimOver() override { return Real()->m_pOutputAnimOver(); }
    void OutputAnimOverUpdated() override { Real()->m_pOutputAnimOver.NetworkStateChanged(); }
    CEntityIOOutput& OutputAnimLoopCycleOver() override { return Real()->m_pOutputAnimLoopCycleOver(); }
    void OutputAnimLoopCycleOverUpdated() override { Real()->m_pOutputAnimLoopCycleOver.NetworkStateChanged(); }
    CEntityIOOutput& OnAnimReachedStart() override { return Real()->m_OnAnimReachedStart(); }
    void OnAnimReachedStartUpdated() override { Real()->m_OnAnimReachedStart.NetworkStateChanged(); }
    CEntityIOOutput& OnAnimReachedEnd() override { return Real()->m_OnAnimReachedEnd(); }
    void OnAnimReachedEndUpdated() override { Real()->m_OnAnimReachedEnd.NetworkStateChanged(); }
    CUtlSymbolLarge& IdleAnim() override { return Real()->m_iszIdleAnim(); }
    void IdleAnimUpdated() override { Real()->m_iszIdleAnim.NetworkStateChanged(); }
    AnimLoopMode_t& IdleAnimLoopMode() override { return Real()->m_nIdleAnimLoopMode(); }
    void IdleAnimLoopModeUpdated() override { Real()->m_nIdleAnimLoopMode.NetworkStateChanged(); }
    bool& RandomizeCycle() override { return Real()->m_bRandomizeCycle(); }
    void RandomizeCycleUpdated() override { Real()->m_bRandomizeCycle.NetworkStateChanged(); }
    bool& StartDisabled() override { return Real()->m_bStartDisabled(); }
    void StartDisabledUpdated() override { Real()->m_bStartDisabled.NetworkStateChanged(); }
    bool& FiredStartEndOutput() override { return Real()->m_bFiredStartEndOutput(); }
    void FiredStartEndOutputUpdated() override { Real()->m_bFiredStartEndOutput.NetworkStateChanged(); }
    bool& ForceNpcExclude() override { return Real()->m_bForceNpcExclude(); }
    void ForceNpcExcludeUpdated() override { Real()->m_bForceNpcExclude.NetworkStateChanged(); }
    bool& CreateNonSolid() override { return Real()->m_bCreateNonSolid(); }
    void CreateNonSolidUpdated() override { Real()->m_bCreateNonSolid.NetworkStateChanged(); }
    bool& IsOverrideProp() override { return Real()->m_bIsOverrideProp(); }
    void IsOverridePropUpdated() override { Real()->m_bIsOverrideProp.NetworkStateChanged(); }
    int32_t& InitialGlowState() override { return Real()->m_iInitialGlowState(); }
    void InitialGlowStateUpdated() override { Real()->m_iInitialGlowState.NetworkStateChanged(); }
    int32_t& GlowRange() override { return Real()->m_nGlowRange(); }
    void GlowRangeUpdated() override { Real()->m_nGlowRange.NetworkStateChanged(); }
    int32_t& GlowRangeMin() override { return Real()->m_nGlowRangeMin(); }
    void GlowRangeMinUpdated() override { Real()->m_nGlowRangeMin.NetworkStateChanged(); }
    Color& GlowColor() override { return Real()->m_glowColor(); }
    void GlowColorUpdated() override { Real()->m_glowColor.NetworkStateChanged(); }
    int32_t& GlowTeam() override { return Real()->m_nGlowTeam(); }
    void GlowTeamUpdated() override { Real()->m_nGlowTeam.NetworkStateChanged(); }
};

inline IDynamicProp* CDynamicProp::ToInterface() { return new CDynamicPropImpl(this); }
inline IDynamicProp* IDynamicProp::FromOriginal(CDynamicProp* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CDYNAMICPROPIMPL_H
