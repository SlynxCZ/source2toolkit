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

#ifndef _INCLUDE_CENVDECALIMPL_H
#define _INCLUDE_CENVDECALIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IEnvDecal.h"
#include "schema/entity/classes/CEnvDecal.h"
#include "CBaseModelEntityImpl.h"

class CEnvDecalImpl : public CBaseModelEntityImpl, public IEnvDecal
{

public:
    explicit CEnvDecalImpl(CEnvDecal* p) : CBaseModelEntityImpl(p) {}

private:
    CEnvDecal* Real() { return static_cast<CEnvDecal*>(m_pReal); }

public:
    CStrongHandle<InfoForResourceTypeIMaterial2>& DecalMaterial() override { return Real()->m_hDecalMaterial(); }
    void DecalMaterialUpdated() override { Real()->m_hDecalMaterial.NetworkStateChanged(); }
    float& Width() override { return Real()->m_flWidth(); }
    void WidthUpdated() override { Real()->m_flWidth.NetworkStateChanged(); }
    float& Height() override { return Real()->m_flHeight(); }
    void HeightUpdated() override { Real()->m_flHeight.NetworkStateChanged(); }
    float& Depth() override { return Real()->m_flDepth(); }
    void DepthUpdated() override { Real()->m_flDepth.NetworkStateChanged(); }
    uint32_t& RenderOrder() override { return Real()->m_nRenderOrder(); }
    void RenderOrderUpdated() override { Real()->m_nRenderOrder.NetworkStateChanged(); }
    bool& ProjectOnWorld() override { return Real()->m_bProjectOnWorld(); }
    void ProjectOnWorldUpdated() override { Real()->m_bProjectOnWorld.NetworkStateChanged(); }
    bool& ProjectOnCharacters() override { return Real()->m_bProjectOnCharacters(); }
    void ProjectOnCharactersUpdated() override { Real()->m_bProjectOnCharacters.NetworkStateChanged(); }
    bool& ProjectOnWater() override { return Real()->m_bProjectOnWater(); }
    void ProjectOnWaterUpdated() override { Real()->m_bProjectOnWater.NetworkStateChanged(); }
    float& DepthSortBias() override { return Real()->m_flDepthSortBias(); }
    void DepthSortBiasUpdated() override { Real()->m_flDepthSortBias.NetworkStateChanged(); }
};

#endif // _INCLUDE_CENVDECALIMPL_H
