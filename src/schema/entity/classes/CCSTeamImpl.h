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

#ifndef _INCLUDE_CCSTEAMIMPL_H
#define _INCLUDE_CCSTEAMIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSTeam.h"
#include "schema/entity/classes/CCSTeam.h"
#include "CTeamImpl.h"

class CCSTeamImpl : public CTeamImpl, public ICSTeam
{

public:
    explicit CCSTeamImpl(CCSTeam* p) : CTeamImpl(p) {}

private:
    CCSTeam* Real() { return static_cast<CCSTeam*>(m_pReal); }

public:
    int32_t& LastRecievedShorthandedRoundBonus() override { return Real()->m_nLastRecievedShorthandedRoundBonus(); }
    void LastRecievedShorthandedRoundBonusUpdated() override { Real()->m_nLastRecievedShorthandedRoundBonus.NetworkStateChanged(); }
    int32_t& ShorthandedRoundBonusStartRound() override { return Real()->m_nShorthandedRoundBonusStartRound(); }
    void ShorthandedRoundBonusStartRoundUpdated() override { Real()->m_nShorthandedRoundBonusStartRound.NetworkStateChanged(); }
    bool& Surrendered() override { return Real()->m_bSurrendered(); }
    void SurrenderedUpdated() override { Real()->m_bSurrendered.NetworkStateChanged(); }
    char* TeamMatchStat() override { return Real()->m_szTeamMatchStat(); }
    int32_t& NumMapVictories() override { return Real()->m_numMapVictories(); }
    void NumMapVictoriesUpdated() override { Real()->m_numMapVictories.NetworkStateChanged(); }
    int32_t& ScoreFirstHalf() override { return Real()->m_scoreFirstHalf(); }
    void ScoreFirstHalfUpdated() override { Real()->m_scoreFirstHalf.NetworkStateChanged(); }
    int32_t& ScoreSecondHalf() override { return Real()->m_scoreSecondHalf(); }
    void ScoreSecondHalfUpdated() override { Real()->m_scoreSecondHalf.NetworkStateChanged(); }
    int32_t& ScoreOvertime() override { return Real()->m_scoreOvertime(); }
    void ScoreOvertimeUpdated() override { Real()->m_scoreOvertime.NetworkStateChanged(); }
    char* ClanTeamname() override { return Real()->m_szClanTeamname(); }
    uint32_t& ClanID() override { return Real()->m_iClanID(); }
    void ClanIDUpdated() override { Real()->m_iClanID.NetworkStateChanged(); }
    char* TeamFlagImage() override { return Real()->m_szTeamFlagImage(); }
    char* TeamLogoImage() override { return Real()->m_szTeamLogoImage(); }
    float& NextResourceTime() override { return Real()->m_flNextResourceTime(); }
    void NextResourceTimeUpdated() override { Real()->m_flNextResourceTime.NetworkStateChanged(); }
    int32_t& LastUpdateSentAt() override { return Real()->m_iLastUpdateSentAt(); }
    void LastUpdateSentAtUpdated() override { Real()->m_iLastUpdateSentAt.NetworkStateChanged(); }
};

#endif // _INCLUDE_CCSTEAMIMPL_H
