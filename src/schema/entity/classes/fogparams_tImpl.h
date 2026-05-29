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

#ifndef _INCLUDE_FOGPARAMS_TIMPL_H
#define _INCLUDE_FOGPARAMS_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/Ifogparams_t.h"
#include "schema/entity/classes/fogparams_t.h"

class fogparams_tImpl : public virtual Ifogparams_t
{

protected:
    void* m_pReal;

public:
    explicit fogparams_tImpl(void* p) : m_pReal(p) {}

private:
    fogparams_t* Real() { return static_cast<fogparams_t*>(m_pReal); }
    fogparams_t* Real() const { return static_cast<fogparams_t*>(m_pReal); }

public:
    fogparams_t* GetOriginal() const override { return Real(); }
    Vector& DirPrimary() override { return Real()->dirPrimary(); }
    void DirPrimaryUpdated() override { Real()->dirPrimary.NetworkStateChanged(); }
    Color& ColorPrimary() override { return Real()->colorPrimary(); }
    void ColorPrimaryUpdated() override { Real()->colorPrimary.NetworkStateChanged(); }
    Color& ColorSecondary() override { return Real()->colorSecondary(); }
    void ColorSecondaryUpdated() override { Real()->colorSecondary.NetworkStateChanged(); }
    Color& ColorPrimaryLerpTo() override { return Real()->colorPrimaryLerpTo(); }
    void ColorPrimaryLerpToUpdated() override { Real()->colorPrimaryLerpTo.NetworkStateChanged(); }
    Color& ColorSecondaryLerpTo() override { return Real()->colorSecondaryLerpTo(); }
    void ColorSecondaryLerpToUpdated() override { Real()->colorSecondaryLerpTo.NetworkStateChanged(); }
    float& Start() override { return Real()->start(); }
    void StartUpdated() override { Real()->start.NetworkStateChanged(); }
    float& End() override { return Real()->end(); }
    void EndUpdated() override { Real()->end.NetworkStateChanged(); }
    float& Farz() override { return Real()->farz(); }
    void FarzUpdated() override { Real()->farz.NetworkStateChanged(); }
    float& Maxdensity() override { return Real()->maxdensity(); }
    void MaxdensityUpdated() override { Real()->maxdensity.NetworkStateChanged(); }
    float& Exponent() override { return Real()->exponent(); }
    void ExponentUpdated() override { Real()->exponent.NetworkStateChanged(); }
    float& HDRColorScale() override { return Real()->HDRColorScale(); }
    void HDRColorScaleUpdated() override { Real()->HDRColorScale.NetworkStateChanged(); }
    float& SkyboxFogFactor() override { return Real()->skyboxFogFactor(); }
    void SkyboxFogFactorUpdated() override { Real()->skyboxFogFactor.NetworkStateChanged(); }
    float& SkyboxFogFactorLerpTo() override { return Real()->skyboxFogFactorLerpTo(); }
    void SkyboxFogFactorLerpToUpdated() override { Real()->skyboxFogFactorLerpTo.NetworkStateChanged(); }
    float& StartLerpTo() override { return Real()->startLerpTo(); }
    void StartLerpToUpdated() override { Real()->startLerpTo.NetworkStateChanged(); }
    float& EndLerpTo() override { return Real()->endLerpTo(); }
    void EndLerpToUpdated() override { Real()->endLerpTo.NetworkStateChanged(); }
    float& MaxdensityLerpTo() override { return Real()->maxdensityLerpTo(); }
    void MaxdensityLerpToUpdated() override { Real()->maxdensityLerpTo.NetworkStateChanged(); }
    float& Lerptime() override { return Real()->lerptime(); }
    void LerptimeUpdated() override { Real()->lerptime.NetworkStateChanged(); }
    float& Duration() override { return Real()->duration(); }
    void DurationUpdated() override { Real()->duration.NetworkStateChanged(); }
    float& Blendtobackground() override { return Real()->blendtobackground(); }
    void BlendtobackgroundUpdated() override { Real()->blendtobackground.NetworkStateChanged(); }
    float& Scattering() override { return Real()->scattering(); }
    void ScatteringUpdated() override { Real()->scattering.NetworkStateChanged(); }
    float& Locallightscale() override { return Real()->locallightscale(); }
    void LocallightscaleUpdated() override { Real()->locallightscale.NetworkStateChanged(); }
    bool& Enable() override { return Real()->enable(); }
    void EnableUpdated() override { Real()->enable.NetworkStateChanged(); }
    bool& Blend() override { return Real()->blend(); }
    void BlendUpdated() override { Real()->blend.NetworkStateChanged(); }
    bool& Padding2() override { return Real()->m_bPadding2(); }
    void Padding2Updated() override { Real()->m_bPadding2.NetworkStateChanged(); }
    bool& Padding() override { return Real()->m_bPadding(); }
    void PaddingUpdated() override { Real()->m_bPadding.NetworkStateChanged(); }
};

inline Ifogparams_t* fogparams_t::ToInterface() { return new fogparams_tImpl(this); }
inline Ifogparams_t* Ifogparams_t::FromOriginal(fogparams_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_FOGPARAMS_TIMPL_H
