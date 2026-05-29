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

#ifndef _INCLUDE_VPHYSICSCOLLISIONATTRIBUTE_TIMPL_H
#define _INCLUDE_VPHYSICSCOLLISIONATTRIBUTE_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IVPhysicsCollisionAttribute_t.h"
#include "schema/entity/classes/VPhysicsCollisionAttribute_t.h"

class VPhysicsCollisionAttribute_tImpl : public virtual IVPhysicsCollisionAttribute_t
{

protected:
    void* m_pReal;

public:
    explicit VPhysicsCollisionAttribute_tImpl(void* p) : m_pReal(p) {}

private:
    VPhysicsCollisionAttribute_t* Real() { return static_cast<VPhysicsCollisionAttribute_t*>(m_pReal); }
    VPhysicsCollisionAttribute_t* Real() const { return static_cast<VPhysicsCollisionAttribute_t*>(m_pReal); }

public:
    VPhysicsCollisionAttribute_t* GetOriginal() const override { return Real(); }
    uint64_t& InteractsAs() override { return Real()->m_nInteractsAs(); }
    void InteractsAsUpdated() override { Real()->m_nInteractsAs.NetworkStateChanged(); }
    uint64_t& InteractsWith() override { return Real()->m_nInteractsWith(); }
    void InteractsWithUpdated() override { Real()->m_nInteractsWith.NetworkStateChanged(); }
    uint64_t& InteractsExclude() override { return Real()->m_nInteractsExclude(); }
    void InteractsExcludeUpdated() override { Real()->m_nInteractsExclude.NetworkStateChanged(); }
    uint32_t& EntityId() override { return Real()->m_nEntityId(); }
    void EntityIdUpdated() override { Real()->m_nEntityId.NetworkStateChanged(); }
    uint32_t& OwnerId() override { return Real()->m_nOwnerId(); }
    void OwnerIdUpdated() override { Real()->m_nOwnerId.NetworkStateChanged(); }
    uint16_t& HierarchyId() override { return Real()->m_nHierarchyId(); }
    void HierarchyIdUpdated() override { Real()->m_nHierarchyId.NetworkStateChanged(); }
    uint16_t& DetailLayerMask() override { return Real()->m_nDetailLayerMask(); }
    void DetailLayerMaskUpdated() override { Real()->m_nDetailLayerMask.NetworkStateChanged(); }
    uint8_t& DetailLayerMaskType() override { return Real()->m_nDetailLayerMaskType(); }
    void DetailLayerMaskTypeUpdated() override { Real()->m_nDetailLayerMaskType.NetworkStateChanged(); }
    uint8_t& TargetDetailLayer() override { return Real()->m_nTargetDetailLayer(); }
    void TargetDetailLayerUpdated() override { Real()->m_nTargetDetailLayer.NetworkStateChanged(); }
    uint8_t& CollisionGroup() override { return Real()->m_nCollisionGroup(); }
    void CollisionGroupUpdated() override { Real()->m_nCollisionGroup.NetworkStateChanged(); }
    uint8_t& CollisionFunctionMask() override { return Real()->m_nCollisionFunctionMask(); }
    void CollisionFunctionMaskUpdated() override { Real()->m_nCollisionFunctionMask.NetworkStateChanged(); }
};

inline IVPhysicsCollisionAttribute_t* VPhysicsCollisionAttribute_t::ToInterface() { return new VPhysicsCollisionAttribute_tImpl(this); }
inline IVPhysicsCollisionAttribute_t* IVPhysicsCollisionAttribute_t::FromOriginal(VPhysicsCollisionAttribute_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_VPHYSICSCOLLISIONATTRIBUTE_TIMPL_H
