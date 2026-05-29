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

#ifndef _INCLUDE_CPROPDOORROTATINGIMPL_H
#define _INCLUDE_CPROPDOORROTATINGIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPropDoorRotating.h"
#include "schema/entity/classes/CPropDoorRotating.h"
#include "CBasePropDoorImpl.h"

class CPropDoorRotatingImpl : public CBasePropDoorImpl, public IPropDoorRotating
{

public:
    explicit CPropDoorRotatingImpl(CPropDoorRotating* p) : CBasePropDoorImpl(p) {}

private:
    CPropDoorRotating* Real() { return static_cast<CPropDoorRotating*>(m_pReal); }
    CPropDoorRotating* Real() const { return static_cast<CPropDoorRotating*>(m_pReal); }

public:
    CPropDoorRotating* GetOriginal() const override { return Real(); }
    Vector& Axis() override { return Real()->m_vecAxis(); }
    void AxisUpdated() override { Real()->m_vecAxis.NetworkStateChanged(); }
    float& Distance() override { return Real()->m_flDistance(); }
    void DistanceUpdated() override { Real()->m_flDistance.NetworkStateChanged(); }
    PropDoorRotatingSpawnPos_t& SpawnPosition() override { return Real()->m_eSpawnPosition(); }
    void SpawnPositionUpdated() override { Real()->m_eSpawnPosition.NetworkStateChanged(); }
    PropDoorRotatingOpenDirection_e& OpenDirection() override { return Real()->m_eOpenDirection(); }
    void OpenDirectionUpdated() override { Real()->m_eOpenDirection.NetworkStateChanged(); }
    PropDoorRotatingOpenDirection_e& CurrentOpenDirection() override { return Real()->m_eCurrentOpenDirection(); }
    void CurrentOpenDirectionUpdated() override { Real()->m_eCurrentOpenDirection.NetworkStateChanged(); }
    doorCheck_e& DefaultCheckDirection() override { return Real()->m_eDefaultCheckDirection(); }
    void DefaultCheckDirectionUpdated() override { Real()->m_eDefaultCheckDirection.NetworkStateChanged(); }
    float& AjarAngle() override { return Real()->m_flAjarAngle(); }
    void AjarAngleUpdated() override { Real()->m_flAjarAngle.NetworkStateChanged(); }
    QAngle& RotationAjarDeprecated() override { return Real()->m_angRotationAjarDeprecated(); }
    void RotationAjarDeprecatedUpdated() override { Real()->m_angRotationAjarDeprecated.NetworkStateChanged(); }
    QAngle& RotationClosed() override { return Real()->m_angRotationClosed(); }
    void RotationClosedUpdated() override { Real()->m_angRotationClosed.NetworkStateChanged(); }
    QAngle& RotationOpenForward() override { return Real()->m_angRotationOpenForward(); }
    void RotationOpenForwardUpdated() override { Real()->m_angRotationOpenForward.NetworkStateChanged(); }
    QAngle& RotationOpenBack() override { return Real()->m_angRotationOpenBack(); }
    void RotationOpenBackUpdated() override { Real()->m_angRotationOpenBack.NetworkStateChanged(); }
    QAngle& Goal() override { return Real()->m_angGoal(); }
    void GoalUpdated() override { Real()->m_angGoal.NetworkStateChanged(); }
    Vector& ForwardBoundsMin() override { return Real()->m_vecForwardBoundsMin(); }
    void ForwardBoundsMinUpdated() override { Real()->m_vecForwardBoundsMin.NetworkStateChanged(); }
    Vector& ForwardBoundsMax() override { return Real()->m_vecForwardBoundsMax(); }
    void ForwardBoundsMaxUpdated() override { Real()->m_vecForwardBoundsMax.NetworkStateChanged(); }
    Vector& BackBoundsMin() override { return Real()->m_vecBackBoundsMin(); }
    void BackBoundsMinUpdated() override { Real()->m_vecBackBoundsMin.NetworkStateChanged(); }
    Vector& BackBoundsMax() override { return Real()->m_vecBackBoundsMax(); }
    void BackBoundsMaxUpdated() override { Real()->m_vecBackBoundsMax.NetworkStateChanged(); }
    bool& AjarDoorShouldntAlwaysOpen() override { return Real()->m_bAjarDoorShouldntAlwaysOpen(); }
    void AjarDoorShouldntAlwaysOpenUpdated() override { Real()->m_bAjarDoorShouldntAlwaysOpen.NetworkStateChanged(); }
    CHandle<CEntityBlocker>& EntityBlocker() override { return Real()->m_hEntityBlocker(); }
    void EntityBlockerUpdated() override { Real()->m_hEntityBlocker.NetworkStateChanged(); }
};

inline IPropDoorRotating* CPropDoorRotating::ToInterface() { return new CPropDoorRotatingImpl(this); }
inline IPropDoorRotating* IPropDoorRotating::FromOriginal(CPropDoorRotating* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPROPDOORROTATINGIMPL_H
