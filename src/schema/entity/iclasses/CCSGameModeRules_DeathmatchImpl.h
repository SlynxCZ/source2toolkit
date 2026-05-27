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

#ifndef _INCLUDE_CCSGAMEMODERULES_DEATHMATCHIMPL_H
#define _INCLUDE_CCSGAMEMODERULES_DEATHMATCHIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/ICSGameModeRules_Deathmatch.h"
#include "schema/entity/classes/CCSGameModeRules_Deathmatch.h"
#include "CCSGameModeRulesImpl.h"

class CCSGameModeRules_DeathmatchImpl : public CCSGameModeRulesImpl, public ICSGameModeRules_Deathmatch
{

public:
    explicit CCSGameModeRules_DeathmatchImpl(CCSGameModeRules_Deathmatch* p) : CCSGameModeRulesImpl(p) {}

private:
    CCSGameModeRules_Deathmatch* Real() { return static_cast<CCSGameModeRules_Deathmatch*>(m_pReal); }

public:
    float& DMBonusStartTime() override { return Real()->m_flDMBonusStartTime(); }
    void DMBonusStartTimeUpdated() override { Real()->m_flDMBonusStartTime.NetworkStateChanged(); }
    float& DMBonusTimeLength() override { return Real()->m_flDMBonusTimeLength(); }
    void DMBonusTimeLengthUpdated() override { Real()->m_flDMBonusTimeLength.NetworkStateChanged(); }
    CUtlString& DMBonusWeapon() override { return Real()->m_sDMBonusWeapon(); }
    void DMBonusWeaponUpdated() override { Real()->m_sDMBonusWeapon.NetworkStateChanged(); }
};

#endif // _INCLUDE_CCSGAMEMODERULES_DEATHMATCHIMPL_H
