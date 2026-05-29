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

#ifndef _INCLUDE_CBARNLIGHTIMPL_H
#define _INCLUDE_CBARNLIGHTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBarnLight.h"
#include "schema/entity/classes/CBarnLight.h"
#include "CBaseModelEntityImpl.h"

class CBarnLightImpl : public CBaseModelEntityImpl, public virtual IBarnLight
{

public:
    explicit CBarnLightImpl(CBarnLight* p) : CBaseModelEntityImpl(p) {}

private:
    CBarnLight* Real() { return static_cast<CBarnLight*>(m_pReal); }
    CBarnLight* Real() const { return static_cast<CBarnLight*>(m_pReal); }

public:
    CBarnLight* GetOriginal() const override { return Real(); }
    bool& Enabled() override { return Real()->m_bEnabled(); }
    void EnabledUpdated() override { Real()->m_bEnabled.NetworkStateChanged(); }
    int32_t& ColorMode() override { return Real()->m_nColorMode(); }
    void ColorModeUpdated() override { Real()->m_nColorMode.NetworkStateChanged(); }
    Color& Color() override { return Real()->m_Color(); }
    void ColorUpdated() override { Real()->m_Color.NetworkStateChanged(); }
    float& ColorTemperature() override { return Real()->m_flColorTemperature(); }
    void ColorTemperatureUpdated() override { Real()->m_flColorTemperature.NetworkStateChanged(); }
    float& Brightness() override { return Real()->m_flBrightness(); }
    void BrightnessUpdated() override { Real()->m_flBrightness.NetworkStateChanged(); }
    float& BrightnessScale() override { return Real()->m_flBrightnessScale(); }
    void BrightnessScaleUpdated() override { Real()->m_flBrightnessScale.NetworkStateChanged(); }
    int32_t& DirectLight() override { return Real()->m_nDirectLight(); }
    void DirectLightUpdated() override { Real()->m_nDirectLight.NetworkStateChanged(); }
    int32_t& BakedShadowIndex() override { return Real()->m_nBakedShadowIndex(); }
    void BakedShadowIndexUpdated() override { Real()->m_nBakedShadowIndex.NetworkStateChanged(); }
    int32_t& LightPathUniqueId() override { return Real()->m_nLightPathUniqueId(); }
    void LightPathUniqueIdUpdated() override { Real()->m_nLightPathUniqueId.NetworkStateChanged(); }
    int32_t& LightMapUniqueId() override { return Real()->m_nLightMapUniqueId(); }
    void LightMapUniqueIdUpdated() override { Real()->m_nLightMapUniqueId.NetworkStateChanged(); }
    int32_t& LuminaireShape() override { return Real()->m_nLuminaireShape(); }
    void LuminaireShapeUpdated() override { Real()->m_nLuminaireShape.NetworkStateChanged(); }
    float& LuminaireSize() override { return Real()->m_flLuminaireSize(); }
    void LuminaireSizeUpdated() override { Real()->m_flLuminaireSize.NetworkStateChanged(); }
    float& LuminaireAnisotropy() override { return Real()->m_flLuminaireAnisotropy(); }
    void LuminaireAnisotropyUpdated() override { Real()->m_flLuminaireAnisotropy.NetworkStateChanged(); }
    CUtlString& LightStyleString() override { return Real()->m_LightStyleString(); }
    void LightStyleStringUpdated() override { Real()->m_LightStyleString.NetworkStateChanged(); }
    float& LightStyleStartTime() override { return Real()->m_flLightStyleStartTime(); }
    void LightStyleStartTimeUpdated() override { Real()->m_flLightStyleStartTime.NetworkStateChanged(); }
    CUtlVector<CUtlString>& QueuedLightStyleStrings() override { return Real()->m_QueuedLightStyleStrings(); }
    void QueuedLightStyleStringsUpdated() override { Real()->m_QueuedLightStyleStrings.NetworkStateChanged(); }
    CUtlVector<CUtlString>& LightStyleEvents() override { return Real()->m_LightStyleEvents(); }
    void LightStyleEventsUpdated() override { Real()->m_LightStyleEvents.NetworkStateChanged(); }
    CUtlVector<CHandle<CBaseModelEntity>>& LightStyleTargets() override { return Real()->m_LightStyleTargets(); }
    void LightStyleTargetsUpdated() override { Real()->m_LightStyleTargets.NetworkStateChanged(); }
    CEntityIOOutput* StyleEvent() override { return Real()->m_StyleEvent(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& LightCookie() override { return Real()->m_hLightCookie(); }
    void LightCookieUpdated() override { Real()->m_hLightCookie.NetworkStateChanged(); }
    float& Shape() override { return Real()->m_flShape(); }
    void ShapeUpdated() override { Real()->m_flShape.NetworkStateChanged(); }
    float& SoftX() override { return Real()->m_flSoftX(); }
    void SoftXUpdated() override { Real()->m_flSoftX.NetworkStateChanged(); }
    float& SoftY() override { return Real()->m_flSoftY(); }
    void SoftYUpdated() override { Real()->m_flSoftY.NetworkStateChanged(); }
    float& Skirt() override { return Real()->m_flSkirt(); }
    void SkirtUpdated() override { Real()->m_flSkirt.NetworkStateChanged(); }
    float& SkirtNear() override { return Real()->m_flSkirtNear(); }
    void SkirtNearUpdated() override { Real()->m_flSkirtNear.NetworkStateChanged(); }
    Vector& SizeParams() override { return Real()->m_vSizeParams(); }
    void SizeParamsUpdated() override { Real()->m_vSizeParams.NetworkStateChanged(); }
    float& Range() override { return Real()->m_flRange(); }
    void RangeUpdated() override { Real()->m_flRange.NetworkStateChanged(); }
    Vector& Shear() override { return Real()->m_vShear(); }
    void ShearUpdated() override { Real()->m_vShear.NetworkStateChanged(); }
    int32_t& BakeSpecularToCubemaps() override { return Real()->m_nBakeSpecularToCubemaps(); }
    void BakeSpecularToCubemapsUpdated() override { Real()->m_nBakeSpecularToCubemaps.NetworkStateChanged(); }
    Vector& BakeSpecularToCubemapsSize() override { return Real()->m_vBakeSpecularToCubemapsSize(); }
    void BakeSpecularToCubemapsSizeUpdated() override { Real()->m_vBakeSpecularToCubemapsSize.NetworkStateChanged(); }
    float& BakeSpecularToCubemapsScale() override { return Real()->m_flBakeSpecularToCubemapsScale(); }
    void BakeSpecularToCubemapsScaleUpdated() override { Real()->m_flBakeSpecularToCubemapsScale.NetworkStateChanged(); }
    int32_t& CastShadows() override { return Real()->m_nCastShadows(); }
    void CastShadowsUpdated() override { Real()->m_nCastShadows.NetworkStateChanged(); }
    int32_t& ShadowMapSize() override { return Real()->m_nShadowMapSize(); }
    void ShadowMapSizeUpdated() override { Real()->m_nShadowMapSize.NetworkStateChanged(); }
    int32_t& ShadowPriority() override { return Real()->m_nShadowPriority(); }
    void ShadowPriorityUpdated() override { Real()->m_nShadowPriority.NetworkStateChanged(); }
    bool& ContactShadow() override { return Real()->m_bContactShadow(); }
    void ContactShadowUpdated() override { Real()->m_bContactShadow.NetworkStateChanged(); }
    bool& ForceShadowsEnabled() override { return Real()->m_bForceShadowsEnabled(); }
    void ForceShadowsEnabledUpdated() override { Real()->m_bForceShadowsEnabled.NetworkStateChanged(); }
    int32_t& BounceLight() override { return Real()->m_nBounceLight(); }
    void BounceLightUpdated() override { Real()->m_nBounceLight.NetworkStateChanged(); }
    float& BounceScale() override { return Real()->m_flBounceScale(); }
    void BounceScaleUpdated() override { Real()->m_flBounceScale.NetworkStateChanged(); }
    float& MinRoughness() override { return Real()->m_flMinRoughness(); }
    void MinRoughnessUpdated() override { Real()->m_flMinRoughness.NetworkStateChanged(); }
    Vector& AlternateColor() override { return Real()->m_vAlternateColor(); }
    void AlternateColorUpdated() override { Real()->m_vAlternateColor.NetworkStateChanged(); }
    float& AlternateColorBrightness() override { return Real()->m_fAlternateColorBrightness(); }
    void AlternateColorBrightnessUpdated() override { Real()->m_fAlternateColorBrightness.NetworkStateChanged(); }
    int32_t& Fog() override { return Real()->m_nFog(); }
    void FogUpdated() override { Real()->m_nFog.NetworkStateChanged(); }
    float& FogStrength() override { return Real()->m_flFogStrength(); }
    void FogStrengthUpdated() override { Real()->m_flFogStrength.NetworkStateChanged(); }
    int32_t& FogShadows() override { return Real()->m_nFogShadows(); }
    void FogShadowsUpdated() override { Real()->m_nFogShadows.NetworkStateChanged(); }
    float& FogScale() override { return Real()->m_flFogScale(); }
    void FogScaleUpdated() override { Real()->m_flFogScale.NetworkStateChanged(); }
    float& FadeSizeStart() override { return Real()->m_flFadeSizeStart(); }
    void FadeSizeStartUpdated() override { Real()->m_flFadeSizeStart.NetworkStateChanged(); }
    float& FadeSizeEnd() override { return Real()->m_flFadeSizeEnd(); }
    void FadeSizeEndUpdated() override { Real()->m_flFadeSizeEnd.NetworkStateChanged(); }
    float& ShadowFadeSizeStart() override { return Real()->m_flShadowFadeSizeStart(); }
    void ShadowFadeSizeStartUpdated() override { Real()->m_flShadowFadeSizeStart.NetworkStateChanged(); }
    float& ShadowFadeSizeEnd() override { return Real()->m_flShadowFadeSizeEnd(); }
    void ShadowFadeSizeEndUpdated() override { Real()->m_flShadowFadeSizeEnd.NetworkStateChanged(); }
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
    int32_t& PrecomputedSubFrusta() override { return Real()->m_nPrecomputedSubFrusta(); }
    void PrecomputedSubFrustaUpdated() override { Real()->m_nPrecomputedSubFrusta.NetworkStateChanged(); }
    Vector& PrecomputedOBBOrigin0() override { return Real()->m_vPrecomputedOBBOrigin0(); }
    void PrecomputedOBBOrigin0Updated() override { Real()->m_vPrecomputedOBBOrigin0.NetworkStateChanged(); }
    QAngle& PrecomputedOBBAngles0() override { return Real()->m_vPrecomputedOBBAngles0(); }
    void PrecomputedOBBAngles0Updated() override { Real()->m_vPrecomputedOBBAngles0.NetworkStateChanged(); }
    Vector& PrecomputedOBBExtent0() override { return Real()->m_vPrecomputedOBBExtent0(); }
    void PrecomputedOBBExtent0Updated() override { Real()->m_vPrecomputedOBBExtent0.NetworkStateChanged(); }
    Vector& PrecomputedOBBOrigin1() override { return Real()->m_vPrecomputedOBBOrigin1(); }
    void PrecomputedOBBOrigin1Updated() override { Real()->m_vPrecomputedOBBOrigin1.NetworkStateChanged(); }
    QAngle& PrecomputedOBBAngles1() override { return Real()->m_vPrecomputedOBBAngles1(); }
    void PrecomputedOBBAngles1Updated() override { Real()->m_vPrecomputedOBBAngles1.NetworkStateChanged(); }
    Vector& PrecomputedOBBExtent1() override { return Real()->m_vPrecomputedOBBExtent1(); }
    void PrecomputedOBBExtent1Updated() override { Real()->m_vPrecomputedOBBExtent1.NetworkStateChanged(); }
    Vector& PrecomputedOBBOrigin2() override { return Real()->m_vPrecomputedOBBOrigin2(); }
    void PrecomputedOBBOrigin2Updated() override { Real()->m_vPrecomputedOBBOrigin2.NetworkStateChanged(); }
    QAngle& PrecomputedOBBAngles2() override { return Real()->m_vPrecomputedOBBAngles2(); }
    void PrecomputedOBBAngles2Updated() override { Real()->m_vPrecomputedOBBAngles2.NetworkStateChanged(); }
    Vector& PrecomputedOBBExtent2() override { return Real()->m_vPrecomputedOBBExtent2(); }
    void PrecomputedOBBExtent2Updated() override { Real()->m_vPrecomputedOBBExtent2.NetworkStateChanged(); }
    Vector& PrecomputedOBBOrigin3() override { return Real()->m_vPrecomputedOBBOrigin3(); }
    void PrecomputedOBBOrigin3Updated() override { Real()->m_vPrecomputedOBBOrigin3.NetworkStateChanged(); }
    QAngle& PrecomputedOBBAngles3() override { return Real()->m_vPrecomputedOBBAngles3(); }
    void PrecomputedOBBAngles3Updated() override { Real()->m_vPrecomputedOBBAngles3.NetworkStateChanged(); }
    Vector& PrecomputedOBBExtent3() override { return Real()->m_vPrecomputedOBBExtent3(); }
    void PrecomputedOBBExtent3Updated() override { Real()->m_vPrecomputedOBBExtent3.NetworkStateChanged(); }
    Vector& PrecomputedOBBOrigin4() override { return Real()->m_vPrecomputedOBBOrigin4(); }
    void PrecomputedOBBOrigin4Updated() override { Real()->m_vPrecomputedOBBOrigin4.NetworkStateChanged(); }
    QAngle& PrecomputedOBBAngles4() override { return Real()->m_vPrecomputedOBBAngles4(); }
    void PrecomputedOBBAngles4Updated() override { Real()->m_vPrecomputedOBBAngles4.NetworkStateChanged(); }
    Vector& PrecomputedOBBExtent4() override { return Real()->m_vPrecomputedOBBExtent4(); }
    void PrecomputedOBBExtent4Updated() override { Real()->m_vPrecomputedOBBExtent4.NetworkStateChanged(); }
    Vector& PrecomputedOBBOrigin5() override { return Real()->m_vPrecomputedOBBOrigin5(); }
    void PrecomputedOBBOrigin5Updated() override { Real()->m_vPrecomputedOBBOrigin5.NetworkStateChanged(); }
    QAngle& PrecomputedOBBAngles5() override { return Real()->m_vPrecomputedOBBAngles5(); }
    void PrecomputedOBBAngles5Updated() override { Real()->m_vPrecomputedOBBAngles5.NetworkStateChanged(); }
    Vector& PrecomputedOBBExtent5() override { return Real()->m_vPrecomputedOBBExtent5(); }
    void PrecomputedOBBExtent5Updated() override { Real()->m_vPrecomputedOBBExtent5.NetworkStateChanged(); }
    bool& PvsModifyEntity() override { return Real()->m_bPvsModifyEntity(); }
    void PvsModifyEntityUpdated() override { Real()->m_bPvsModifyEntity.NetworkStateChanged(); }
    bool& TransmitAlways() override { return Real()->m_bTransmitAlways(); }
    void TransmitAlwaysUpdated() override { Real()->m_bTransmitAlways.NetworkStateChanged(); }
    CUtlVector<uint16_t>& VisClusters() override { return Real()->m_VisClusters(); }
    void VisClustersUpdated() override { Real()->m_VisClusters.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IBarnLight* CBarnLight::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IBarnLight*>(tagIt->second.ptr_for_return);
    auto* impl = new CBarnLightImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IBarnLight*>(impl));
    return impl;
}
inline IBarnLight* IBarnLight::FromRaw(CEntityInstance* p) { return p ? static_cast<CBarnLight*>(p)->ToInterface() : nullptr; }
inline IBarnLight* IBarnLight::FromOriginal(CBarnLight* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBARNLIGHTIMPL_H
