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

#ifndef _INCLUDE_CTRIGGERPHYSICSIMPL_H
#define _INCLUDE_CTRIGGERPHYSICSIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ITriggerPhysics.h"
#include "schema/entity/classes/CTriggerPhysics.h"
#include "CBaseTriggerImpl.h"

class CTriggerPhysicsImpl : public CBaseTriggerImpl, public ITriggerPhysics
{

public:
    explicit CTriggerPhysicsImpl(CTriggerPhysics* p) : CBaseTriggerImpl(p) {}

private:
    CTriggerPhysics* Real() { return static_cast<CTriggerPhysics*>(m_pReal); }

public:
    IPhysicsMotionController*& Controller() override { return Real()->m_pController(); }
    void ControllerUpdated() override { Real()->m_pController.NetworkStateChanged(); }
    float& GravityScale() override { return Real()->m_gravityScale(); }
    void GravityScaleUpdated() override { Real()->m_gravityScale.NetworkStateChanged(); }
    float& LinearLimit() override { return Real()->m_linearLimit(); }
    void LinearLimitUpdated() override { Real()->m_linearLimit.NetworkStateChanged(); }
    float& LinearDamping() override { return Real()->m_linearDamping(); }
    void LinearDampingUpdated() override { Real()->m_linearDamping.NetworkStateChanged(); }
    float& AngularLimit() override { return Real()->m_angularLimit(); }
    void AngularLimitUpdated() override { Real()->m_angularLimit.NetworkStateChanged(); }
    float& AngularDamping() override { return Real()->m_angularDamping(); }
    void AngularDampingUpdated() override { Real()->m_angularDamping.NetworkStateChanged(); }
    float& LinearForce() override { return Real()->m_linearForce(); }
    void LinearForceUpdated() override { Real()->m_linearForce.NetworkStateChanged(); }
    float& Frequency() override { return Real()->m_flFrequency(); }
    void FrequencyUpdated() override { Real()->m_flFrequency.NetworkStateChanged(); }
    float& DampingRatio() override { return Real()->m_flDampingRatio(); }
    void DampingRatioUpdated() override { Real()->m_flDampingRatio.NetworkStateChanged(); }
    Vector& LinearForcePointAt() override { return Real()->m_vecLinearForcePointAt(); }
    void LinearForcePointAtUpdated() override { Real()->m_vecLinearForcePointAt.NetworkStateChanged(); }
    bool& CollapseToForcePoint() override { return Real()->m_bCollapseToForcePoint(); }
    void CollapseToForcePointUpdated() override { Real()->m_bCollapseToForcePoint.NetworkStateChanged(); }
    Vector& LinearForcePointAtWorld() override { return Real()->m_vecLinearForcePointAtWorld(); }
    void LinearForcePointAtWorldUpdated() override { Real()->m_vecLinearForcePointAtWorld.NetworkStateChanged(); }
    Vector& LinearForceDirection() override { return Real()->m_vecLinearForceDirection(); }
    void LinearForceDirectionUpdated() override { Real()->m_vecLinearForceDirection.NetworkStateChanged(); }
    bool& ConvertToDebrisWhenPossible() override { return Real()->m_bConvertToDebrisWhenPossible(); }
    void ConvertToDebrisWhenPossibleUpdated() override { Real()->m_bConvertToDebrisWhenPossible.NetworkStateChanged(); }
};

#endif // _INCLUDE_CTRIGGERPHYSICSIMPL_H
