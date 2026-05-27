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

#ifndef _INCLUDE_CGENERICCONSTRAINTIMPL_H
#define _INCLUDE_CGENERICCONSTRAINTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IGenericConstraint.h"
#include "schema/entity/classes/CGenericConstraint.h"
#include "CPhysConstraintImpl.h"

class CGenericConstraintImpl : public CPhysConstraintImpl, public IGenericConstraint
{

public:
    explicit CGenericConstraintImpl(CGenericConstraint* p) : CPhysConstraintImpl(p) {}

private:
    CGenericConstraint* Real() { return static_cast<CGenericConstraint*>(m_pReal); }

public:
    bool& PlaceAnchorsAtConstraintTransform() override { return Real()->m_bPlaceAnchorsAtConstraintTransform(); }
    void PlaceAnchorsAtConstraintTransformUpdated() override { Real()->m_bPlaceAnchorsAtConstraintTransform.NetworkStateChanged(); }
    JointMotion_t& LinearMotionX() override { return Real()->m_nLinearMotionX(); }
    void LinearMotionXUpdated() override { Real()->m_nLinearMotionX.NetworkStateChanged(); }
    JointMotion_t& LinearMotionY() override { return Real()->m_nLinearMotionY(); }
    void LinearMotionYUpdated() override { Real()->m_nLinearMotionY.NetworkStateChanged(); }
    JointMotion_t& LinearMotionZ() override { return Real()->m_nLinearMotionZ(); }
    void LinearMotionZUpdated() override { Real()->m_nLinearMotionZ.NetworkStateChanged(); }
    float& LinearFrequencyX() override { return Real()->m_flLinearFrequencyX(); }
    void LinearFrequencyXUpdated() override { Real()->m_flLinearFrequencyX.NetworkStateChanged(); }
    float& LinearFrequencyY() override { return Real()->m_flLinearFrequencyY(); }
    void LinearFrequencyYUpdated() override { Real()->m_flLinearFrequencyY.NetworkStateChanged(); }
    float& LinearFrequencyZ() override { return Real()->m_flLinearFrequencyZ(); }
    void LinearFrequencyZUpdated() override { Real()->m_flLinearFrequencyZ.NetworkStateChanged(); }
    float& LinearDampingRatioX() override { return Real()->m_flLinearDampingRatioX(); }
    void LinearDampingRatioXUpdated() override { Real()->m_flLinearDampingRatioX.NetworkStateChanged(); }
    float& LinearDampingRatioY() override { return Real()->m_flLinearDampingRatioY(); }
    void LinearDampingRatioYUpdated() override { Real()->m_flLinearDampingRatioY.NetworkStateChanged(); }
    float& LinearDampingRatioZ() override { return Real()->m_flLinearDampingRatioZ(); }
    void LinearDampingRatioZUpdated() override { Real()->m_flLinearDampingRatioZ.NetworkStateChanged(); }
    float& MaxLinearImpulseX() override { return Real()->m_flMaxLinearImpulseX(); }
    void MaxLinearImpulseXUpdated() override { Real()->m_flMaxLinearImpulseX.NetworkStateChanged(); }
    float& MaxLinearImpulseY() override { return Real()->m_flMaxLinearImpulseY(); }
    void MaxLinearImpulseYUpdated() override { Real()->m_flMaxLinearImpulseY.NetworkStateChanged(); }
    float& MaxLinearImpulseZ() override { return Real()->m_flMaxLinearImpulseZ(); }
    void MaxLinearImpulseZUpdated() override { Real()->m_flMaxLinearImpulseZ.NetworkStateChanged(); }
    float& BreakAfterTimeX() override { return Real()->m_flBreakAfterTimeX(); }
    void BreakAfterTimeXUpdated() override { Real()->m_flBreakAfterTimeX.NetworkStateChanged(); }
    float& BreakAfterTimeY() override { return Real()->m_flBreakAfterTimeY(); }
    void BreakAfterTimeYUpdated() override { Real()->m_flBreakAfterTimeY.NetworkStateChanged(); }
    float& BreakAfterTimeZ() override { return Real()->m_flBreakAfterTimeZ(); }
    void BreakAfterTimeZUpdated() override { Real()->m_flBreakAfterTimeZ.NetworkStateChanged(); }
    float& BreakAfterTimeStartTimeX() override { return Real()->m_flBreakAfterTimeStartTimeX(); }
    void BreakAfterTimeStartTimeXUpdated() override { Real()->m_flBreakAfterTimeStartTimeX.NetworkStateChanged(); }
    float& BreakAfterTimeStartTimeY() override { return Real()->m_flBreakAfterTimeStartTimeY(); }
    void BreakAfterTimeStartTimeYUpdated() override { Real()->m_flBreakAfterTimeStartTimeY.NetworkStateChanged(); }
    float& BreakAfterTimeStartTimeZ() override { return Real()->m_flBreakAfterTimeStartTimeZ(); }
    void BreakAfterTimeStartTimeZUpdated() override { Real()->m_flBreakAfterTimeStartTimeZ.NetworkStateChanged(); }
    float& BreakAfterTimeThresholdX() override { return Real()->m_flBreakAfterTimeThresholdX(); }
    void BreakAfterTimeThresholdXUpdated() override { Real()->m_flBreakAfterTimeThresholdX.NetworkStateChanged(); }
    float& BreakAfterTimeThresholdY() override { return Real()->m_flBreakAfterTimeThresholdY(); }
    void BreakAfterTimeThresholdYUpdated() override { Real()->m_flBreakAfterTimeThresholdY.NetworkStateChanged(); }
    float& BreakAfterTimeThresholdZ() override { return Real()->m_flBreakAfterTimeThresholdZ(); }
    void BreakAfterTimeThresholdZUpdated() override { Real()->m_flBreakAfterTimeThresholdZ.NetworkStateChanged(); }
    float& NotifyForceX() override { return Real()->m_flNotifyForceX(); }
    void NotifyForceXUpdated() override { Real()->m_flNotifyForceX.NetworkStateChanged(); }
    float& NotifyForceY() override { return Real()->m_flNotifyForceY(); }
    void NotifyForceYUpdated() override { Real()->m_flNotifyForceY.NetworkStateChanged(); }
    float& NotifyForceZ() override { return Real()->m_flNotifyForceZ(); }
    void NotifyForceZUpdated() override { Real()->m_flNotifyForceZ.NetworkStateChanged(); }
    float& NotifyForceMinTimeX() override { return Real()->m_flNotifyForceMinTimeX(); }
    void NotifyForceMinTimeXUpdated() override { Real()->m_flNotifyForceMinTimeX.NetworkStateChanged(); }
    float& NotifyForceMinTimeY() override { return Real()->m_flNotifyForceMinTimeY(); }
    void NotifyForceMinTimeYUpdated() override { Real()->m_flNotifyForceMinTimeY.NetworkStateChanged(); }
    float& NotifyForceMinTimeZ() override { return Real()->m_flNotifyForceMinTimeZ(); }
    void NotifyForceMinTimeZUpdated() override { Real()->m_flNotifyForceMinTimeZ.NetworkStateChanged(); }
    float& NotifyForceLastTimeX() override { return Real()->m_flNotifyForceLastTimeX(); }
    void NotifyForceLastTimeXUpdated() override { Real()->m_flNotifyForceLastTimeX.NetworkStateChanged(); }
    float& NotifyForceLastTimeY() override { return Real()->m_flNotifyForceLastTimeY(); }
    void NotifyForceLastTimeYUpdated() override { Real()->m_flNotifyForceLastTimeY.NetworkStateChanged(); }
    float& NotifyForceLastTimeZ() override { return Real()->m_flNotifyForceLastTimeZ(); }
    void NotifyForceLastTimeZUpdated() override { Real()->m_flNotifyForceLastTimeZ.NetworkStateChanged(); }
    bool& AxisNotifiedX() override { return Real()->m_bAxisNotifiedX(); }
    void AxisNotifiedXUpdated() override { Real()->m_bAxisNotifiedX.NetworkStateChanged(); }
    bool& AxisNotifiedY() override { return Real()->m_bAxisNotifiedY(); }
    void AxisNotifiedYUpdated() override { Real()->m_bAxisNotifiedY.NetworkStateChanged(); }
    bool& AxisNotifiedZ() override { return Real()->m_bAxisNotifiedZ(); }
    void AxisNotifiedZUpdated() override { Real()->m_bAxisNotifiedZ.NetworkStateChanged(); }
    JointMotion_t& AngularMotionX() override { return Real()->m_nAngularMotionX(); }
    void AngularMotionXUpdated() override { Real()->m_nAngularMotionX.NetworkStateChanged(); }
    JointMotion_t& AngularMotionY() override { return Real()->m_nAngularMotionY(); }
    void AngularMotionYUpdated() override { Real()->m_nAngularMotionY.NetworkStateChanged(); }
    JointMotion_t& AngularMotionZ() override { return Real()->m_nAngularMotionZ(); }
    void AngularMotionZUpdated() override { Real()->m_nAngularMotionZ.NetworkStateChanged(); }
    float& AngularFrequencyX() override { return Real()->m_flAngularFrequencyX(); }
    void AngularFrequencyXUpdated() override { Real()->m_flAngularFrequencyX.NetworkStateChanged(); }
    float& AngularFrequencyY() override { return Real()->m_flAngularFrequencyY(); }
    void AngularFrequencyYUpdated() override { Real()->m_flAngularFrequencyY.NetworkStateChanged(); }
    float& AngularFrequencyZ() override { return Real()->m_flAngularFrequencyZ(); }
    void AngularFrequencyZUpdated() override { Real()->m_flAngularFrequencyZ.NetworkStateChanged(); }
    float& AngularDampingRatioX() override { return Real()->m_flAngularDampingRatioX(); }
    void AngularDampingRatioXUpdated() override { Real()->m_flAngularDampingRatioX.NetworkStateChanged(); }
    float& AngularDampingRatioY() override { return Real()->m_flAngularDampingRatioY(); }
    void AngularDampingRatioYUpdated() override { Real()->m_flAngularDampingRatioY.NetworkStateChanged(); }
    float& AngularDampingRatioZ() override { return Real()->m_flAngularDampingRatioZ(); }
    void AngularDampingRatioZUpdated() override { Real()->m_flAngularDampingRatioZ.NetworkStateChanged(); }
    float& MaxAngularImpulseX() override { return Real()->m_flMaxAngularImpulseX(); }
    void MaxAngularImpulseXUpdated() override { Real()->m_flMaxAngularImpulseX.NetworkStateChanged(); }
    float& MaxAngularImpulseY() override { return Real()->m_flMaxAngularImpulseY(); }
    void MaxAngularImpulseYUpdated() override { Real()->m_flMaxAngularImpulseY.NetworkStateChanged(); }
    float& MaxAngularImpulseZ() override { return Real()->m_flMaxAngularImpulseZ(); }
    void MaxAngularImpulseZUpdated() override { Real()->m_flMaxAngularImpulseZ.NetworkStateChanged(); }
    CEntityIOOutput& NotifyForceReachedX() override { return Real()->m_NotifyForceReachedX(); }
    void NotifyForceReachedXUpdated() override { Real()->m_NotifyForceReachedX.NetworkStateChanged(); }
    CEntityIOOutput& NotifyForceReachedY() override { return Real()->m_NotifyForceReachedY(); }
    void NotifyForceReachedYUpdated() override { Real()->m_NotifyForceReachedY.NetworkStateChanged(); }
    CEntityIOOutput& NotifyForceReachedZ() override { return Real()->m_NotifyForceReachedZ(); }
    void NotifyForceReachedZUpdated() override { Real()->m_NotifyForceReachedZ.NetworkStateChanged(); }
};

#endif // _INCLUDE_CGENERICCONSTRAINTIMPL_H
