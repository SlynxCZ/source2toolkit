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

#ifndef _INCLUDE_CSOUNDOPVARSETPOINTENTITYIMPL_H
#define _INCLUDE_CSOUNDOPVARSETPOINTENTITYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISoundOpvarSetPointEntity.h"
#include "schema/entity/classes/CSoundOpvarSetPointEntity.h"
#include "CSoundOpvarSetPointBaseImpl.h"

class CSoundOpvarSetPointEntityImpl : public CSoundOpvarSetPointBaseImpl, public ISoundOpvarSetPointEntity
{

public:
    explicit CSoundOpvarSetPointEntityImpl(CSoundOpvarSetPointEntity* p) : CSoundOpvarSetPointBaseImpl(p) {}

private:
    CSoundOpvarSetPointEntity* Real() { return static_cast<CSoundOpvarSetPointEntity*>(m_pReal); }
    CSoundOpvarSetPointEntity* Real() const { return static_cast<CSoundOpvarSetPointEntity*>(m_pReal); }

public:
    CSoundOpvarSetPointEntity* GetOriginal() const override { return Real(); }
    CEntityIOOutput& OnEnter() override { return Real()->m_OnEnter(); }
    void OnEnterUpdated() override { Real()->m_OnEnter.NetworkStateChanged(); }
    CEntityIOOutput& OnExit() override { return Real()->m_OnExit(); }
    void OnExitUpdated() override { Real()->m_OnExit.NetworkStateChanged(); }
    bool& AutoDisable() override { return Real()->m_bAutoDisable(); }
    void AutoDisableUpdated() override { Real()->m_bAutoDisable.NetworkStateChanged(); }
    float& DistanceMin() override { return Real()->m_flDistanceMin(); }
    void DistanceMinUpdated() override { Real()->m_flDistanceMin.NetworkStateChanged(); }
    float& DistanceMax() override { return Real()->m_flDistanceMax(); }
    void DistanceMaxUpdated() override { Real()->m_flDistanceMax.NetworkStateChanged(); }
    float& DistanceMapMin() override { return Real()->m_flDistanceMapMin(); }
    void DistanceMapMinUpdated() override { Real()->m_flDistanceMapMin.NetworkStateChanged(); }
    float& DistanceMapMax() override { return Real()->m_flDistanceMapMax(); }
    void DistanceMapMaxUpdated() override { Real()->m_flDistanceMapMax.NetworkStateChanged(); }
    float& OcclusionRadius() override { return Real()->m_flOcclusionRadius(); }
    void OcclusionRadiusUpdated() override { Real()->m_flOcclusionRadius.NetworkStateChanged(); }
    float& OcclusionMin() override { return Real()->m_flOcclusionMin(); }
    void OcclusionMinUpdated() override { Real()->m_flOcclusionMin.NetworkStateChanged(); }
    float& OcclusionMax() override { return Real()->m_flOcclusionMax(); }
    void OcclusionMaxUpdated() override { Real()->m_flOcclusionMax.NetworkStateChanged(); }
    float& ValSetOnDisable() override { return Real()->m_flValSetOnDisable(); }
    void ValSetOnDisableUpdated() override { Real()->m_flValSetOnDisable.NetworkStateChanged(); }
    bool& SetValueOnDisable() override { return Real()->m_bSetValueOnDisable(); }
    void SetValueOnDisableUpdated() override { Real()->m_bSetValueOnDisable.NetworkStateChanged(); }
    bool& Reloading() override { return Real()->m_bReloading(); }
    void ReloadingUpdated() override { Real()->m_bReloading.NetworkStateChanged(); }
    int32_t& SimulationMode() override { return Real()->m_nSimulationMode(); }
    void SimulationModeUpdated() override { Real()->m_nSimulationMode.NetworkStateChanged(); }
    int32_t& VisibilitySamples() override { return Real()->m_nVisibilitySamples(); }
    void VisibilitySamplesUpdated() override { Real()->m_nVisibilitySamples.NetworkStateChanged(); }
    Vector& DynamicProxyPoint() override { return Real()->m_vDynamicProxyPoint(); }
    void DynamicProxyPointUpdated() override { Real()->m_vDynamicProxyPoint.NetworkStateChanged(); }
    float& DynamicMaximumOcclusion() override { return Real()->m_flDynamicMaximumOcclusion(); }
    void DynamicMaximumOcclusionUpdated() override { Real()->m_flDynamicMaximumOcclusion.NetworkStateChanged(); }
    CEntityHandle& DynamicEntity() override { return Real()->m_hDynamicEntity(); }
    void DynamicEntityUpdated() override { Real()->m_hDynamicEntity.NetworkStateChanged(); }
    CUtlSymbolLarge& DynamicEntityName() override { return Real()->m_iszDynamicEntityName(); }
    void DynamicEntityNameUpdated() override { Real()->m_iszDynamicEntityName.NetworkStateChanged(); }
    float& PathingDistanceNormFactor() override { return Real()->m_flPathingDistanceNormFactor(); }
    void PathingDistanceNormFactorUpdated() override { Real()->m_flPathingDistanceNormFactor.NetworkStateChanged(); }
    Vector& PathingSourcePos() override { return Real()->m_vPathingSourcePos(); }
    void PathingSourcePosUpdated() override { Real()->m_vPathingSourcePos.NetworkStateChanged(); }
    Vector& PathingListenerPos() override { return Real()->m_vPathingListenerPos(); }
    void PathingListenerPosUpdated() override { Real()->m_vPathingListenerPos.NetworkStateChanged(); }
    Vector& PathingDirection() override { return Real()->m_vPathingDirection(); }
    void PathingDirectionUpdated() override { Real()->m_vPathingDirection.NetworkStateChanged(); }
    int32_t& PathingSourceIndex() override { return Real()->m_nPathingSourceIndex(); }
    void PathingSourceIndexUpdated() override { Real()->m_nPathingSourceIndex.NetworkStateChanged(); }
};

inline ISoundOpvarSetPointEntity* CSoundOpvarSetPointEntity::ToInterface() { return new CSoundOpvarSetPointEntityImpl(this); }
inline ISoundOpvarSetPointEntity* ISoundOpvarSetPointEntity::FromOriginal(CSoundOpvarSetPointEntity* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CSOUNDOPVARSETPOINTENTITYIMPL_H
