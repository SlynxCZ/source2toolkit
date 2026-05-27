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

#ifndef _INCLUDE_CENVCUBEMAPFOGIMPL_H
#define _INCLUDE_CENVCUBEMAPFOGIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvCubemapFog.h"
#include "schema/entity/classes/CEnvCubemapFog.h"
#include "CBaseEntityImpl.h"

class CEnvCubemapFogImpl : public CBaseEntityImpl, public IEnvCubemapFog
{

public:
    explicit CEnvCubemapFogImpl(CEnvCubemapFog* p) : CBaseEntityImpl(p) {}

private:
    CEnvCubemapFog* Real() { return static_cast<CEnvCubemapFog*>(m_pReal); }

public:
    float& EndDistance() override { return Real()->m_flEndDistance(); }
    void EndDistanceUpdated() override { Real()->m_flEndDistance.NetworkStateChanged(); }
    float& StartDistance() override { return Real()->m_flStartDistance(); }
    void StartDistanceUpdated() override { Real()->m_flStartDistance.NetworkStateChanged(); }
    float& FogFalloffExponent() override { return Real()->m_flFogFalloffExponent(); }
    void FogFalloffExponentUpdated() override { Real()->m_flFogFalloffExponent.NetworkStateChanged(); }
    bool& HeightFogEnabled() override { return Real()->m_bHeightFogEnabled(); }
    void HeightFogEnabledUpdated() override { Real()->m_bHeightFogEnabled.NetworkStateChanged(); }
    float& FogHeightWidth() override { return Real()->m_flFogHeightWidth(); }
    void FogHeightWidthUpdated() override { Real()->m_flFogHeightWidth.NetworkStateChanged(); }
    float& FogHeightEnd() override { return Real()->m_flFogHeightEnd(); }
    void FogHeightEndUpdated() override { Real()->m_flFogHeightEnd.NetworkStateChanged(); }
    float& FogHeightStart() override { return Real()->m_flFogHeightStart(); }
    void FogHeightStartUpdated() override { Real()->m_flFogHeightStart.NetworkStateChanged(); }
    float& FogHeightExponent() override { return Real()->m_flFogHeightExponent(); }
    void FogHeightExponentUpdated() override { Real()->m_flFogHeightExponent.NetworkStateChanged(); }
    float& LODBias() override { return Real()->m_flLODBias(); }
    void LODBiasUpdated() override { Real()->m_flLODBias.NetworkStateChanged(); }
    bool& Active() override { return Real()->m_bActive(); }
    void ActiveUpdated() override { Real()->m_bActive.NetworkStateChanged(); }
    bool& StartDisabled() override { return Real()->m_bStartDisabled(); }
    void StartDisabledUpdated() override { Real()->m_bStartDisabled.NetworkStateChanged(); }
    float& FogMaxOpacity() override { return Real()->m_flFogMaxOpacity(); }
    void FogMaxOpacityUpdated() override { Real()->m_flFogMaxOpacity.NetworkStateChanged(); }
    int32_t& CubemapSourceType() override { return Real()->m_nCubemapSourceType(); }
    void CubemapSourceTypeUpdated() override { Real()->m_nCubemapSourceType.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIMaterial2>& SkyMaterial() override { return Real()->m_hSkyMaterial(); }
    void SkyMaterialUpdated() override { Real()->m_hSkyMaterial.NetworkStateChanged(); }
    CUtlSymbolLarge& SkyEntity() override { return Real()->m_iszSkyEntity(); }
    void SkyEntityUpdated() override { Real()->m_iszSkyEntity.NetworkStateChanged(); }
    int32_t& HeightFogType() override { return Real()->m_nHeightFogType(); }
    void HeightFogTypeUpdated() override { Real()->m_nHeightFogType.NetworkStateChanged(); }
    int32_t& FogHeightBlendMode() override { return Real()->m_nFogHeightBlendMode(); }
    void FogHeightBlendModeUpdated() override { Real()->m_nFogHeightBlendMode.NetworkStateChanged(); }
    int32_t& FogHeightCoordinateSpace() override { return Real()->m_nFogHeightCoordinateSpace(); }
    void FogHeightCoordinateSpaceUpdated() override { Real()->m_nFogHeightCoordinateSpace.NetworkStateChanged(); }
    int32_t& DistanceFogType() override { return Real()->m_nDistanceFogType(); }
    void DistanceFogTypeUpdated() override { Real()->m_nDistanceFogType.NetworkStateChanged(); }
    CUtlSymbolLarge& DistanceFogCurveString() override { return Real()->m_DistanceFogCurveString(); }
    void DistanceFogCurveStringUpdated() override { Real()->m_DistanceFogCurveString.NetworkStateChanged(); }
    CUtlSymbolLarge& HeightFogCurveString() override { return Real()->m_HeightFogCurveString(); }
    void HeightFogCurveStringUpdated() override { Real()->m_HeightFogCurveString.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& FogCubemapTexture() override { return Real()->m_hFogCubemapTexture(); }
    void FogCubemapTextureUpdated() override { Real()->m_hFogCubemapTexture.NetworkStateChanged(); }
    bool& HasHeightFogEnd() override { return Real()->m_bHasHeightFogEnd(); }
    void HasHeightFogEndUpdated() override { Real()->m_bHasHeightFogEnd.NetworkStateChanged(); }
    bool& FirstTime() override { return Real()->m_bFirstTime(); }
    void FirstTimeUpdated() override { Real()->m_bFirstTime.NetworkStateChanged(); }
};

#endif // _INCLUDE_CENVCUBEMAPFOGIMPL_H
