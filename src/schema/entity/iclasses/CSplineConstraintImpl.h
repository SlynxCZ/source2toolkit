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

#ifndef _INCLUDE_CSPLINECONSTRAINTIMPL_H
#define _INCLUDE_CSPLINECONSTRAINTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/ISplineConstraint.h"
#include "schema/entity/classes/CSplineConstraint.h"
#include "CPhysConstraintImpl.h"

class CSplineConstraintImpl : public CPhysConstraintImpl, public ISplineConstraint
{

public:
    explicit CSplineConstraintImpl(CSplineConstraint* p) : CPhysConstraintImpl(p) {}

private:
    CSplineConstraint* Real() { return static_cast<CSplineConstraint*>(m_pReal); }

public:
    Vector& AnchorOffsetRestore() override { return Real()->m_vAnchorOffsetRestore(); }
    void AnchorOffsetRestoreUpdated() override { Real()->m_vAnchorOffsetRestore.NetworkStateChanged(); }
    CHandle<CBaseEntity>& SplineEntity() override { return Real()->m_hSplineEntity(); }
    void SplineEntityUpdated() override { Real()->m_hSplineEntity.NetworkStateChanged(); }
    IPhysicsBody*& SplineBody() override { return Real()->m_pSplineBody(); }
    void SplineBodyUpdated() override { Real()->m_pSplineBody.NetworkStateChanged(); }
    bool& EnableLateralConstraint() override { return Real()->m_bEnableLateralConstraint(); }
    void EnableLateralConstraintUpdated() override { Real()->m_bEnableLateralConstraint.NetworkStateChanged(); }
    bool& EnableVerticalConstraint() override { return Real()->m_bEnableVerticalConstraint(); }
    void EnableVerticalConstraintUpdated() override { Real()->m_bEnableVerticalConstraint.NetworkStateChanged(); }
    bool& EnableAngularConstraint() override { return Real()->m_bEnableAngularConstraint(); }
    void EnableAngularConstraintUpdated() override { Real()->m_bEnableAngularConstraint.NetworkStateChanged(); }
    bool& EnableLimit() override { return Real()->m_bEnableLimit(); }
    void EnableLimitUpdated() override { Real()->m_bEnableLimit.NetworkStateChanged(); }
    bool& FireEventsOnPath() override { return Real()->m_bFireEventsOnPath(); }
    void FireEventsOnPathUpdated() override { Real()->m_bFireEventsOnPath.NetworkStateChanged(); }
    float& LinearFrequency() override { return Real()->m_flLinearFrequency(); }
    void LinearFrequencyUpdated() override { Real()->m_flLinearFrequency.NetworkStateChanged(); }
    float& LinarDampingRatio() override { return Real()->m_flLinarDampingRatio(); }
    void LinarDampingRatioUpdated() override { Real()->m_flLinarDampingRatio.NetworkStateChanged(); }
    float& JointFriction() override { return Real()->m_flJointFriction(); }
    void JointFrictionUpdated() override { Real()->m_flJointFriction.NetworkStateChanged(); }
    float& TransitionTime() override { return Real()->m_flTransitionTime(); }
    void TransitionTimeUpdated() override { Real()->m_flTransitionTime.NetworkStateChanged(); }
    Vector& PreSolveAnchorPos() override { return Real()->m_vPreSolveAnchorPos(); }
    void PreSolveAnchorPosUpdated() override { Real()->m_vPreSolveAnchorPos.NetworkStateChanged(); }
    float& StartTransitionTime() override { return Real()->m_StartTransitionTime(); }
    void StartTransitionTimeUpdated() override { Real()->m_StartTransitionTime.NetworkStateChanged(); }
    Vector& TangentSpaceAnchorAtTransitionStart() override { return Real()->m_vTangentSpaceAnchorAtTransitionStart(); }
    void TangentSpaceAnchorAtTransitionStartUpdated() override { Real()->m_vTangentSpaceAnchorAtTransitionStart.NetworkStateChanged(); }
};

#endif // _INCLUDE_CSPLINECONSTRAINTIMPL_H
