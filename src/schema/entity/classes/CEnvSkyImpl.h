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

#ifndef _INCLUDE_CENVSKYIMPL_H
#define _INCLUDE_CENVSKYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvSky.h"
#include "schema/entity/classes/CEnvSky.h"
#include "CBaseModelEntityImpl.h"

class CEnvSkyImpl : public CBaseModelEntityImpl, public IEnvSky
{

public:
    explicit CEnvSkyImpl(CEnvSky* p) : CBaseModelEntityImpl(p) {}

private:
    CEnvSky* Real() { return static_cast<CEnvSky*>(m_pReal); }
    CEnvSky* Real() const { return static_cast<CEnvSky*>(m_pReal); }

public:
    CEnvSky* GetOriginal() const override { return Real(); }
    CStrongHandle<InfoForResourceTypeIMaterial2>& SkyMaterial() override { return Real()->m_hSkyMaterial(); }
    void SkyMaterialUpdated() override { Real()->m_hSkyMaterial.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIMaterial2>& SkyMaterialLightingOnly() override { return Real()->m_hSkyMaterialLightingOnly(); }
    void SkyMaterialLightingOnlyUpdated() override { Real()->m_hSkyMaterialLightingOnly.NetworkStateChanged(); }
    bool& StartDisabled() override { return Real()->m_bStartDisabled(); }
    void StartDisabledUpdated() override { Real()->m_bStartDisabled.NetworkStateChanged(); }
    Color& TintColor() override { return Real()->m_vTintColor(); }
    void TintColorUpdated() override { Real()->m_vTintColor.NetworkStateChanged(); }
    Color& TintColorLightingOnly() override { return Real()->m_vTintColorLightingOnly(); }
    void TintColorLightingOnlyUpdated() override { Real()->m_vTintColorLightingOnly.NetworkStateChanged(); }
    float& BrightnessScale() override { return Real()->m_flBrightnessScale(); }
    void BrightnessScaleUpdated() override { Real()->m_flBrightnessScale.NetworkStateChanged(); }
    int32_t& FogType() override { return Real()->m_nFogType(); }
    void FogTypeUpdated() override { Real()->m_nFogType.NetworkStateChanged(); }
    float& FogMinStart() override { return Real()->m_flFogMinStart(); }
    void FogMinStartUpdated() override { Real()->m_flFogMinStart.NetworkStateChanged(); }
    float& FogMinEnd() override { return Real()->m_flFogMinEnd(); }
    void FogMinEndUpdated() override { Real()->m_flFogMinEnd.NetworkStateChanged(); }
    float& FogMaxStart() override { return Real()->m_flFogMaxStart(); }
    void FogMaxStartUpdated() override { Real()->m_flFogMaxStart.NetworkStateChanged(); }
    float& FogMaxEnd() override { return Real()->m_flFogMaxEnd(); }
    void FogMaxEndUpdated() override { Real()->m_flFogMaxEnd.NetworkStateChanged(); }
    bool& Enabled() override { return Real()->m_bEnabled(); }
    void EnabledUpdated() override { Real()->m_bEnabled.NetworkStateChanged(); }
};

inline IEnvSky* CEnvSky::ToInterface() { return new CEnvSkyImpl(this); }
inline IEnvSky* IEnvSky::FromOriginal(CEnvSky* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CENVSKYIMPL_H
