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

#ifndef _INCLUDE_SHARD_MODEL_DESC_TIMPL_H
#define _INCLUDE_SHARD_MODEL_DESC_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/Ishard_model_desc_t.h"
#include "schema/entity/classes/shard_model_desc_t.h"

class shard_model_desc_tImpl : public virtual Ishard_model_desc_t
{

protected:
    void* m_pReal;

public:
    explicit shard_model_desc_tImpl(void* p) : m_pReal(p) {}

private:
    shard_model_desc_t* Real() { return static_cast<shard_model_desc_t*>(m_pReal); }
    shard_model_desc_t* Real() const { return static_cast<shard_model_desc_t*>(m_pReal); }

public:
    shard_model_desc_t* GetOriginal() const override { return Real(); }
    int32_t& ModelID() override { return Real()->m_nModelID(); }
    void ModelIDUpdated() override { Real()->m_nModelID.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIMaterial2>& MaterialBase() override { return Real()->m_hMaterialBase(); }
    void MaterialBaseUpdated() override { Real()->m_hMaterialBase.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIMaterial2>& MaterialDamageOverlay() override { return Real()->m_hMaterialDamageOverlay(); }
    void MaterialDamageOverlayUpdated() override { Real()->m_hMaterialDamageOverlay.NetworkStateChanged(); }
    ShardSolid_t& Solid() override { return Real()->m_solid(); }
    void SolidUpdated() override { Real()->m_solid.NetworkStateChanged(); }
    Vector2D& PanelSize() override { return Real()->m_vecPanelSize(); }
    void PanelSizeUpdated() override { Real()->m_vecPanelSize.NetworkStateChanged(); }
    Vector2D& StressPositionA() override { return Real()->m_vecStressPositionA(); }
    void StressPositionAUpdated() override { Real()->m_vecStressPositionA.NetworkStateChanged(); }
    Vector2D& StressPositionB() override { return Real()->m_vecStressPositionB(); }
    void StressPositionBUpdated() override { Real()->m_vecStressPositionB.NetworkStateChanged(); }
    CUtlVector<Vector2D>& PanelVertices() override { return Real()->m_vecPanelVertices(); }
    void PanelVerticesUpdated() override { Real()->m_vecPanelVertices.NetworkStateChanged(); }
    CUtlVector<Vector4D>& InitialPanelVertices() override { return Real()->m_vInitialPanelVertices(); }
    void InitialPanelVerticesUpdated() override { Real()->m_vInitialPanelVertices.NetworkStateChanged(); }
    float& GlassHalfThickness() override { return Real()->m_flGlassHalfThickness(); }
    void GlassHalfThicknessUpdated() override { Real()->m_flGlassHalfThickness.NetworkStateChanged(); }
    bool& HasParent() override { return Real()->m_bHasParent(); }
    void HasParentUpdated() override { Real()->m_bHasParent.NetworkStateChanged(); }
    bool& ParentFrozen() override { return Real()->m_bParentFrozen(); }
    void ParentFrozenUpdated() override { Real()->m_bParentFrozen.NetworkStateChanged(); }
    CUtlStringToken* SurfacePropStringToken() override { return Real()->m_SurfacePropStringToken(); }
};

inline Ishard_model_desc_t* shard_model_desc_t::ToInterface() { return new shard_model_desc_tImpl(this); }
inline Ishard_model_desc_t* Ishard_model_desc_t::FromOriginal(shard_model_desc_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_SHARD_MODEL_DESC_TIMPL_H
