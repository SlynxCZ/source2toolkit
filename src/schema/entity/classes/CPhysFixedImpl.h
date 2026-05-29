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

#ifndef _INCLUDE_CPHYSFIXEDIMPL_H
#define _INCLUDE_CPHYSFIXEDIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPhysFixed.h"
#include "schema/entity/classes/CPhysFixed.h"
#include "CPhysConstraintImpl.h"

class CPhysFixedImpl : public CPhysConstraintImpl, public virtual IPhysFixed
{

public:
    explicit CPhysFixedImpl(CPhysFixed* p) : CPhysConstraintImpl(p) {}

private:
    CPhysFixed* Real() { return static_cast<CPhysFixed*>(m_pReal); }
    CPhysFixed* Real() const { return static_cast<CPhysFixed*>(m_pReal); }

public:
    CPhysFixed* GetOriginal() const override { return Real(); }
    float& LinearFrequency() override { return Real()->m_flLinearFrequency(); }
    void LinearFrequencyUpdated() override { Real()->m_flLinearFrequency.NetworkStateChanged(); }
    float& LinearDampingRatio() override { return Real()->m_flLinearDampingRatio(); }
    void LinearDampingRatioUpdated() override { Real()->m_flLinearDampingRatio.NetworkStateChanged(); }
    float& AngularFrequency() override { return Real()->m_flAngularFrequency(); }
    void AngularFrequencyUpdated() override { Real()->m_flAngularFrequency.NetworkStateChanged(); }
    float& AngularDampingRatio() override { return Real()->m_flAngularDampingRatio(); }
    void AngularDampingRatioUpdated() override { Real()->m_flAngularDampingRatio.NetworkStateChanged(); }
    bool& EnableLinearConstraint() override { return Real()->m_bEnableLinearConstraint(); }
    void EnableLinearConstraintUpdated() override { Real()->m_bEnableLinearConstraint.NetworkStateChanged(); }
    bool& EnableAngularConstraint() override { return Real()->m_bEnableAngularConstraint(); }
    void EnableAngularConstraintUpdated() override { Real()->m_bEnableAngularConstraint.NetworkStateChanged(); }
    CUtlSymbolLarge& BoneName1() override { return Real()->m_sBoneName1(); }
    void BoneName1Updated() override { Real()->m_sBoneName1.NetworkStateChanged(); }
    CUtlSymbolLarge& BoneName2() override { return Real()->m_sBoneName2(); }
    void BoneName2Updated() override { Real()->m_sBoneName2.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IPhysFixed* CPhysFixed::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPhysFixed*>(tagIt->second.ptr_for_return);
    auto* impl = new CPhysFixedImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPhysFixed*>(impl));
    return impl;
}
inline IPhysFixed* IPhysFixed::FromRaw(CEntityInstance* p) { return p ? static_cast<CPhysFixed*>(p)->ToInterface() : nullptr; }
inline IPhysFixed* IPhysFixed::FromOriginal(CPhysFixed* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPHYSFIXEDIMPL_H
