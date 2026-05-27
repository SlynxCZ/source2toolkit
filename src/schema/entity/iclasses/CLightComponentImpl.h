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

#ifndef _INCLUDE_CLIGHTCOMPONENTIMPL_H
#define _INCLUDE_CLIGHTCOMPONENTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/ILightComponent.h"
#include "schema/entity/classes/CLightComponent.h"

class CLightComponentImpl : public virtual ILightComponent
{

protected:
    void* m_pReal;

public:
    explicit CLightComponentImpl(void* p) : m_pReal(p) {}

private:
    CLightComponent* Real() { return static_cast<CLightComponent*>(m_pReal); }

public:
    CEntityInstance*& __m_pChainEntity() override { return Real()->__m_pChainEntity(); }
    void __m_pChainEntityUpdated() override { Real()->__m_pChainEntity.NetworkStateChanged(); }
    Color& Color() override { return Real()->m_Color(); }
    void ColorUpdated() override { Real()->m_Color.NetworkStateChanged(); }
    Color& SecondaryColor() override { return Real()->m_SecondaryColor(); }
    void SecondaryColorUpdated() override { Real()->m_SecondaryColor.NetworkStateChanged(); }
    float& Brightness() override { return Real()->m_flBrightness(); }
    void BrightnessUpdated() override { Real()->m_flBrightness.NetworkStateChanged(); }
    float& BrightnessScale() override { return Real()->m_flBrightnessScale(); }
    void BrightnessScaleUpdated() override { Real()->m_flBrightnessScale.NetworkStateChanged(); }
    float& BrightnessMult() override { return Real()->m_flBrightnessMult(); }
    void BrightnessMultUpdated() override { Real()->m_flBrightnessMult.NetworkStateChanged(); }
    float& Range() override { return Real()->m_flRange(); }
    void RangeUpdated() override { Real()->m_flRange.NetworkStateChanged(); }
    float& Falloff() override { return Real()->m_flFalloff(); }
    void FalloffUpdated() override { Real()->m_flFalloff.NetworkStateChanged(); }
    float& Attenuation0() override { return Real()->m_flAttenuation0(); }
    void Attenuation0Updated() override { Real()->m_flAttenuation0.NetworkStateChanged(); }
    float& Attenuation1() override { return Real()->m_flAttenuation1(); }
    void Attenuation1Updated() override { Real()->m_flAttenuation1.NetworkStateChanged(); }
    float& Attenuation2() override { return Real()->m_flAttenuation2(); }
    void Attenuation2Updated() override { Real()->m_flAttenuation2.NetworkStateChanged(); }
    float& Theta() override { return Real()->m_flTheta(); }
    void ThetaUpdated() override { Real()->m_flTheta.NetworkStateChanged(); }
    float& Phi() override { return Real()->m_flPhi(); }
    void PhiUpdated() override { Real()->m_flPhi.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& LightCookie() override { return Real()->m_hLightCookie(); }
    void LightCookieUpdated() override { Real()->m_hLightCookie.NetworkStateChanged(); }
    int32_t& Cascades() override { return Real()->m_nCascades(); }
    void CascadesUpdated() override { Real()->m_nCascades.NetworkStateChanged(); }
    int32_t& CastShadows() override { return Real()->m_nCastShadows(); }
    void CastShadowsUpdated() override { Real()->m_nCastShadows.NetworkStateChanged(); }
    int32_t& ShadowWidth() override { return Real()->m_nShadowWidth(); }
    void ShadowWidthUpdated() override { Real()->m_nShadowWidth.NetworkStateChanged(); }
    int32_t& ShadowHeight() override { return Real()->m_nShadowHeight(); }
    void ShadowHeightUpdated() override { Real()->m_nShadowHeight.NetworkStateChanged(); }
    bool& RenderDiffuse() override { return Real()->m_bRenderDiffuse(); }
    void RenderDiffuseUpdated() override { Real()->m_bRenderDiffuse.NetworkStateChanged(); }
    int32_t& RenderSpecular() override { return Real()->m_nRenderSpecular(); }
    void RenderSpecularUpdated() override { Real()->m_nRenderSpecular.NetworkStateChanged(); }
    bool& RenderTransmissive() override { return Real()->m_bRenderTransmissive(); }
    void RenderTransmissiveUpdated() override { Real()->m_bRenderTransmissive.NetworkStateChanged(); }
    float& OrthoLightWidth() override { return Real()->m_flOrthoLightWidth(); }
    void OrthoLightWidthUpdated() override { Real()->m_flOrthoLightWidth.NetworkStateChanged(); }
    float& OrthoLightHeight() override { return Real()->m_flOrthoLightHeight(); }
    void OrthoLightHeightUpdated() override { Real()->m_flOrthoLightHeight.NetworkStateChanged(); }
    int32_t& Style() override { return Real()->m_nStyle(); }
    void StyleUpdated() override { Real()->m_nStyle.NetworkStateChanged(); }
    CUtlString& Pattern() override { return Real()->m_Pattern(); }
    void PatternUpdated() override { Real()->m_Pattern.NetworkStateChanged(); }
    int32_t& CascadeRenderStaticObjects() override { return Real()->m_nCascadeRenderStaticObjects(); }
    void CascadeRenderStaticObjectsUpdated() override { Real()->m_nCascadeRenderStaticObjects.NetworkStateChanged(); }
    float& ShadowCascadeCrossFade() override { return Real()->m_flShadowCascadeCrossFade(); }
    void ShadowCascadeCrossFadeUpdated() override { Real()->m_flShadowCascadeCrossFade.NetworkStateChanged(); }
    float& ShadowCascadeDistanceFade() override { return Real()->m_flShadowCascadeDistanceFade(); }
    void ShadowCascadeDistanceFadeUpdated() override { Real()->m_flShadowCascadeDistanceFade.NetworkStateChanged(); }
    float& ShadowCascadeDistance0() override { return Real()->m_flShadowCascadeDistance0(); }
    void ShadowCascadeDistance0Updated() override { Real()->m_flShadowCascadeDistance0.NetworkStateChanged(); }
    float& ShadowCascadeDistance1() override { return Real()->m_flShadowCascadeDistance1(); }
    void ShadowCascadeDistance1Updated() override { Real()->m_flShadowCascadeDistance1.NetworkStateChanged(); }
    float& ShadowCascadeDistance2() override { return Real()->m_flShadowCascadeDistance2(); }
    void ShadowCascadeDistance2Updated() override { Real()->m_flShadowCascadeDistance2.NetworkStateChanged(); }
    float& ShadowCascadeDistance3() override { return Real()->m_flShadowCascadeDistance3(); }
    void ShadowCascadeDistance3Updated() override { Real()->m_flShadowCascadeDistance3.NetworkStateChanged(); }
    int32_t& ShadowCascadeResolution0() override { return Real()->m_nShadowCascadeResolution0(); }
    void ShadowCascadeResolution0Updated() override { Real()->m_nShadowCascadeResolution0.NetworkStateChanged(); }
    int32_t& ShadowCascadeResolution1() override { return Real()->m_nShadowCascadeResolution1(); }
    void ShadowCascadeResolution1Updated() override { Real()->m_nShadowCascadeResolution1.NetworkStateChanged(); }
    int32_t& ShadowCascadeResolution2() override { return Real()->m_nShadowCascadeResolution2(); }
    void ShadowCascadeResolution2Updated() override { Real()->m_nShadowCascadeResolution2.NetworkStateChanged(); }
    int32_t& ShadowCascadeResolution3() override { return Real()->m_nShadowCascadeResolution3(); }
    void ShadowCascadeResolution3Updated() override { Real()->m_nShadowCascadeResolution3.NetworkStateChanged(); }
    bool& UsesBakedShadowing() override { return Real()->m_bUsesBakedShadowing(); }
    void UsesBakedShadowingUpdated() override { Real()->m_bUsesBakedShadowing.NetworkStateChanged(); }
    int32_t& ShadowPriority() override { return Real()->m_nShadowPriority(); }
    void ShadowPriorityUpdated() override { Real()->m_nShadowPriority.NetworkStateChanged(); }
    int32_t& BakedShadowIndex() override { return Real()->m_nBakedShadowIndex(); }
    void BakedShadowIndexUpdated() override { Real()->m_nBakedShadowIndex.NetworkStateChanged(); }
    int32_t& LightPathUniqueId() override { return Real()->m_nLightPathUniqueId(); }
    void LightPathUniqueIdUpdated() override { Real()->m_nLightPathUniqueId.NetworkStateChanged(); }
    int32_t& LightMapUniqueId() override { return Real()->m_nLightMapUniqueId(); }
    void LightMapUniqueIdUpdated() override { Real()->m_nLightMapUniqueId.NetworkStateChanged(); }
    bool& RenderToCubemaps() override { return Real()->m_bRenderToCubemaps(); }
    void RenderToCubemapsUpdated() override { Real()->m_bRenderToCubemaps.NetworkStateChanged(); }
    bool& AllowSSTGeneration() override { return Real()->m_bAllowSSTGeneration(); }
    void AllowSSTGenerationUpdated() override { Real()->m_bAllowSSTGeneration.NetworkStateChanged(); }
    int32_t& DirectLight() override { return Real()->m_nDirectLight(); }
    void DirectLightUpdated() override { Real()->m_nDirectLight.NetworkStateChanged(); }
    int32_t& BounceLight() override { return Real()->m_nBounceLight(); }
    void BounceLightUpdated() override { Real()->m_nBounceLight.NetworkStateChanged(); }
    float& BounceScale() override { return Real()->m_flBounceScale(); }
    void BounceScaleUpdated() override { Real()->m_flBounceScale.NetworkStateChanged(); }
    float& FadeMinDist() override { return Real()->m_flFadeMinDist(); }
    void FadeMinDistUpdated() override { Real()->m_flFadeMinDist.NetworkStateChanged(); }
    float& FadeMaxDist() override { return Real()->m_flFadeMaxDist(); }
    void FadeMaxDistUpdated() override { Real()->m_flFadeMaxDist.NetworkStateChanged(); }
    float& ShadowFadeMinDist() override { return Real()->m_flShadowFadeMinDist(); }
    void ShadowFadeMinDistUpdated() override { Real()->m_flShadowFadeMinDist.NetworkStateChanged(); }
    float& ShadowFadeMaxDist() override { return Real()->m_flShadowFadeMaxDist(); }
    void ShadowFadeMaxDistUpdated() override { Real()->m_flShadowFadeMaxDist.NetworkStateChanged(); }
    bool& Enabled() override { return Real()->m_bEnabled(); }
    void EnabledUpdated() override { Real()->m_bEnabled.NetworkStateChanged(); }
    bool& Flicker() override { return Real()->m_bFlicker(); }
    void FlickerUpdated() override { Real()->m_bFlicker.NetworkStateChanged(); }
    bool& PrecomputedFieldsValid() override { return Real()->m_bPrecomputedFieldsValid(); }
    void PrecomputedFieldsValidUpdated() override { Real()->m_bPrecomputedFieldsValid.NetworkStateChanged(); }
    Vector& PrecomputedBoundsMins() override { return Real()->m_vPrecomputedBoundsMins(); }
    void PrecomputedBoundsMinsUpdated() override { Real()->m_vPrecomputedBoundsMins.NetworkStateChanged(); }
    Vector& PrecomputedBoundsMaxs() override { return Real()->m_vPrecomputedBoundsMaxs(); }
    void PrecomputedBoundsMaxsUpdated() override { Real()->m_vPrecomputedBoundsMaxs.NetworkStateChanged(); }
    Vector& PrecomputedOBBOrigin() override { return Real()->m_vPrecomputedOBBOrigin(); }
    void PrecomputedOBBOriginUpdated() override { Real()->m_vPrecomputedOBBOrigin.NetworkStateChanged(); }
    QAngle& PrecomputedOBBAngles() override { return Real()->m_vPrecomputedOBBAngles(); }
    void PrecomputedOBBAnglesUpdated() override { Real()->m_vPrecomputedOBBAngles.NetworkStateChanged(); }
    Vector& PrecomputedOBBExtent() override { return Real()->m_vPrecomputedOBBExtent(); }
    void PrecomputedOBBExtentUpdated() override { Real()->m_vPrecomputedOBBExtent.NetworkStateChanged(); }
    float& PrecomputedMaxRange() override { return Real()->m_flPrecomputedMaxRange(); }
    void PrecomputedMaxRangeUpdated() override { Real()->m_flPrecomputedMaxRange.NetworkStateChanged(); }
    int32_t& FogLightingMode() override { return Real()->m_nFogLightingMode(); }
    void FogLightingModeUpdated() override { Real()->m_nFogLightingMode.NetworkStateChanged(); }
    float& FogContributionStength() override { return Real()->m_flFogContributionStength(); }
    void FogContributionStengthUpdated() override { Real()->m_flFogContributionStength.NetworkStateChanged(); }
    float& NearClipPlane() override { return Real()->m_flNearClipPlane(); }
    void NearClipPlaneUpdated() override { Real()->m_flNearClipPlane.NetworkStateChanged(); }
    Color& SkyColor() override { return Real()->m_SkyColor(); }
    void SkyColorUpdated() override { Real()->m_SkyColor.NetworkStateChanged(); }
    float& SkyIntensity() override { return Real()->m_flSkyIntensity(); }
    void SkyIntensityUpdated() override { Real()->m_flSkyIntensity.NetworkStateChanged(); }
    Color& SkyAmbientBounce() override { return Real()->m_SkyAmbientBounce(); }
    void SkyAmbientBounceUpdated() override { Real()->m_SkyAmbientBounce.NetworkStateChanged(); }
    bool& UseSecondaryColor() override { return Real()->m_bUseSecondaryColor(); }
    void UseSecondaryColorUpdated() override { Real()->m_bUseSecondaryColor.NetworkStateChanged(); }
    bool& MixedShadows() override { return Real()->m_bMixedShadows(); }
    void MixedShadowsUpdated() override { Real()->m_bMixedShadows.NetworkStateChanged(); }
    float& LightStyleStartTime() override { return Real()->m_flLightStyleStartTime(); }
    void LightStyleStartTimeUpdated() override { Real()->m_flLightStyleStartTime.NetworkStateChanged(); }
    float& CapsuleLength() override { return Real()->m_flCapsuleLength(); }
    void CapsuleLengthUpdated() override { Real()->m_flCapsuleLength.NetworkStateChanged(); }
    float& MinRoughness() override { return Real()->m_flMinRoughness(); }
    void MinRoughnessUpdated() override { Real()->m_flMinRoughness.NetworkStateChanged(); }
    bool& PvsModifyEntity() override { return Real()->m_bPvsModifyEntity(); }
    void PvsModifyEntityUpdated() override { Real()->m_bPvsModifyEntity.NetworkStateChanged(); }
};

#endif // _INCLUDE_CLIGHTCOMPONENTIMPL_H
