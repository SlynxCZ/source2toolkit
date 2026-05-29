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

#ifndef _INCLUDE_CPOINTCAMERAIMPL_H
#define _INCLUDE_CPOINTCAMERAIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPointCamera.h"
#include "schema/entity/classes/CPointCamera.h"
#include "CBaseEntityImpl.h"

class CPointCameraImpl : public CBaseEntityImpl, public virtual IPointCamera
{

public:
    explicit CPointCameraImpl(CPointCamera* p) : CBaseEntityImpl(p) {}

private:
    CPointCamera* Real() { return static_cast<CPointCamera*>(m_pReal); }
    CPointCamera* Real() const { return static_cast<CPointCamera*>(m_pReal); }

public:
    CPointCamera* GetOriginal() const override { return Real(); }
    float& FOV() override { return Real()->m_FOV(); }
    void FOVUpdated() override { Real()->m_FOV.NetworkStateChanged(); }
    float& Resolution() override { return Real()->m_Resolution(); }
    void ResolutionUpdated() override { Real()->m_Resolution.NetworkStateChanged(); }
    bool& FogEnable() override { return Real()->m_bFogEnable(); }
    void FogEnableUpdated() override { Real()->m_bFogEnable.NetworkStateChanged(); }
    Color& FogColor() override { return Real()->m_FogColor(); }
    void FogColorUpdated() override { Real()->m_FogColor.NetworkStateChanged(); }
    float& FogStart() override { return Real()->m_flFogStart(); }
    void FogStartUpdated() override { Real()->m_flFogStart.NetworkStateChanged(); }
    float& FogEnd() override { return Real()->m_flFogEnd(); }
    void FogEndUpdated() override { Real()->m_flFogEnd.NetworkStateChanged(); }
    float& FogMaxDensity() override { return Real()->m_flFogMaxDensity(); }
    void FogMaxDensityUpdated() override { Real()->m_flFogMaxDensity.NetworkStateChanged(); }
    bool& Active() override { return Real()->m_bActive(); }
    void ActiveUpdated() override { Real()->m_bActive.NetworkStateChanged(); }
    bool& UseScreenAspectRatio() override { return Real()->m_bUseScreenAspectRatio(); }
    void UseScreenAspectRatioUpdated() override { Real()->m_bUseScreenAspectRatio.NetworkStateChanged(); }
    float& AspectRatio() override { return Real()->m_flAspectRatio(); }
    void AspectRatioUpdated() override { Real()->m_flAspectRatio.NetworkStateChanged(); }
    bool& NoSky() override { return Real()->m_bNoSky(); }
    void NoSkyUpdated() override { Real()->m_bNoSky.NetworkStateChanged(); }
    float& Brightness() override { return Real()->m_fBrightness(); }
    void BrightnessUpdated() override { Real()->m_fBrightness.NetworkStateChanged(); }
    float& ZFar() override { return Real()->m_flZFar(); }
    void ZFarUpdated() override { Real()->m_flZFar.NetworkStateChanged(); }
    float& ZNear() override { return Real()->m_flZNear(); }
    void ZNearUpdated() override { Real()->m_flZNear.NetworkStateChanged(); }
    bool& CanHLTVUse() override { return Real()->m_bCanHLTVUse(); }
    void CanHLTVUseUpdated() override { Real()->m_bCanHLTVUse.NetworkStateChanged(); }
    bool& AlignWithParent() override { return Real()->m_bAlignWithParent(); }
    void AlignWithParentUpdated() override { Real()->m_bAlignWithParent.NetworkStateChanged(); }
    bool& DofEnabled() override { return Real()->m_bDofEnabled(); }
    void DofEnabledUpdated() override { Real()->m_bDofEnabled.NetworkStateChanged(); }
    float& DofNearBlurry() override { return Real()->m_flDofNearBlurry(); }
    void DofNearBlurryUpdated() override { Real()->m_flDofNearBlurry.NetworkStateChanged(); }
    float& DofNearCrisp() override { return Real()->m_flDofNearCrisp(); }
    void DofNearCrispUpdated() override { Real()->m_flDofNearCrisp.NetworkStateChanged(); }
    float& DofFarCrisp() override { return Real()->m_flDofFarCrisp(); }
    void DofFarCrispUpdated() override { Real()->m_flDofFarCrisp.NetworkStateChanged(); }
    float& DofFarBlurry() override { return Real()->m_flDofFarBlurry(); }
    void DofFarBlurryUpdated() override { Real()->m_flDofFarBlurry.NetworkStateChanged(); }
    float& DofTiltToGround() override { return Real()->m_flDofTiltToGround(); }
    void DofTiltToGroundUpdated() override { Real()->m_flDofTiltToGround.NetworkStateChanged(); }
    float& TargetFOV() override { return Real()->m_TargetFOV(); }
    void TargetFOVUpdated() override { Real()->m_TargetFOV.NetworkStateChanged(); }
    float& DegreesPerSecond() override { return Real()->m_DegreesPerSecond(); }
    void DegreesPerSecondUpdated() override { Real()->m_DegreesPerSecond.NetworkStateChanged(); }
    bool& IsOn() override { return Real()->m_bIsOn(); }
    void IsOnUpdated() override { Real()->m_bIsOn.NetworkStateChanged(); }
    CPointCamera*& Next() override { return Real()->m_pNext(); }
    void NextUpdated() override { Real()->m_pNext.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IPointCamera* CPointCamera::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPointCamera*>(tagIt->second.ptr_for_return);
    auto* impl = new CPointCameraImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPointCamera*>(impl));
    return impl;
}
inline IPointCamera* IPointCamera::FromRaw(CEntityInstance* p) { return p ? static_cast<CPointCamera*>(p)->ToInterface() : nullptr; }
inline IPointCamera* IPointCamera::FromOriginal(CPointCamera* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPOINTCAMERAIMPL_H
