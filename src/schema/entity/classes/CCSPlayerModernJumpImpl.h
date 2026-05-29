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

#ifndef _INCLUDE_CCSPLAYERMODERNJUMPIMPL_H
#define _INCLUDE_CCSPLAYERMODERNJUMPIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayerModernJump.h"
#include "schema/entity/classes/CCSPlayerModernJump.h"

class CCSPlayerModernJumpImpl : public virtual ICSPlayerModernJump
{

protected:
    void* m_pReal;

public:
    explicit CCSPlayerModernJumpImpl(void* p) : m_pReal(p) {}

private:
    CCSPlayerModernJump* Real() { return static_cast<CCSPlayerModernJump*>(m_pReal); }
    CCSPlayerModernJump* Real() const { return static_cast<CCSPlayerModernJump*>(m_pReal); }

public:
    CCSPlayerModernJump* GetOriginal() const override { return Real(); }
    int32_t& LastActualJumpPressTick() override { return Real()->m_nLastActualJumpPressTick(); }
    void LastActualJumpPressTickUpdated() override { Real()->m_nLastActualJumpPressTick.NetworkStateChanged(); }
    float& LastActualJumpPressFrac() override { return Real()->m_flLastActualJumpPressFrac(); }
    void LastActualJumpPressFracUpdated() override { Real()->m_flLastActualJumpPressFrac.NetworkStateChanged(); }
    int32_t& LastUsableJumpPressTick() override { return Real()->m_nLastUsableJumpPressTick(); }
    void LastUsableJumpPressTickUpdated() override { Real()->m_nLastUsableJumpPressTick.NetworkStateChanged(); }
    float& LastUsableJumpPressFrac() override { return Real()->m_flLastUsableJumpPressFrac(); }
    void LastUsableJumpPressFracUpdated() override { Real()->m_flLastUsableJumpPressFrac.NetworkStateChanged(); }
    int32_t& LastLandedTick() override { return Real()->m_nLastLandedTick(); }
    void LastLandedTickUpdated() override { Real()->m_nLastLandedTick.NetworkStateChanged(); }
    float& LastLandedFrac() override { return Real()->m_flLastLandedFrac(); }
    void LastLandedFracUpdated() override { Real()->m_flLastLandedFrac.NetworkStateChanged(); }
    float& LastLandedVelocityX() override { return Real()->m_flLastLandedVelocityX(); }
    void LastLandedVelocityXUpdated() override { Real()->m_flLastLandedVelocityX.NetworkStateChanged(); }
    float& LastLandedVelocityY() override { return Real()->m_flLastLandedVelocityY(); }
    void LastLandedVelocityYUpdated() override { Real()->m_flLastLandedVelocityY.NetworkStateChanged(); }
    float& LastLandedVelocityZ() override { return Real()->m_flLastLandedVelocityZ(); }
    void LastLandedVelocityZUpdated() override { Real()->m_flLastLandedVelocityZ.NetworkStateChanged(); }
};

inline ICSPlayerModernJump* CCSPlayerModernJump::ToInterface() { return new CCSPlayerModernJumpImpl(this); }
inline ICSPlayerModernJump* ICSPlayerModernJump::FromOriginal(CCSPlayerModernJump* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSPLAYERMODERNJUMPIMPL_H
