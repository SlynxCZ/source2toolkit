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

#ifndef _INCLUDE_CTEAMIMPL_H
#define _INCLUDE_CTEAMIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ITeam.h"
#include "schema/entity/classes/CTeam.h"
#include "CBaseEntityImpl.h"

class CTeamImpl : public CBaseEntityImpl, public ITeam
{

public:
    explicit CTeamImpl(CTeam* p) : CBaseEntityImpl(p) {}

private:
    CTeam* Real() { return static_cast<CTeam*>(m_pReal); }
    CTeam* Real() const { return static_cast<CTeam*>(m_pReal); }

public:
    CTeam* GetOriginal() const override { return Real(); }
    CUtlVector<CHandle<CBasePlayerController>>& PlayerControllers() override { return Real()->m_aPlayerControllers(); }
    void PlayerControllersUpdated() override { Real()->m_aPlayerControllers.NetworkStateChanged(); }
    CUtlVector<CHandle<CBasePlayerPawn>>& Players() override { return Real()->m_aPlayers(); }
    void PlayersUpdated() override { Real()->m_aPlayers.NetworkStateChanged(); }
    int32_t& Score() override { return Real()->m_iScore(); }
    void ScoreUpdated() override { Real()->m_iScore.NetworkStateChanged(); }
    char* Teamname() override { return Real()->m_szTeamname(); }
};

inline ITeam* CTeam::ToInterface() { return new CTeamImpl(this); }
inline ITeam* ITeam::FromOriginal(CTeam* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CTEAMIMPL_H
