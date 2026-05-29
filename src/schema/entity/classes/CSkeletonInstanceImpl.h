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

#ifndef _INCLUDE_CSKELETONINSTANCEIMPL_H
#define _INCLUDE_CSKELETONINSTANCEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISkeletonInstance.h"
#include "schema/entity/classes/CSkeletonInstance.h"
#include "CGameSceneNodeImpl.h"

class CSkeletonInstanceImpl : public CGameSceneNodeImpl, public ISkeletonInstance
{

public:
    explicit CSkeletonInstanceImpl(CSkeletonInstance* p) : CGameSceneNodeImpl(p) {}

private:
    CSkeletonInstance* Real() { return static_cast<CSkeletonInstance*>(m_pReal); }
    CSkeletonInstance* Real() const { return static_cast<CSkeletonInstance*>(m_pReal); }

public:
    CSkeletonInstance* GetOriginal() const override { return Real(); }
    CModelState& ModelState() override { return Real()->m_modelState(); }
    void ModelStateUpdated() override { Real()->m_modelState.NetworkStateChanged(); }
    bool& UseParentRenderBounds() override { return Real()->m_bUseParentRenderBounds(); }
    void UseParentRenderBoundsUpdated() override { Real()->m_bUseParentRenderBounds.NetworkStateChanged(); }
    bool& DisableSolidCollisionsForHierarchy() override { return Real()->m_bDisableSolidCollisionsForHierarchy(); }
    void DisableSolidCollisionsForHierarchyUpdated() override { Real()->m_bDisableSolidCollisionsForHierarchy.NetworkStateChanged(); }
    CUtlStringToken* MaterialGroup() override { return Real()->m_materialGroup(); }
    uint8_t& HitboxSet() override { return Real()->m_nHitboxSet(); }
    void HitboxSetUpdated() override { Real()->m_nHitboxSet.NetworkStateChanged(); }
    bool& ForceServerConstraintsEnabled() override { return Real()->m_bForceServerConstraintsEnabled(); }
    void ForceServerConstraintsEnabledUpdated() override { Real()->m_bForceServerConstraintsEnabled.NetworkStateChanged(); }
};

inline ISkeletonInstance* CSkeletonInstance::ToInterface() { return new CSkeletonInstanceImpl(this); }
inline ISkeletonInstance* ISkeletonInstance::FromOriginal(CSkeletonInstance* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CSKELETONINSTANCEIMPL_H
