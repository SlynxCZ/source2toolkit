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

#ifndef _INCLUDE_CBUOYANCYHELPERIMPL_H
#define _INCLUDE_CBUOYANCYHELPERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBuoyancyHelper.h"
#include "schema/entity/classes/CBuoyancyHelper.h"

class CBuoyancyHelperImpl : public virtual IBuoyancyHelper
{

protected:
    void* m_pReal;

public:
    explicit CBuoyancyHelperImpl(void* p) : m_pReal(p) {}

private:
    CBuoyancyHelper* Real() { return static_cast<CBuoyancyHelper*>(m_pReal); }
    CBuoyancyHelper* Real() const { return static_cast<CBuoyancyHelper*>(m_pReal); }

public:
    CBuoyancyHelper* GetOriginal() const override { return Real(); }
    IPhysicsMotionController*& Controller() override { return Real()->m_pController(); }
    void ControllerUpdated() override { Real()->m_pController.NetworkStateChanged(); }
    CUtlStringToken* FluidType() override { return Real()->m_nFluidType(); }
    float& FluidDensity() override { return Real()->m_flFluidDensity(); }
    void FluidDensityUpdated() override { Real()->m_flFluidDensity.NetworkStateChanged(); }
    float& NeutrallyBuoyantGravity() override { return Real()->m_flNeutrallyBuoyantGravity(); }
    void NeutrallyBuoyantGravityUpdated() override { Real()->m_flNeutrallyBuoyantGravity.NetworkStateChanged(); }
    float& NeutrallyBuoyantLinearDamping() override { return Real()->m_flNeutrallyBuoyantLinearDamping(); }
    void NeutrallyBuoyantLinearDampingUpdated() override { Real()->m_flNeutrallyBuoyantLinearDamping.NetworkStateChanged(); }
    float& NeutrallyBuoyantAngularDamping() override { return Real()->m_flNeutrallyBuoyantAngularDamping(); }
    void NeutrallyBuoyantAngularDampingUpdated() override { Real()->m_flNeutrallyBuoyantAngularDamping.NetworkStateChanged(); }
    bool& NeutrallyBuoyant() override { return Real()->m_bNeutrallyBuoyant(); }
    void NeutrallyBuoyantUpdated() override { Real()->m_bNeutrallyBuoyant.NetworkStateChanged(); }
    CUtlVector<float>& FractionOfWheelSubmergedForWheelFriction() override { return Real()->m_vecFractionOfWheelSubmergedForWheelFriction(); }
    void FractionOfWheelSubmergedForWheelFrictionUpdated() override { Real()->m_vecFractionOfWheelSubmergedForWheelFriction.NetworkStateChanged(); }
    CUtlVector<float>& WheelFrictionScales() override { return Real()->m_vecWheelFrictionScales(); }
    void WheelFrictionScalesUpdated() override { Real()->m_vecWheelFrictionScales.NetworkStateChanged(); }
    CUtlVector<float>& FractionOfWheelSubmergedForWheelDrag() override { return Real()->m_vecFractionOfWheelSubmergedForWheelDrag(); }
    void FractionOfWheelSubmergedForWheelDragUpdated() override { Real()->m_vecFractionOfWheelSubmergedForWheelDrag.NetworkStateChanged(); }
    CUtlVector<float>& WheelDrag() override { return Real()->m_vecWheelDrag(); }
    void WheelDragUpdated() override { Real()->m_vecWheelDrag.NetworkStateChanged(); }
};

inline IBuoyancyHelper* CBuoyancyHelper::ToInterface() { return new CBuoyancyHelperImpl(this); }
inline IBuoyancyHelper* IBuoyancyHelper::FromOriginal(CBuoyancyHelper* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBUOYANCYHELPERIMPL_H
