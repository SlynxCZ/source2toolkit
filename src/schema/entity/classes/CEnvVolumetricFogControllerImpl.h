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

#ifndef _INCLUDE_CENVVOLUMETRICFOGCONTROLLERIMPL_H
#define _INCLUDE_CENVVOLUMETRICFOGCONTROLLERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvVolumetricFogController.h"
#include "schema/entity/classes/CEnvVolumetricFogController.h"
#include "CBaseEntityImpl.h"

class CEnvVolumetricFogControllerImpl : public CBaseEntityImpl, public IEnvVolumetricFogController
{

public:
    explicit CEnvVolumetricFogControllerImpl(CEnvVolumetricFogController* p) : CBaseEntityImpl(p) {}

private:
    CEnvVolumetricFogController* Real() { return static_cast<CEnvVolumetricFogController*>(m_pReal); }

public:
    float& Scattering() override { return Real()->m_flScattering(); }
    void ScatteringUpdated() override { Real()->m_flScattering.NetworkStateChanged(); }
    Color& TintColor() override { return Real()->m_TintColor(); }
    void TintColorUpdated() override { Real()->m_TintColor.NetworkStateChanged(); }
    float& Anisotropy() override { return Real()->m_flAnisotropy(); }
    void AnisotropyUpdated() override { Real()->m_flAnisotropy.NetworkStateChanged(); }
    float& FadeSpeed() override { return Real()->m_flFadeSpeed(); }
    void FadeSpeedUpdated() override { Real()->m_flFadeSpeed.NetworkStateChanged(); }
    float& DrawDistance() override { return Real()->m_flDrawDistance(); }
    void DrawDistanceUpdated() override { Real()->m_flDrawDistance.NetworkStateChanged(); }
    float& FadeInStart() override { return Real()->m_flFadeInStart(); }
    void FadeInStartUpdated() override { Real()->m_flFadeInStart.NetworkStateChanged(); }
    float& FadeInEnd() override { return Real()->m_flFadeInEnd(); }
    void FadeInEndUpdated() override { Real()->m_flFadeInEnd.NetworkStateChanged(); }
    float& IndirectStrength() override { return Real()->m_flIndirectStrength(); }
    void IndirectStrengthUpdated() override { Real()->m_flIndirectStrength.NetworkStateChanged(); }
    int32_t& VolumeDepth() override { return Real()->m_nVolumeDepth(); }
    void VolumeDepthUpdated() override { Real()->m_nVolumeDepth.NetworkStateChanged(); }
    float& FirstVolumeSliceThickness() override { return Real()->m_fFirstVolumeSliceThickness(); }
    void FirstVolumeSliceThicknessUpdated() override { Real()->m_fFirstVolumeSliceThickness.NetworkStateChanged(); }
    int32_t& IndirectTextureDimX() override { return Real()->m_nIndirectTextureDimX(); }
    void IndirectTextureDimXUpdated() override { Real()->m_nIndirectTextureDimX.NetworkStateChanged(); }
    int32_t& IndirectTextureDimY() override { return Real()->m_nIndirectTextureDimY(); }
    void IndirectTextureDimYUpdated() override { Real()->m_nIndirectTextureDimY.NetworkStateChanged(); }
    int32_t& IndirectTextureDimZ() override { return Real()->m_nIndirectTextureDimZ(); }
    void IndirectTextureDimZUpdated() override { Real()->m_nIndirectTextureDimZ.NetworkStateChanged(); }
    Vector& BoxMins() override { return Real()->m_vBoxMins(); }
    void BoxMinsUpdated() override { Real()->m_vBoxMins.NetworkStateChanged(); }
    Vector& BoxMaxs() override { return Real()->m_vBoxMaxs(); }
    void BoxMaxsUpdated() override { Real()->m_vBoxMaxs.NetworkStateChanged(); }
    bool& Active() override { return Real()->m_bActive(); }
    void ActiveUpdated() override { Real()->m_bActive.NetworkStateChanged(); }
    float& StartAnisoTime() override { return Real()->m_flStartAnisoTime(); }
    void StartAnisoTimeUpdated() override { Real()->m_flStartAnisoTime.NetworkStateChanged(); }
    float& StartScatterTime() override { return Real()->m_flStartScatterTime(); }
    void StartScatterTimeUpdated() override { Real()->m_flStartScatterTime.NetworkStateChanged(); }
    float& StartDrawDistanceTime() override { return Real()->m_flStartDrawDistanceTime(); }
    void StartDrawDistanceTimeUpdated() override { Real()->m_flStartDrawDistanceTime.NetworkStateChanged(); }
    float& StartAnisotropy() override { return Real()->m_flStartAnisotropy(); }
    void StartAnisotropyUpdated() override { Real()->m_flStartAnisotropy.NetworkStateChanged(); }
    float& StartScattering() override { return Real()->m_flStartScattering(); }
    void StartScatteringUpdated() override { Real()->m_flStartScattering.NetworkStateChanged(); }
    float& StartDrawDistance() override { return Real()->m_flStartDrawDistance(); }
    void StartDrawDistanceUpdated() override { Real()->m_flStartDrawDistance.NetworkStateChanged(); }
    float& DefaultAnisotropy() override { return Real()->m_flDefaultAnisotropy(); }
    void DefaultAnisotropyUpdated() override { Real()->m_flDefaultAnisotropy.NetworkStateChanged(); }
    float& DefaultScattering() override { return Real()->m_flDefaultScattering(); }
    void DefaultScatteringUpdated() override { Real()->m_flDefaultScattering.NetworkStateChanged(); }
    float& DefaultDrawDistance() override { return Real()->m_flDefaultDrawDistance(); }
    void DefaultDrawDistanceUpdated() override { Real()->m_flDefaultDrawDistance.NetworkStateChanged(); }
    bool& StartDisabled() override { return Real()->m_bStartDisabled(); }
    void StartDisabledUpdated() override { Real()->m_bStartDisabled.NetworkStateChanged(); }
    bool& EnableIndirect() override { return Real()->m_bEnableIndirect(); }
    void EnableIndirectUpdated() override { Real()->m_bEnableIndirect.NetworkStateChanged(); }
    bool& IsMaster() override { return Real()->m_bIsMaster(); }
    void IsMasterUpdated() override { Real()->m_bIsMaster.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& FogIndirectTexture() override { return Real()->m_hFogIndirectTexture(); }
    void FogIndirectTextureUpdated() override { Real()->m_hFogIndirectTexture.NetworkStateChanged(); }
    int32_t& ForceRefreshCount() override { return Real()->m_nForceRefreshCount(); }
    void ForceRefreshCountUpdated() override { Real()->m_nForceRefreshCount.NetworkStateChanged(); }
    float& NoiseSpeed() override { return Real()->m_fNoiseSpeed(); }
    void NoiseSpeedUpdated() override { Real()->m_fNoiseSpeed.NetworkStateChanged(); }
    float& NoiseStrength() override { return Real()->m_fNoiseStrength(); }
    void NoiseStrengthUpdated() override { Real()->m_fNoiseStrength.NetworkStateChanged(); }
    Vector& NoiseScale() override { return Real()->m_vNoiseScale(); }
    void NoiseScaleUpdated() override { Real()->m_vNoiseScale.NetworkStateChanged(); }
    float& WindSpeed() override { return Real()->m_fWindSpeed(); }
    void WindSpeedUpdated() override { Real()->m_fWindSpeed.NetworkStateChanged(); }
    Vector& WindDirection() override { return Real()->m_vWindDirection(); }
    void WindDirectionUpdated() override { Real()->m_vWindDirection.NetworkStateChanged(); }
    bool& FirstTime() override { return Real()->m_bFirstTime(); }
    void FirstTimeUpdated() override { Real()->m_bFirstTime.NetworkStateChanged(); }
};

#endif // _INCLUDE_CENVVOLUMETRICFOGCONTROLLERIMPL_H
