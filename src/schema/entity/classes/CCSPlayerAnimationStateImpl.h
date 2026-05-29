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

#ifndef _INCLUDE_CCSPLAYERANIMATIONSTATEIMPL_H
#define _INCLUDE_CCSPLAYERANIMATIONSTATEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayerAnimationState.h"
#include "schema/entity/classes/CCSPlayerAnimationState.h"

class CCSPlayerAnimationStateImpl : public virtual ICSPlayerAnimationState
{

protected:
    void* m_pReal;

public:
    explicit CCSPlayerAnimationStateImpl(void* p) : m_pReal(p) {}

private:
    CCSPlayerAnimationState* Real() { return static_cast<CCSPlayerAnimationState*>(m_pReal); }
    CCSPlayerAnimationState* Real() const { return static_cast<CCSPlayerAnimationState*>(m_pReal); }

public:
    CCSPlayerAnimationState* GetOriginal() const override { return Real(); }
    CCSPlayerAnimationState__MoveType_t& CurrentMoveType() override { return Real()->m_currentMoveType(); }
    void CurrentMoveTypeUpdated() override { Real()->m_currentMoveType.NetworkStateChanged(); }
    CCSPlayerAnimationState__GroundMoveState_t& GroundMoveState() override { return Real()->m_groundMoveState(); }
    void GroundMoveStateUpdated() override { Real()->m_groundMoveState.NetworkStateChanged(); }
    CCSPlayerAnimationState__Direction_t& GroundActionDirection() override { return Real()->m_groundActionDirection(); }
    void GroundActionDirectionUpdated() override { Real()->m_groundActionDirection.NetworkStateChanged(); }
    CCSPlayerAnimationState__AirAction_t& AirAction() override { return Real()->m_airAction(); }
    void AirActionUpdated() override { Real()->m_airAction.NetworkStateChanged(); }
    bool& WasOnGroundLastUpdate() override { return Real()->m_bWasOnGroundLastUpdate(); }
    void WasOnGroundLastUpdateUpdated() override { Real()->m_bWasOnGroundLastUpdate.NetworkStateChanged(); }
    bool& WasStationaryLastUpdate() override { return Real()->m_bWasStationaryLastUpdate(); }
    void WasStationaryLastUpdateUpdated() override { Real()->m_bWasStationaryLastUpdate.NetworkStateChanged(); }
    int32_t& ActionStartTick() override { return Real()->m_actionStartTick(); }
    void ActionStartTickUpdated() override { Real()->m_actionStartTick.NetworkStateChanged(); }
    int32_t& StaticAimTimerStartTick() override { return Real()->m_staticAimTimerStartTick(); }
    void StaticAimTimerStartTickUpdated() override { Real()->m_staticAimTimerStartTick.NetworkStateChanged(); }
    int32_t& PlantAndTurnStartTick() override { return Real()->m_plantAndTurnStartTick(); }
    void PlantAndTurnStartTickUpdated() override { Real()->m_plantAndTurnStartTick.NetworkStateChanged(); }
    float& TurnOnSpotAngle() override { return Real()->m_flTurnOnSpotAngle(); }
    void TurnOnSpotAngleUpdated() override { Real()->m_flTurnOnSpotAngle.NetworkStateChanged(); }
    float& PreviousAimYaw() override { return Real()->m_flPreviousAimYaw(); }
    void PreviousAimYawUpdated() override { Real()->m_flPreviousAimYaw.NetworkStateChanged(); }
    float& PreviousHorizontalSpeed() override { return Real()->m_flPreviousHorizontalSpeed(); }
    void PreviousHorizontalSpeedUpdated() override { Real()->m_flPreviousHorizontalSpeed.NetworkStateChanged(); }
    float& FootIKOffsetLeft() override { return Real()->m_flFootIKOffsetLeft(); }
    void FootIKOffsetLeftUpdated() override { Real()->m_flFootIKOffsetLeft.NetworkStateChanged(); }
    float& FootIKOffsetRight() override { return Real()->m_flFootIKOffsetRight(); }
    void FootIKOffsetRightUpdated() override { Real()->m_flFootIKOffsetRight.NetworkStateChanged(); }
    float& WeaponDropPercentageDueToMovement() override { return Real()->m_flWeaponDropPercentageDueToMovement(); }
    void WeaponDropPercentageDueToMovementUpdated() override { Real()->m_flWeaponDropPercentageDueToMovement.NetworkStateChanged(); }
    float& WeaponDropSmoothDampVelocity() override { return Real()->m_flWeaponDropSmoothDampVelocity(); }
    void WeaponDropSmoothDampVelocityUpdated() override { Real()->m_flWeaponDropSmoothDampVelocity.NetworkStateChanged(); }
};

inline ICSPlayerAnimationState* CCSPlayerAnimationState::ToInterface() { return new CCSPlayerAnimationStateImpl(this); }
inline ICSPlayerAnimationState* ICSPlayerAnimationState::FromOriginal(CCSPlayerAnimationState* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSPLAYERANIMATIONSTATEIMPL_H
