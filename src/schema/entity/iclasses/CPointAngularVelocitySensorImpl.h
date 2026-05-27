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

#ifndef _INCLUDE_CPOINTANGULARVELOCITYSENSORIMPL_H
#define _INCLUDE_CPOINTANGULARVELOCITYSENSORIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IPointAngularVelocitySensor.h"
#include "schema/entity/classes/CPointAngularVelocitySensor.h"
#include "CPointEntityImpl.h"

class CPointAngularVelocitySensorImpl : public CPointEntityImpl, public IPointAngularVelocitySensor
{

public:
    explicit CPointAngularVelocitySensorImpl(CPointAngularVelocitySensor* p) : CPointEntityImpl(p) {}

private:
    CPointAngularVelocitySensor* Real() { return static_cast<CPointAngularVelocitySensor*>(m_pReal); }

public:
    CHandle<CBaseEntity>& TargetEntity() override { return Real()->m_hTargetEntity(); }
    void TargetEntityUpdated() override { Real()->m_hTargetEntity.NetworkStateChanged(); }
    float& Threshold() override { return Real()->m_flThreshold(); }
    void ThresholdUpdated() override { Real()->m_flThreshold.NetworkStateChanged(); }
    int32_t& LastCompareResult() override { return Real()->m_nLastCompareResult(); }
    void LastCompareResultUpdated() override { Real()->m_nLastCompareResult.NetworkStateChanged(); }
    int32_t& LastFireResult() override { return Real()->m_nLastFireResult(); }
    void LastFireResultUpdated() override { Real()->m_nLastFireResult.NetworkStateChanged(); }
    float& FireTime() override { return Real()->m_flFireTime(); }
    void FireTimeUpdated() override { Real()->m_flFireTime.NetworkStateChanged(); }
    float& FireInterval() override { return Real()->m_flFireInterval(); }
    void FireIntervalUpdated() override { Real()->m_flFireInterval.NetworkStateChanged(); }
    float& LastAngVelocity() override { return Real()->m_flLastAngVelocity(); }
    void LastAngVelocityUpdated() override { Real()->m_flLastAngVelocity.NetworkStateChanged(); }
    QAngle& LastOrientation() override { return Real()->m_lastOrientation(); }
    void LastOrientationUpdated() override { Real()->m_lastOrientation.NetworkStateChanged(); }
    Vector& Axis() override { return Real()->m_vecAxis(); }
    void AxisUpdated() override { Real()->m_vecAxis.NetworkStateChanged(); }
    bool& UseHelper() override { return Real()->m_bUseHelper(); }
    void UseHelperUpdated() override { Real()->m_bUseHelper.NetworkStateChanged(); }
    CEntityIOOutput& OnLessThan() override { return Real()->m_OnLessThan(); }
    void OnLessThanUpdated() override { Real()->m_OnLessThan.NetworkStateChanged(); }
    CEntityIOOutput& OnLessThanOrEqualTo() override { return Real()->m_OnLessThanOrEqualTo(); }
    void OnLessThanOrEqualToUpdated() override { Real()->m_OnLessThanOrEqualTo.NetworkStateChanged(); }
    CEntityIOOutput& OnGreaterThan() override { return Real()->m_OnGreaterThan(); }
    void OnGreaterThanUpdated() override { Real()->m_OnGreaterThan.NetworkStateChanged(); }
    CEntityIOOutput& OnGreaterThanOrEqualTo() override { return Real()->m_OnGreaterThanOrEqualTo(); }
    void OnGreaterThanOrEqualToUpdated() override { Real()->m_OnGreaterThanOrEqualTo.NetworkStateChanged(); }
    CEntityIOOutput& OnEqualTo() override { return Real()->m_OnEqualTo(); }
    void OnEqualToUpdated() override { Real()->m_OnEqualTo.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPOINTANGULARVELOCITYSENSORIMPL_H
