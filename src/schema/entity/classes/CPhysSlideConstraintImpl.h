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

#ifndef _INCLUDE_CPHYSSLIDECONSTRAINTIMPL_H
#define _INCLUDE_CPHYSSLIDECONSTRAINTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPhysSlideConstraint.h"
#include "schema/entity/classes/CPhysSlideConstraint.h"
#include "CPhysConstraintImpl.h"

class CPhysSlideConstraintImpl : public CPhysConstraintImpl, public virtual IPhysSlideConstraint
{

public:
    explicit CPhysSlideConstraintImpl(CPhysSlideConstraint* p) : CPhysConstraintImpl(p) {}

private:
    CPhysSlideConstraint* Real() { return static_cast<CPhysSlideConstraint*>(m_pReal); }
    CPhysSlideConstraint* Real() const { return static_cast<CPhysSlideConstraint*>(m_pReal); }

public:
    CPhysSlideConstraint* GetOriginal() const override { return Real(); }
    Vector& AxisEnd() override { return Real()->m_axisEnd(); }
    void AxisEndUpdated() override { Real()->m_axisEnd.NetworkStateChanged(); }
    float& SlideFriction() override { return Real()->m_slideFriction(); }
    void SlideFrictionUpdated() override { Real()->m_slideFriction.NetworkStateChanged(); }
    float& SystemLoadScale() override { return Real()->m_systemLoadScale(); }
    void SystemLoadScaleUpdated() override { Real()->m_systemLoadScale.NetworkStateChanged(); }
    float& InitialOffset() override { return Real()->m_initialOffset(); }
    void InitialOffsetUpdated() override { Real()->m_initialOffset.NetworkStateChanged(); }
    bool& EnableLinearConstraint() override { return Real()->m_bEnableLinearConstraint(); }
    void EnableLinearConstraintUpdated() override { Real()->m_bEnableLinearConstraint.NetworkStateChanged(); }
    bool& EnableAngularConstraint() override { return Real()->m_bEnableAngularConstraint(); }
    void EnableAngularConstraintUpdated() override { Real()->m_bEnableAngularConstraint.NetworkStateChanged(); }
    float& MotorFrequency() override { return Real()->m_flMotorFrequency(); }
    void MotorFrequencyUpdated() override { Real()->m_flMotorFrequency.NetworkStateChanged(); }
    float& MotorDampingRatio() override { return Real()->m_flMotorDampingRatio(); }
    void MotorDampingRatioUpdated() override { Real()->m_flMotorDampingRatio.NetworkStateChanged(); }
    bool& UseEntityPivot() override { return Real()->m_bUseEntityPivot(); }
    void UseEntityPivotUpdated() override { Real()->m_bUseEntityPivot.NetworkStateChanged(); }
    ::ConstraintSoundInfo& SoundInfo() override { return Real()->m_soundInfo(); }
    void SoundInfoUpdated() override { Real()->m_soundInfo.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IPhysSlideConstraint* CPhysSlideConstraint::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPhysSlideConstraint*>(tagIt->second.ptr_for_return);
    auto* impl = new CPhysSlideConstraintImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPhysSlideConstraint*>(impl));
    return impl;
}
inline IPhysSlideConstraint* IPhysSlideConstraint::FromRaw(CEntityInstance* p) { return p ? static_cast<CPhysSlideConstraint*>(p)->ToInterface() : nullptr; }
inline IPhysSlideConstraint* IPhysSlideConstraint::FromOriginal(CPhysSlideConstraint* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPHYSSLIDECONSTRAINTIMPL_H
