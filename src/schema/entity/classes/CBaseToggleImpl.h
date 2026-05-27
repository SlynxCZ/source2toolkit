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

#ifndef _INCLUDE_CBASETOGGLEIMPL_H
#define _INCLUDE_CBASETOGGLEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBaseToggle.h"
#include "schema/entity/classes/CBaseToggle.h"
#include "CBaseModelEntityImpl.h"

class CBaseToggleImpl : public CBaseModelEntityImpl, public IBaseToggle
{

public:
    explicit CBaseToggleImpl(CBaseToggle* p) : CBaseModelEntityImpl(p) {}

private:
    CBaseToggle* Real() { return static_cast<CBaseToggle*>(m_pReal); }

public:
    TOGGLE_STATE& Toggle_state() override { return Real()->m_toggle_state(); }
    void Toggle_stateUpdated() override { Real()->m_toggle_state.NetworkStateChanged(); }
    float& MoveDistance() override { return Real()->m_flMoveDistance(); }
    void MoveDistanceUpdated() override { Real()->m_flMoveDistance.NetworkStateChanged(); }
    float& Wait() override { return Real()->m_flWait(); }
    void WaitUpdated() override { Real()->m_flWait.NetworkStateChanged(); }
    float& Lip() override { return Real()->m_flLip(); }
    void LipUpdated() override { Real()->m_flLip.NetworkStateChanged(); }
    bool& AlwaysFireBlockedOutputs() override { return Real()->m_bAlwaysFireBlockedOutputs(); }
    void AlwaysFireBlockedOutputsUpdated() override { Real()->m_bAlwaysFireBlockedOutputs.NetworkStateChanged(); }
    Vector& Position1() override { return Real()->m_vecPosition1(); }
    void Position1Updated() override { Real()->m_vecPosition1.NetworkStateChanged(); }
    Vector& Position2() override { return Real()->m_vecPosition2(); }
    void Position2Updated() override { Real()->m_vecPosition2.NetworkStateChanged(); }
    QAngle& MoveAng() override { return Real()->m_vecMoveAng(); }
    void MoveAngUpdated() override { Real()->m_vecMoveAng.NetworkStateChanged(); }
    QAngle& Angle1() override { return Real()->m_vecAngle1(); }
    void Angle1Updated() override { Real()->m_vecAngle1.NetworkStateChanged(); }
    QAngle& Angle2() override { return Real()->m_vecAngle2(); }
    void Angle2Updated() override { Real()->m_vecAngle2.NetworkStateChanged(); }
    float& Height() override { return Real()->m_flHeight(); }
    void HeightUpdated() override { Real()->m_flHeight.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Activator() override { return Real()->m_hActivator(); }
    void ActivatorUpdated() override { Real()->m_hActivator.NetworkStateChanged(); }
    Vector& FinalDest() override { return Real()->m_vecFinalDest(); }
    void FinalDestUpdated() override { Real()->m_vecFinalDest.NetworkStateChanged(); }
    QAngle& FinalAngle() override { return Real()->m_vecFinalAngle(); }
    void FinalAngleUpdated() override { Real()->m_vecFinalAngle.NetworkStateChanged(); }
    int32_t& MovementType() override { return Real()->m_movementType(); }
    void MovementTypeUpdated() override { Real()->m_movementType.NetworkStateChanged(); }
    CUtlSymbolLarge& Master() override { return Real()->m_sMaster(); }
    void MasterUpdated() override { Real()->m_sMaster.NetworkStateChanged(); }
};

#endif // _INCLUDE_CBASETOGGLEIMPL_H
