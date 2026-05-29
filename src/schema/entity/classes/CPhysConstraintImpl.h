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

#ifndef _INCLUDE_CPHYSCONSTRAINTIMPL_H
#define _INCLUDE_CPHYSCONSTRAINTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPhysConstraint.h"
#include "schema/entity/classes/CPhysConstraint.h"
#include "CLogicalEntityImpl.h"

class CPhysConstraintImpl : public CLogicalEntityImpl, public virtual IPhysConstraint
{

public:
    explicit CPhysConstraintImpl(CPhysConstraint* p) : CLogicalEntityImpl(p) {}

private:
    CPhysConstraint* Real() { return static_cast<CPhysConstraint*>(m_pReal); }
    CPhysConstraint* Real() const { return static_cast<CPhysConstraint*>(m_pReal); }

public:
    CPhysConstraint* GetOriginal() const override { return Real(); }
    IPhysicsJoint*& Joint() override { return Real()->m_hJoint(); }
    void JointUpdated() override { Real()->m_hJoint.NetworkStateChanged(); }
    CUtlSymbolLarge& NameAttach1() override { return Real()->m_nameAttach1(); }
    void NameAttach1Updated() override { Real()->m_nameAttach1.NetworkStateChanged(); }
    CUtlSymbolLarge& NameAttach2() override { return Real()->m_nameAttach2(); }
    void NameAttach2Updated() override { Real()->m_nameAttach2.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Attach1() override { return Real()->m_hAttach1(); }
    void Attach1Updated() override { Real()->m_hAttach1.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Attach2() override { return Real()->m_hAttach2(); }
    void Attach2Updated() override { Real()->m_hAttach2.NetworkStateChanged(); }
    CUtlSymbolLarge& NameAttachment1() override { return Real()->m_nameAttachment1(); }
    void NameAttachment1Updated() override { Real()->m_nameAttachment1.NetworkStateChanged(); }
    CUtlSymbolLarge& NameAttachment2() override { return Real()->m_nameAttachment2(); }
    void NameAttachment2Updated() override { Real()->m_nameAttachment2.NetworkStateChanged(); }
    CUtlSymbolLarge& BreakSound() override { return Real()->m_breakSound(); }
    void BreakSoundUpdated() override { Real()->m_breakSound.NetworkStateChanged(); }
    float& ForceLimit() override { return Real()->m_forceLimit(); }
    void ForceLimitUpdated() override { Real()->m_forceLimit.NetworkStateChanged(); }
    float& TorqueLimit() override { return Real()->m_torqueLimit(); }
    void TorqueLimitUpdated() override { Real()->m_torqueLimit.NetworkStateChanged(); }
    float& MinTeleportDistance() override { return Real()->m_minTeleportDistance(); }
    void MinTeleportDistanceUpdated() override { Real()->m_minTeleportDistance.NetworkStateChanged(); }
    bool& SnapObjectPositions() override { return Real()->m_bSnapObjectPositions(); }
    void SnapObjectPositionsUpdated() override { Real()->m_bSnapObjectPositions.NetworkStateChanged(); }
    bool& TreatEntity1AsInfiniteMass() override { return Real()->m_bTreatEntity1AsInfiniteMass(); }
    void TreatEntity1AsInfiniteMassUpdated() override { Real()->m_bTreatEntity1AsInfiniteMass.NetworkStateChanged(); }
    ::CEntityIOOutput& OnBreak() override { return Real()->m_OnBreak(); }
    void OnBreakUpdated() override { Real()->m_OnBreak.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IPhysConstraint* CPhysConstraint::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPhysConstraint*>(tagIt->second.ptr_for_return);
    auto* impl = new CPhysConstraintImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPhysConstraint*>(impl));
    return impl;
}
inline IPhysConstraint* IPhysConstraint::FromRaw(CEntityInstance* p) { return p ? static_cast<CPhysConstraint*>(p)->ToInterface() : nullptr; }
inline IPhysConstraint* IPhysConstraint::FromOriginal(CPhysConstraint* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPHYSCONSTRAINTIMPL_H
