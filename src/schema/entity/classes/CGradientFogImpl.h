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

#ifndef _INCLUDE_CGRADIENTFOGIMPL_H
#define _INCLUDE_CGRADIENTFOGIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IGradientFog.h"
#include "schema/entity/classes/CGradientFog.h"
#include "CBaseEntityImpl.h"

class CGradientFogImpl : public CBaseEntityImpl, public virtual IGradientFog
{

public:
    explicit CGradientFogImpl(CGradientFog* p) : CBaseEntityImpl(p) {}

private:
    CGradientFog* Real() { return static_cast<CGradientFog*>(m_pReal); }
    CGradientFog* Real() const { return static_cast<CGradientFog*>(m_pReal); }

public:
    CGradientFog* GetOriginal() const override { return Real(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& GradientFogTexture() override { return Real()->m_hGradientFogTexture(); }
    void GradientFogTextureUpdated() override { Real()->m_hGradientFogTexture.NetworkStateChanged(); }
    float& FogStartDistance() override { return Real()->m_flFogStartDistance(); }
    void FogStartDistanceUpdated() override { Real()->m_flFogStartDistance.NetworkStateChanged(); }
    float& FogEndDistance() override { return Real()->m_flFogEndDistance(); }
    void FogEndDistanceUpdated() override { Real()->m_flFogEndDistance.NetworkStateChanged(); }
    bool& HeightFogEnabled() override { return Real()->m_bHeightFogEnabled(); }
    void HeightFogEnabledUpdated() override { Real()->m_bHeightFogEnabled.NetworkStateChanged(); }
    float& FogStartHeight() override { return Real()->m_flFogStartHeight(); }
    void FogStartHeightUpdated() override { Real()->m_flFogStartHeight.NetworkStateChanged(); }
    float& FogEndHeight() override { return Real()->m_flFogEndHeight(); }
    void FogEndHeightUpdated() override { Real()->m_flFogEndHeight.NetworkStateChanged(); }
    float& FarZ() override { return Real()->m_flFarZ(); }
    void FarZUpdated() override { Real()->m_flFarZ.NetworkStateChanged(); }
    float& FogMaxOpacity() override { return Real()->m_flFogMaxOpacity(); }
    void FogMaxOpacityUpdated() override { Real()->m_flFogMaxOpacity.NetworkStateChanged(); }
    float& FogFalloffExponent() override { return Real()->m_flFogFalloffExponent(); }
    void FogFalloffExponentUpdated() override { Real()->m_flFogFalloffExponent.NetworkStateChanged(); }
    float& FogVerticalExponent() override { return Real()->m_flFogVerticalExponent(); }
    void FogVerticalExponentUpdated() override { Real()->m_flFogVerticalExponent.NetworkStateChanged(); }
    Color& FogColor() override { return Real()->m_fogColor(); }
    void FogColorUpdated() override { Real()->m_fogColor.NetworkStateChanged(); }
    float& FogStrength() override { return Real()->m_flFogStrength(); }
    void FogStrengthUpdated() override { Real()->m_flFogStrength.NetworkStateChanged(); }
    float& FadeTime() override { return Real()->m_flFadeTime(); }
    void FadeTimeUpdated() override { Real()->m_flFadeTime.NetworkStateChanged(); }
    bool& StartDisabled() override { return Real()->m_bStartDisabled(); }
    void StartDisabledUpdated() override { Real()->m_bStartDisabled.NetworkStateChanged(); }
    bool& IsEnabled() override { return Real()->m_bIsEnabled(); }
    void IsEnabledUpdated() override { Real()->m_bIsEnabled.NetworkStateChanged(); }
    bool& GradientFogNeedsTextures() override { return Real()->m_bGradientFogNeedsTextures(); }
    void GradientFogNeedsTexturesUpdated() override { Real()->m_bGradientFogNeedsTextures.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IGradientFog* CGradientFog::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IGradientFog*>(tagIt->second.ptr_for_return);
    auto* impl = new CGradientFogImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IGradientFog*>(impl));
    return impl;
}
inline IGradientFog* IGradientFog::FromRaw(CEntityInstance* p) { return p ? static_cast<CGradientFog*>(p)->ToInterface() : nullptr; }
inline IGradientFog* IGradientFog::FromOriginal(CGradientFog* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CGRADIENTFOGIMPL_H
