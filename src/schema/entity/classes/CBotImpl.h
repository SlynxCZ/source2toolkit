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

#ifndef _INCLUDE_CBOTIMPL_H
#define _INCLUDE_CBOTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBot.h"
#include "schema/entity/classes/CBot.h"

class CBotImpl : public virtual IBot
{

protected:
    void* m_pReal;

public:
    explicit CBotImpl(void* p) : m_pReal(p) {}

private:
    CBot* Real() { return static_cast<CBot*>(m_pReal); }
    CBot* Real() const { return static_cast<CBot*>(m_pReal); }

public:
    CBot* GetOriginal() const override { return Real(); }
    CCSPlayerController*& Controller() override { return Real()->m_pController(); }
    void ControllerUpdated() override { Real()->m_pController.NetworkStateChanged(); }
    CCSPlayerPawn*& Player() override { return Real()->m_pPlayer(); }
    void PlayerUpdated() override { Real()->m_pPlayer.NetworkStateChanged(); }
    bool& HasSpawned() override { return Real()->m_bHasSpawned(); }
    void HasSpawnedUpdated() override { Real()->m_bHasSpawned.NetworkStateChanged(); }
    uint32_t& Id() override { return Real()->m_id(); }
    void IdUpdated() override { Real()->m_id.NetworkStateChanged(); }
    bool& IsRunning() override { return Real()->m_isRunning(); }
    void IsRunningUpdated() override { Real()->m_isRunning.NetworkStateChanged(); }
    bool& IsCrouching() override { return Real()->m_isCrouching(); }
    void IsCrouchingUpdated() override { Real()->m_isCrouching.NetworkStateChanged(); }
    float& ForwardSpeed() override { return Real()->m_forwardSpeed(); }
    void ForwardSpeedUpdated() override { Real()->m_forwardSpeed.NetworkStateChanged(); }
    float& LeftSpeed() override { return Real()->m_leftSpeed(); }
    void LeftSpeedUpdated() override { Real()->m_leftSpeed.NetworkStateChanged(); }
    float& VerticalSpeed() override { return Real()->m_verticalSpeed(); }
    void VerticalSpeedUpdated() override { Real()->m_verticalSpeed.NetworkStateChanged(); }
    uint64_t& ButtonFlags() override { return Real()->m_buttonFlags(); }
    void ButtonFlagsUpdated() override { Real()->m_buttonFlags.NetworkStateChanged(); }
    float& JumpTimestamp() override { return Real()->m_jumpTimestamp(); }
    void JumpTimestampUpdated() override { Real()->m_jumpTimestamp.NetworkStateChanged(); }
    Vector& ViewForward() override { return Real()->m_viewForward(); }
    void ViewForwardUpdated() override { Real()->m_viewForward.NetworkStateChanged(); }
    int32_t& PostureStackIndex() override { return Real()->m_postureStackIndex(); }
    void PostureStackIndexUpdated() override { Real()->m_postureStackIndex.NetworkStateChanged(); }
};

inline IBot* CBot::ToInterface() { return new CBotImpl(this); }
inline IBot* IBot::FromOriginal(CBot* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBOTIMPL_H
