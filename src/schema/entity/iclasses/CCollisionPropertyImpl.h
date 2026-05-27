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

#ifndef _INCLUDE_CCOLLISIONPROPERTYIMPL_H
#define _INCLUDE_CCOLLISIONPROPERTYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/ICollisionProperty.h"
#include "schema/entity/classes/CCollisionProperty.h"

class CCollisionPropertyImpl : public virtual ICollisionProperty
{

protected:
    void* m_pReal;

public:
    explicit CCollisionPropertyImpl(void* p) : m_pReal(p) {}

private:
    CCollisionProperty* Real() { return static_cast<CCollisionProperty*>(m_pReal); }

public:
    VPhysicsCollisionAttribute_t& CollisionAttribute() override { return Real()->m_collisionAttribute(); }
    void CollisionAttributeUpdated() override { Real()->m_collisionAttribute.NetworkStateChanged(); }
    Vector& Mins() override { return Real()->m_vecMins(); }
    void MinsUpdated() override { Real()->m_vecMins.NetworkStateChanged(); }
    Vector& Maxs() override { return Real()->m_vecMaxs(); }
    void MaxsUpdated() override { Real()->m_vecMaxs.NetworkStateChanged(); }
    uint8_t& SolidFlags() override { return Real()->m_usSolidFlags(); }
    void SolidFlagsUpdated() override { Real()->m_usSolidFlags.NetworkStateChanged(); }
    SolidType_t& SolidType() override { return Real()->m_nSolidType(); }
    void SolidTypeUpdated() override { Real()->m_nSolidType.NetworkStateChanged(); }
    uint8_t& TriggerBloat() override { return Real()->m_triggerBloat(); }
    void TriggerBloatUpdated() override { Real()->m_triggerBloat.NetworkStateChanged(); }
    SurroundingBoundsType_t& SurroundType() override { return Real()->m_nSurroundType(); }
    void SurroundTypeUpdated() override { Real()->m_nSurroundType.NetworkStateChanged(); }
    uint8_t& CollisionGroup() override { return Real()->m_CollisionGroup(); }
    void CollisionGroupUpdated() override { Real()->m_CollisionGroup.NetworkStateChanged(); }
    uint8_t& EnablePhysics() override { return Real()->m_nEnablePhysics(); }
    void EnablePhysicsUpdated() override { Real()->m_nEnablePhysics.NetworkStateChanged(); }
    float& BoundingRadius() override { return Real()->m_flBoundingRadius(); }
    void BoundingRadiusUpdated() override { Real()->m_flBoundingRadius.NetworkStateChanged(); }
    Vector& SpecifiedSurroundingMins() override { return Real()->m_vecSpecifiedSurroundingMins(); }
    void SpecifiedSurroundingMinsUpdated() override { Real()->m_vecSpecifiedSurroundingMins.NetworkStateChanged(); }
    Vector& SpecifiedSurroundingMaxs() override { return Real()->m_vecSpecifiedSurroundingMaxs(); }
    void SpecifiedSurroundingMaxsUpdated() override { Real()->m_vecSpecifiedSurroundingMaxs.NetworkStateChanged(); }
    Vector& SurroundingMaxs() override { return Real()->m_vecSurroundingMaxs(); }
    void SurroundingMaxsUpdated() override { Real()->m_vecSurroundingMaxs.NetworkStateChanged(); }
    Vector& SurroundingMins() override { return Real()->m_vecSurroundingMins(); }
    void SurroundingMinsUpdated() override { Real()->m_vecSurroundingMins.NetworkStateChanged(); }
    Vector& CapsuleCenter1() override { return Real()->m_vCapsuleCenter1(); }
    void CapsuleCenter1Updated() override { Real()->m_vCapsuleCenter1.NetworkStateChanged(); }
    Vector& CapsuleCenter2() override { return Real()->m_vCapsuleCenter2(); }
    void CapsuleCenter2Updated() override { Real()->m_vCapsuleCenter2.NetworkStateChanged(); }
    float& CapsuleRadius() override { return Real()->m_flCapsuleRadius(); }
    void CapsuleRadiusUpdated() override { Real()->m_flCapsuleRadius.NetworkStateChanged(); }
};

#endif // _INCLUDE_CCOLLISIONPROPERTYIMPL_H
