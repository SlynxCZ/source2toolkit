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

#ifndef _INCLUDE_CMODELSTATEIMPL_H
#define _INCLUDE_CMODELSTATEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IModelState.h"
#include "schema/entity/classes/CModelState.h"

class CModelStateImpl : public virtual IModelState
{

protected:
    void* m_pReal;

public:
    explicit CModelStateImpl(void* p) : m_pReal(p) {}

private:
    CModelState* Real() { return static_cast<CModelState*>(m_pReal); }
    CModelState* Real() const { return static_cast<CModelState*>(m_pReal); }

public:
    CModelState* GetOriginal() const override { return Real(); }
    CStrongHandle<InfoForResourceTypeCModel>& Model() override { return Real()->m_hModel(); }
    void ModelUpdated() override { Real()->m_hModel.NetworkStateChanged(); }
    CUtlSymbolLarge& ModelName() override { return Real()->m_ModelName(); }
    void ModelNameUpdated() override { Real()->m_ModelName.NetworkStateChanged(); }
    IPhysAggregateInstance*& VPhysicsAggregate() override { return Real()->m_pVPhysicsAggregate(); }
    void VPhysicsAggregateUpdated() override { Real()->m_pVPhysicsAggregate.NetworkStateChanged(); }
    float& RootBoneOffset_x() override { return Real()->m_flRootBoneOffset_x(); }
    void RootBoneOffset_xUpdated() override { Real()->m_flRootBoneOffset_x.NetworkStateChanged(); }
    float& RootBoneOffset_y() override { return Real()->m_flRootBoneOffset_y(); }
    void RootBoneOffset_yUpdated() override { Real()->m_flRootBoneOffset_y.NetworkStateChanged(); }
    float& RootBoneOffset_z() override { return Real()->m_flRootBoneOffset_z(); }
    void RootBoneOffset_zUpdated() override { Real()->m_flRootBoneOffset_z.NetworkStateChanged(); }
    uint8_t& RootBoneOffsetResetSerialNumber() override { return Real()->m_nRootBoneOffsetResetSerialNumber(); }
    void RootBoneOffsetResetSerialNumberUpdated() override { Real()->m_nRootBoneOffsetResetSerialNumber.NetworkStateChanged(); }
    bool& ClientClothCreationSuppressed() override { return Real()->m_bClientClothCreationSuppressed(); }
    void ClientClothCreationSuppressedUpdated() override { Real()->m_bClientClothCreationSuppressed.NetworkStateChanged(); }
    uint8_t& AnimStateNoInterpSerialNumber() override { return Real()->m_nAnimStateNoInterpSerialNumber(); }
    void AnimStateNoInterpSerialNumberUpdated() override { Real()->m_nAnimStateNoInterpSerialNumber.NetworkStateChanged(); }
    uint64_t& MeshGroupMask() override { return Real()->m_MeshGroupMask(); }
    void MeshGroupMaskUpdated() override { Real()->m_MeshGroupMask.NetworkStateChanged(); }
    CUtlVector<int32_t>& BodyGroupChoices() override { return Real()->m_nBodyGroupChoices(); }
    void BodyGroupChoicesUpdated() override { Real()->m_nBodyGroupChoices.NetworkStateChanged(); }
    int8_t& IdealMotionType() override { return Real()->m_nIdealMotionType(); }
    void IdealMotionTypeUpdated() override { Real()->m_nIdealMotionType.NetworkStateChanged(); }
    int8_t& ForceLOD() override { return Real()->m_nForceLOD(); }
    void ForceLODUpdated() override { Real()->m_nForceLOD.NetworkStateChanged(); }
    int8_t& ClothUpdateFlags() override { return Real()->m_nClothUpdateFlags(); }
    void ClothUpdateFlagsUpdated() override { Real()->m_nClothUpdateFlags.NetworkStateChanged(); }
};

inline IModelState* CModelState::ToInterface() { return new CModelStateImpl(this); }
inline IModelState* IModelState::FromOriginal(CModelState* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CMODELSTATEIMPL_H
