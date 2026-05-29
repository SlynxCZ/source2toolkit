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

#ifndef _INCLUDE_CPHYSWHEELCONSTRAINTIMPL_H
#define _INCLUDE_CPHYSWHEELCONSTRAINTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPhysWheelConstraint.h"
#include "schema/entity/classes/CPhysWheelConstraint.h"
#include "CPhysConstraintImpl.h"

class CPhysWheelConstraintImpl : public CPhysConstraintImpl, public IPhysWheelConstraint
{

public:
    explicit CPhysWheelConstraintImpl(CPhysWheelConstraint* p) : CPhysConstraintImpl(p) {}

private:
    CPhysWheelConstraint* Real() { return static_cast<CPhysWheelConstraint*>(m_pReal); }
    CPhysWheelConstraint* Real() const { return static_cast<CPhysWheelConstraint*>(m_pReal); }

public:
    CPhysWheelConstraint* GetOriginal() const override { return Real(); }
    float& SuspensionFrequency() override { return Real()->m_flSuspensionFrequency(); }
    void SuspensionFrequencyUpdated() override { Real()->m_flSuspensionFrequency.NetworkStateChanged(); }
    float& SuspensionDampingRatio() override { return Real()->m_flSuspensionDampingRatio(); }
    void SuspensionDampingRatioUpdated() override { Real()->m_flSuspensionDampingRatio.NetworkStateChanged(); }
    float& SuspensionHeightOffset() override { return Real()->m_flSuspensionHeightOffset(); }
    void SuspensionHeightOffsetUpdated() override { Real()->m_flSuspensionHeightOffset.NetworkStateChanged(); }
    bool& EnableSuspensionLimit() override { return Real()->m_bEnableSuspensionLimit(); }
    void EnableSuspensionLimitUpdated() override { Real()->m_bEnableSuspensionLimit.NetworkStateChanged(); }
    float& MinSuspensionOffset() override { return Real()->m_flMinSuspensionOffset(); }
    void MinSuspensionOffsetUpdated() override { Real()->m_flMinSuspensionOffset.NetworkStateChanged(); }
    float& MaxSuspensionOffset() override { return Real()->m_flMaxSuspensionOffset(); }
    void MaxSuspensionOffsetUpdated() override { Real()->m_flMaxSuspensionOffset.NetworkStateChanged(); }
    bool& EnableSteeringLimit() override { return Real()->m_bEnableSteeringLimit(); }
    void EnableSteeringLimitUpdated() override { Real()->m_bEnableSteeringLimit.NetworkStateChanged(); }
    float& MinSteeringAngle() override { return Real()->m_flMinSteeringAngle(); }
    void MinSteeringAngleUpdated() override { Real()->m_flMinSteeringAngle.NetworkStateChanged(); }
    float& MaxSteeringAngle() override { return Real()->m_flMaxSteeringAngle(); }
    void MaxSteeringAngleUpdated() override { Real()->m_flMaxSteeringAngle.NetworkStateChanged(); }
    float& SteeringAxisFriction() override { return Real()->m_flSteeringAxisFriction(); }
    void SteeringAxisFrictionUpdated() override { Real()->m_flSteeringAxisFriction.NetworkStateChanged(); }
    float& SpinAxisFriction() override { return Real()->m_flSpinAxisFriction(); }
    void SpinAxisFrictionUpdated() override { Real()->m_flSpinAxisFriction.NetworkStateChanged(); }
    CHandle<CBaseEntity>& SteeringMimicsEntity() override { return Real()->m_hSteeringMimicsEntity(); }
    void SteeringMimicsEntityUpdated() override { Real()->m_hSteeringMimicsEntity.NetworkStateChanged(); }
};

inline IPhysWheelConstraint* CPhysWheelConstraint::ToInterface() { return new CPhysWheelConstraintImpl(this); }
inline IPhysWheelConstraint* IPhysWheelConstraint::FromOriginal(CPhysWheelConstraint* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPHYSWHEELCONSTRAINTIMPL_H
