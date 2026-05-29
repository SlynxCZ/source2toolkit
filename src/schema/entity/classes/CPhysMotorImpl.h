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

#ifndef _INCLUDE_CPHYSMOTORIMPL_H
#define _INCLUDE_CPHYSMOTORIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPhysMotor.h"
#include "schema/entity/classes/CPhysMotor.h"
#include "CLogicalEntityImpl.h"

class CPhysMotorImpl : public CLogicalEntityImpl, public IPhysMotor
{

public:
    explicit CPhysMotorImpl(CPhysMotor* p) : CLogicalEntityImpl(p) {}

private:
    CPhysMotor* Real() { return static_cast<CPhysMotor*>(m_pReal); }
    CPhysMotor* Real() const { return static_cast<CPhysMotor*>(m_pReal); }

public:
    CPhysMotor* GetOriginal() const override { return Real(); }
    CUtlSymbolLarge& NameAttach() override { return Real()->m_nameAttach(); }
    void NameAttachUpdated() override { Real()->m_nameAttach.NetworkStateChanged(); }
    CUtlSymbolLarge& NameAnchor() override { return Real()->m_nameAnchor(); }
    void NameAnchorUpdated() override { Real()->m_nameAnchor.NetworkStateChanged(); }
    CHandle<CBaseEntity>& AttachedObject() override { return Real()->m_hAttachedObject(); }
    void AttachedObjectUpdated() override { Real()->m_hAttachedObject.NetworkStateChanged(); }
    CHandle<CBaseEntity>& AnchorObject() override { return Real()->m_hAnchorObject(); }
    void AnchorObjectUpdated() override { Real()->m_hAnchorObject.NetworkStateChanged(); }
    float& SpinUp() override { return Real()->m_spinUp(); }
    void SpinUpUpdated() override { Real()->m_spinUp.NetworkStateChanged(); }
    float& SpinDown() override { return Real()->m_spinDown(); }
    void SpinDownUpdated() override { Real()->m_spinDown.NetworkStateChanged(); }
    float& MotorFriction() override { return Real()->m_flMotorFriction(); }
    void MotorFrictionUpdated() override { Real()->m_flMotorFriction.NetworkStateChanged(); }
    float& AdditionalAcceleration() override { return Real()->m_additionalAcceleration(); }
    void AdditionalAccelerationUpdated() override { Real()->m_additionalAcceleration.NetworkStateChanged(); }
    float& AngularAcceleration() override { return Real()->m_angularAcceleration(); }
    void AngularAccelerationUpdated() override { Real()->m_angularAcceleration.NetworkStateChanged(); }
    float& TorqueScale() override { return Real()->m_flTorqueScale(); }
    void TorqueScaleUpdated() override { Real()->m_flTorqueScale.NetworkStateChanged(); }
    float& TargetSpeed() override { return Real()->m_flTargetSpeed(); }
    void TargetSpeedUpdated() override { Real()->m_flTargetSpeed.NetworkStateChanged(); }
    float& SpeedWhenSpinUpOrSpinDownStarted() override { return Real()->m_flSpeedWhenSpinUpOrSpinDownStarted(); }
    void SpeedWhenSpinUpOrSpinDownStartedUpdated() override { Real()->m_flSpeedWhenSpinUpOrSpinDownStarted.NetworkStateChanged(); }
    IPhysicsBody*& FixedWorldBody() override { return Real()->m_pFixedWorldBody(); }
    void FixedWorldBodyUpdated() override { Real()->m_pFixedWorldBody.NetworkStateChanged(); }
    IPhysicsJoint*& MotorJoint() override { return Real()->m_pMotorJoint(); }
    void MotorJointUpdated() override { Real()->m_pMotorJoint.NetworkStateChanged(); }
    ::CMotorController& Motor() override { return Real()->m_motor(); }
    void MotorUpdated() override { Real()->m_motor.NetworkStateChanged(); }
};

inline IPhysMotor* CPhysMotor::ToInterface() { return new CPhysMotorImpl(this); }
inline IPhysMotor* IPhysMotor::FromOriginal(CPhysMotor* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPHYSMOTORIMPL_H
