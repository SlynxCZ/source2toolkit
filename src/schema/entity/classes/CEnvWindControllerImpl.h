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

#ifndef _INCLUDE_CENVWINDCONTROLLERIMPL_H
#define _INCLUDE_CENVWINDCONTROLLERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvWindController.h"
#include "schema/entity/classes/CEnvWindController.h"
#include "CBaseEntityImpl.h"

class CEnvWindControllerImpl : public CBaseEntityImpl, public IEnvWindController
{

public:
    explicit CEnvWindControllerImpl(CEnvWindController* p) : CBaseEntityImpl(p) {}

private:
    CEnvWindController* Real() { return static_cast<CEnvWindController*>(m_pReal); }
    CEnvWindController* Real() const { return static_cast<CEnvWindController*>(m_pReal); }

public:
    CEnvWindController* GetOriginal() const override { return Real(); }
    ::CEnvWindShared& EnvWindShared() override { return Real()->m_EnvWindShared(); }
    void EnvWindSharedUpdated() override { Real()->m_EnvWindShared.NetworkStateChanged(); }
    float& DirectionVariation() override { return Real()->m_fDirectionVariation(); }
    void DirectionVariationUpdated() override { Real()->m_fDirectionVariation.NetworkStateChanged(); }
    float& SpeedVariation() override { return Real()->m_fSpeedVariation(); }
    void SpeedVariationUpdated() override { Real()->m_fSpeedVariation.NetworkStateChanged(); }
    float& Turbulence() override { return Real()->m_fTurbulence(); }
    void TurbulenceUpdated() override { Real()->m_fTurbulence.NetworkStateChanged(); }
    float& VolumeHalfExtentXY() override { return Real()->m_fVolumeHalfExtentXY(); }
    void VolumeHalfExtentXYUpdated() override { Real()->m_fVolumeHalfExtentXY.NetworkStateChanged(); }
    float& VolumeHalfExtentZ() override { return Real()->m_fVolumeHalfExtentZ(); }
    void VolumeHalfExtentZUpdated() override { Real()->m_fVolumeHalfExtentZ.NetworkStateChanged(); }
    int32_t& VolumeResolutionXY() override { return Real()->m_nVolumeResolutionXY(); }
    void VolumeResolutionXYUpdated() override { Real()->m_nVolumeResolutionXY.NetworkStateChanged(); }
    int32_t& VolumeResolutionZ() override { return Real()->m_nVolumeResolutionZ(); }
    void VolumeResolutionZUpdated() override { Real()->m_nVolumeResolutionZ.NetworkStateChanged(); }
    int32_t& ClipmapLevels() override { return Real()->m_nClipmapLevels(); }
    void ClipmapLevelsUpdated() override { Real()->m_nClipmapLevels.NetworkStateChanged(); }
    bool& IsMaster() override { return Real()->m_bIsMaster(); }
    void IsMasterUpdated() override { Real()->m_bIsMaster.NetworkStateChanged(); }
    bool& FirstTime() override { return Real()->m_bFirstTime(); }
    void FirstTimeUpdated() override { Real()->m_bFirstTime.NetworkStateChanged(); }
};

inline IEnvWindController* CEnvWindController::ToInterface() { return new CEnvWindControllerImpl(this); }
inline IEnvWindController* IEnvWindController::FromOriginal(CEnvWindController* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CENVWINDCONTROLLERIMPL_H
