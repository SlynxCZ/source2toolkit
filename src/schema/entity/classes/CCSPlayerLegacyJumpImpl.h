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

#ifndef _INCLUDE_CCSPLAYERLEGACYJUMPIMPL_H
#define _INCLUDE_CCSPLAYERLEGACYJUMPIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayerLegacyJump.h"
#include "schema/entity/classes/CCSPlayerLegacyJump.h"

class CCSPlayerLegacyJumpImpl : public virtual ICSPlayerLegacyJump
{

protected:
    void* m_pReal;

public:
    explicit CCSPlayerLegacyJumpImpl(void* p) : m_pReal(p) {}

private:
    CCSPlayerLegacyJump* Real() { return static_cast<CCSPlayerLegacyJump*>(m_pReal); }
    CCSPlayerLegacyJump* Real() const { return static_cast<CCSPlayerLegacyJump*>(m_pReal); }

public:
    CCSPlayerLegacyJump* GetOriginal() const override { return Real(); }
    bool& OldJumpPressed() override { return Real()->m_bOldJumpPressed(); }
    void OldJumpPressedUpdated() override { Real()->m_bOldJumpPressed.NetworkStateChanged(); }
    float& JumpPressedTime() override { return Real()->m_flJumpPressedTime(); }
    void JumpPressedTimeUpdated() override { Real()->m_flJumpPressedTime.NetworkStateChanged(); }
};

inline ICSPlayerLegacyJump* CCSPlayerLegacyJump::ToInterface() { return new CCSPlayerLegacyJumpImpl(this); }
inline ICSPlayerLegacyJump* ICSPlayerLegacyJump::FromRaw(CEntityInstance*) { return nullptr; }
inline ICSPlayerLegacyJump* ICSPlayerLegacyJump::FromOriginal(CCSPlayerLegacyJump* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSPLAYERLEGACYJUMPIMPL_H
