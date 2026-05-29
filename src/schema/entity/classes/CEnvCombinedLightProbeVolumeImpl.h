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

#ifndef _INCLUDE_CENVCOMBINEDLIGHTPROBEVOLUMEIMPL_H
#define _INCLUDE_CENVCOMBINEDLIGHTPROBEVOLUMEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvCombinedLightProbeVolume.h"
#include "schema/entity/classes/CEnvCombinedLightProbeVolume.h"
#include "CBaseEntityImpl.h"

class CEnvCombinedLightProbeVolumeImpl : public CBaseEntityImpl, public IEnvCombinedLightProbeVolume
{

public:
    explicit CEnvCombinedLightProbeVolumeImpl(CEnvCombinedLightProbeVolume* p) : CBaseEntityImpl(p) {}

private:
    CEnvCombinedLightProbeVolume* Real() { return static_cast<CEnvCombinedLightProbeVolume*>(m_pReal); }
    CEnvCombinedLightProbeVolume* Real() const { return static_cast<CEnvCombinedLightProbeVolume*>(m_pReal); }

public:
    CEnvCombinedLightProbeVolume* GetOriginal() const override { return Real(); }
    Color& Entity_Color() override { return Real()->m_Entity_Color(); }
    void Entity_ColorUpdated() override { Real()->m_Entity_Color.NetworkStateChanged(); }
    float& Entity_flBrightness() override { return Real()->m_Entity_flBrightness(); }
    void Entity_flBrightnessUpdated() override { Real()->m_Entity_flBrightness.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& Entity_hCubemapTexture() override { return Real()->m_Entity_hCubemapTexture(); }
    void Entity_hCubemapTextureUpdated() override { Real()->m_Entity_hCubemapTexture.NetworkStateChanged(); }
    bool& Entity_bCustomCubemapTexture() override { return Real()->m_Entity_bCustomCubemapTexture(); }
    void Entity_bCustomCubemapTextureUpdated() override { Real()->m_Entity_bCustomCubemapTexture.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& Entity_hLightProbeTexture_AmbientCube() override { return Real()->m_Entity_hLightProbeTexture_AmbientCube(); }
    void Entity_hLightProbeTexture_AmbientCubeUpdated() override { Real()->m_Entity_hLightProbeTexture_AmbientCube.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& Entity_hLightProbeTexture_SDF() override { return Real()->m_Entity_hLightProbeTexture_SDF(); }
    void Entity_hLightProbeTexture_SDFUpdated() override { Real()->m_Entity_hLightProbeTexture_SDF.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& Entity_hLightProbeTexture_SH2_DC() override { return Real()->m_Entity_hLightProbeTexture_SH2_DC(); }
    void Entity_hLightProbeTexture_SH2_DCUpdated() override { Real()->m_Entity_hLightProbeTexture_SH2_DC.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& Entity_hLightProbeTexture_SH2_R() override { return Real()->m_Entity_hLightProbeTexture_SH2_R(); }
    void Entity_hLightProbeTexture_SH2_RUpdated() override { Real()->m_Entity_hLightProbeTexture_SH2_R.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& Entity_hLightProbeTexture_SH2_G() override { return Real()->m_Entity_hLightProbeTexture_SH2_G(); }
    void Entity_hLightProbeTexture_SH2_GUpdated() override { Real()->m_Entity_hLightProbeTexture_SH2_G.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& Entity_hLightProbeTexture_SH2_B() override { return Real()->m_Entity_hLightProbeTexture_SH2_B(); }
    void Entity_hLightProbeTexture_SH2_BUpdated() override { Real()->m_Entity_hLightProbeTexture_SH2_B.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& Entity_hLightProbeDirectLightIndicesTexture() override { return Real()->m_Entity_hLightProbeDirectLightIndicesTexture(); }
    void Entity_hLightProbeDirectLightIndicesTextureUpdated() override { Real()->m_Entity_hLightProbeDirectLightIndicesTexture.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& Entity_hLightProbeDirectLightScalarsTexture() override { return Real()->m_Entity_hLightProbeDirectLightScalarsTexture(); }
    void Entity_hLightProbeDirectLightScalarsTextureUpdated() override { Real()->m_Entity_hLightProbeDirectLightScalarsTexture.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& Entity_hLightProbeDirectLightShadowsTexture() override { return Real()->m_Entity_hLightProbeDirectLightShadowsTexture(); }
    void Entity_hLightProbeDirectLightShadowsTextureUpdated() override { Real()->m_Entity_hLightProbeDirectLightShadowsTexture.NetworkStateChanged(); }
    Vector& Entity_vBoxMins() override { return Real()->m_Entity_vBoxMins(); }
    void Entity_vBoxMinsUpdated() override { Real()->m_Entity_vBoxMins.NetworkStateChanged(); }
    Vector& Entity_vBoxMaxs() override { return Real()->m_Entity_vBoxMaxs(); }
    void Entity_vBoxMaxsUpdated() override { Real()->m_Entity_vBoxMaxs.NetworkStateChanged(); }
    bool& Entity_bMoveable() override { return Real()->m_Entity_bMoveable(); }
    void Entity_bMoveableUpdated() override { Real()->m_Entity_bMoveable.NetworkStateChanged(); }
    int32_t& Entity_nHandshake() override { return Real()->m_Entity_nHandshake(); }
    void Entity_nHandshakeUpdated() override { Real()->m_Entity_nHandshake.NetworkStateChanged(); }
    int32_t& Entity_nEnvCubeMapArrayIndex() override { return Real()->m_Entity_nEnvCubeMapArrayIndex(); }
    void Entity_nEnvCubeMapArrayIndexUpdated() override { Real()->m_Entity_nEnvCubeMapArrayIndex.NetworkStateChanged(); }
    int32_t& Entity_nPriority() override { return Real()->m_Entity_nPriority(); }
    void Entity_nPriorityUpdated() override { Real()->m_Entity_nPriority.NetworkStateChanged(); }
    bool& Entity_bStartDisabled() override { return Real()->m_Entity_bStartDisabled(); }
    void Entity_bStartDisabledUpdated() override { Real()->m_Entity_bStartDisabled.NetworkStateChanged(); }
    float& Entity_flEdgeFadeDist() override { return Real()->m_Entity_flEdgeFadeDist(); }
    void Entity_flEdgeFadeDistUpdated() override { Real()->m_Entity_flEdgeFadeDist.NetworkStateChanged(); }
    Vector& Entity_vEdgeFadeDists() override { return Real()->m_Entity_vEdgeFadeDists(); }
    void Entity_vEdgeFadeDistsUpdated() override { Real()->m_Entity_vEdgeFadeDists.NetworkStateChanged(); }
    int32_t& Entity_nLightProbeSizeX() override { return Real()->m_Entity_nLightProbeSizeX(); }
    void Entity_nLightProbeSizeXUpdated() override { Real()->m_Entity_nLightProbeSizeX.NetworkStateChanged(); }
    int32_t& Entity_nLightProbeSizeY() override { return Real()->m_Entity_nLightProbeSizeY(); }
    void Entity_nLightProbeSizeYUpdated() override { Real()->m_Entity_nLightProbeSizeY.NetworkStateChanged(); }
    int32_t& Entity_nLightProbeSizeZ() override { return Real()->m_Entity_nLightProbeSizeZ(); }
    void Entity_nLightProbeSizeZUpdated() override { Real()->m_Entity_nLightProbeSizeZ.NetworkStateChanged(); }
    int32_t& Entity_nLightProbeAtlasX() override { return Real()->m_Entity_nLightProbeAtlasX(); }
    void Entity_nLightProbeAtlasXUpdated() override { Real()->m_Entity_nLightProbeAtlasX.NetworkStateChanged(); }
    int32_t& Entity_nLightProbeAtlasY() override { return Real()->m_Entity_nLightProbeAtlasY(); }
    void Entity_nLightProbeAtlasYUpdated() override { Real()->m_Entity_nLightProbeAtlasY.NetworkStateChanged(); }
    int32_t& Entity_nLightProbeAtlasZ() override { return Real()->m_Entity_nLightProbeAtlasZ(); }
    void Entity_nLightProbeAtlasZUpdated() override { Real()->m_Entity_nLightProbeAtlasZ.NetworkStateChanged(); }
    bool& Entity_bEnabled() override { return Real()->m_Entity_bEnabled(); }
    void Entity_bEnabledUpdated() override { Real()->m_Entity_bEnabled.NetworkStateChanged(); }
};

inline IEnvCombinedLightProbeVolume* CEnvCombinedLightProbeVolume::ToInterface() { return new CEnvCombinedLightProbeVolumeImpl(this); }
inline IEnvCombinedLightProbeVolume* IEnvCombinedLightProbeVolume::FromOriginal(CEnvCombinedLightProbeVolume* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CENVCOMBINEDLIGHTPROBEVOLUMEIMPL_H
