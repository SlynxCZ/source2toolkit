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

#ifndef _INCLUDE_CPLAYER_MOVEMENTSERVICESIMPL_H
#define _INCLUDE_CPLAYER_MOVEMENTSERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IPlayer_MovementServices.h"
#include "schema/entity/classes/CPlayer_MovementServices.h"
#include "CPlayerPawnComponentImpl.h"

class CPlayer_MovementServicesImpl : public CPlayerPawnComponentImpl, public IPlayer_MovementServices
{

public:
    explicit CPlayer_MovementServicesImpl(CPlayer_MovementServices* p) : CPlayerPawnComponentImpl(p) {}

private:
    CPlayer_MovementServices* Real() { return static_cast<CPlayer_MovementServices*>(m_pReal); }

public:
    int32_t& Impulse() override { return Real()->m_nImpulse(); }
    void ImpulseUpdated() override { Real()->m_nImpulse.NetworkStateChanged(); }
    CInButtonState& Buttons() override { return Real()->m_nButtons(); }
    void ButtonsUpdated() override { Real()->m_nButtons.NetworkStateChanged(); }
    uint64_t& QueuedButtonDownMask() override { return Real()->m_nQueuedButtonDownMask(); }
    void QueuedButtonDownMaskUpdated() override { Real()->m_nQueuedButtonDownMask.NetworkStateChanged(); }
    uint64_t& QueuedButtonChangeMask() override { return Real()->m_nQueuedButtonChangeMask(); }
    void QueuedButtonChangeMaskUpdated() override { Real()->m_nQueuedButtonChangeMask.NetworkStateChanged(); }
    uint64_t& ButtonDoublePressed() override { return Real()->m_nButtonDoublePressed(); }
    void ButtonDoublePressedUpdated() override { Real()->m_nButtonDoublePressed.NetworkStateChanged(); }
    uint32_t* ButtonPressedCmdNumber() override { return Real()->m_pButtonPressedCmdNumber(); }
    uint32_t& LastCommandNumberProcessed() override { return Real()->m_nLastCommandNumberProcessed(); }
    void LastCommandNumberProcessedUpdated() override { Real()->m_nLastCommandNumberProcessed.NetworkStateChanged(); }
    uint64_t& ToggleButtonDownMask() override { return Real()->m_nToggleButtonDownMask(); }
    void ToggleButtonDownMaskUpdated() override { Real()->m_nToggleButtonDownMask.NetworkStateChanged(); }
    float& CmdForwardMove() override { return Real()->m_flCmdForwardMove(); }
    void CmdForwardMoveUpdated() override { Real()->m_flCmdForwardMove.NetworkStateChanged(); }
    float& CmdLeftMove() override { return Real()->m_flCmdLeftMove(); }
    void CmdLeftMoveUpdated() override { Real()->m_flCmdLeftMove.NetworkStateChanged(); }
    float& CmdUpMove() override { return Real()->m_flCmdUpMove(); }
    void CmdUpMoveUpdated() override { Real()->m_flCmdUpMove.NetworkStateChanged(); }
    float& Maxspeed() override { return Real()->m_flMaxspeed(); }
    void MaxspeedUpdated() override { Real()->m_flMaxspeed.NetworkStateChanged(); }
    float* ForceSubtickMoveWhen() override { return Real()->m_arrForceSubtickMoveWhen(); }
    float& ForwardMove() override { return Real()->m_flForwardMove(); }
    void ForwardMoveUpdated() override { Real()->m_flForwardMove.NetworkStateChanged(); }
    float& LeftMove() override { return Real()->m_flLeftMove(); }
    void LeftMoveUpdated() override { Real()->m_flLeftMove.NetworkStateChanged(); }
    float& UpMove() override { return Real()->m_flUpMove(); }
    void UpMoveUpdated() override { Real()->m_flUpMove.NetworkStateChanged(); }
    Vector& LastMovementImpulses() override { return Real()->m_vecLastMovementImpulses(); }
    void LastMovementImpulsesUpdated() override { Real()->m_vecLastMovementImpulses.NetworkStateChanged(); }
    QAngle& OldViewAngles() override { return Real()->m_vecOldViewAngles(); }
    void OldViewAnglesUpdated() override { Real()->m_vecOldViewAngles.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPLAYER_MOVEMENTSERVICESIMPL_H
