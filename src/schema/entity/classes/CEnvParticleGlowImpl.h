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

#ifndef _INCLUDE_CENVPARTICLEGLOWIMPL_H
#define _INCLUDE_CENVPARTICLEGLOWIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvParticleGlow.h"
#include "schema/entity/classes/CEnvParticleGlow.h"
#include "CParticleSystemImpl.h"

class CEnvParticleGlowImpl : public CParticleSystemImpl, public IEnvParticleGlow
{

public:
    explicit CEnvParticleGlowImpl(CEnvParticleGlow* p) : CParticleSystemImpl(p) {}

private:
    CEnvParticleGlow* Real() { return static_cast<CEnvParticleGlow*>(m_pReal); }
    CEnvParticleGlow* Real() const { return static_cast<CEnvParticleGlow*>(m_pReal); }

public:
    CEnvParticleGlow* GetOriginal() const override { return Real(); }
    float& AlphaScale() override { return Real()->m_flAlphaScale(); }
    void AlphaScaleUpdated() override { Real()->m_flAlphaScale.NetworkStateChanged(); }
    float& RadiusScale() override { return Real()->m_flRadiusScale(); }
    void RadiusScaleUpdated() override { Real()->m_flRadiusScale.NetworkStateChanged(); }
    float& SelfIllumScale() override { return Real()->m_flSelfIllumScale(); }
    void SelfIllumScaleUpdated() override { Real()->m_flSelfIllumScale.NetworkStateChanged(); }
    Color& ColorTint() override { return Real()->m_ColorTint(); }
    void ColorTintUpdated() override { Real()->m_ColorTint.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& TextureOverride() override { return Real()->m_hTextureOverride(); }
    void TextureOverrideUpdated() override { Real()->m_hTextureOverride.NetworkStateChanged(); }
};

inline IEnvParticleGlow* CEnvParticleGlow::ToInterface() { return new CEnvParticleGlowImpl(this); }
inline IEnvParticleGlow* IEnvParticleGlow::FromOriginal(CEnvParticleGlow* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CENVPARTICLEGLOWIMPL_H
