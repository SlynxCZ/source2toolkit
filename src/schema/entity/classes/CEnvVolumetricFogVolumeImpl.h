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

#ifndef _INCLUDE_CENVVOLUMETRICFOGVOLUMEIMPL_H
#define _INCLUDE_CENVVOLUMETRICFOGVOLUMEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvVolumetricFogVolume.h"
#include "schema/entity/classes/CEnvVolumetricFogVolume.h"
#include "CBaseEntityImpl.h"

class CEnvVolumetricFogVolumeImpl : public CBaseEntityImpl, public IEnvVolumetricFogVolume
{

public:
    explicit CEnvVolumetricFogVolumeImpl(CEnvVolumetricFogVolume* p) : CBaseEntityImpl(p) {}

private:
    CEnvVolumetricFogVolume* Real() { return static_cast<CEnvVolumetricFogVolume*>(m_pReal); }

public:
    bool& Active() override { return Real()->m_bActive(); }
    void ActiveUpdated() override { Real()->m_bActive.NetworkStateChanged(); }
    Vector& BoxMins() override { return Real()->m_vBoxMins(); }
    void BoxMinsUpdated() override { Real()->m_vBoxMins.NetworkStateChanged(); }
    Vector& BoxMaxs() override { return Real()->m_vBoxMaxs(); }
    void BoxMaxsUpdated() override { Real()->m_vBoxMaxs.NetworkStateChanged(); }
    bool& StartDisabled() override { return Real()->m_bStartDisabled(); }
    void StartDisabledUpdated() override { Real()->m_bStartDisabled.NetworkStateChanged(); }
    bool& IndirectUseLPVs() override { return Real()->m_bIndirectUseLPVs(); }
    void IndirectUseLPVsUpdated() override { Real()->m_bIndirectUseLPVs.NetworkStateChanged(); }
    float& Strength() override { return Real()->m_flStrength(); }
    void StrengthUpdated() override { Real()->m_flStrength.NetworkStateChanged(); }
    int32_t& FalloffShape() override { return Real()->m_nFalloffShape(); }
    void FalloffShapeUpdated() override { Real()->m_nFalloffShape.NetworkStateChanged(); }
    float& FalloffExponent() override { return Real()->m_flFalloffExponent(); }
    void FalloffExponentUpdated() override { Real()->m_flFalloffExponent.NetworkStateChanged(); }
    float& HeightFogDepth() override { return Real()->m_flHeightFogDepth(); }
    void HeightFogDepthUpdated() override { Real()->m_flHeightFogDepth.NetworkStateChanged(); }
    float& HeightFogEdgeWidth() override { return Real()->m_fHeightFogEdgeWidth(); }
    void HeightFogEdgeWidthUpdated() override { Real()->m_fHeightFogEdgeWidth.NetworkStateChanged(); }
    float& IndirectLightStrength() override { return Real()->m_fIndirectLightStrength(); }
    void IndirectLightStrengthUpdated() override { Real()->m_fIndirectLightStrength.NetworkStateChanged(); }
    float& SunLightStrength() override { return Real()->m_fSunLightStrength(); }
    void SunLightStrengthUpdated() override { Real()->m_fSunLightStrength.NetworkStateChanged(); }
    float& NoiseStrength() override { return Real()->m_fNoiseStrength(); }
    void NoiseStrengthUpdated() override { Real()->m_fNoiseStrength.NetworkStateChanged(); }
    Color& TintColor() override { return Real()->m_TintColor(); }
    void TintColorUpdated() override { Real()->m_TintColor.NetworkStateChanged(); }
    bool& OverrideTintColor() override { return Real()->m_bOverrideTintColor(); }
    void OverrideTintColorUpdated() override { Real()->m_bOverrideTintColor.NetworkStateChanged(); }
    bool& OverrideIndirectLightStrength() override { return Real()->m_bOverrideIndirectLightStrength(); }
    void OverrideIndirectLightStrengthUpdated() override { Real()->m_bOverrideIndirectLightStrength.NetworkStateChanged(); }
    bool& OverrideSunLightStrength() override { return Real()->m_bOverrideSunLightStrength(); }
    void OverrideSunLightStrengthUpdated() override { Real()->m_bOverrideSunLightStrength.NetworkStateChanged(); }
    bool& OverrideNoiseStrength() override { return Real()->m_bOverrideNoiseStrength(); }
    void OverrideNoiseStrengthUpdated() override { Real()->m_bOverrideNoiseStrength.NetworkStateChanged(); }
};

#endif // _INCLUDE_CENVVOLUMETRICFOGVOLUMEIMPL_H
