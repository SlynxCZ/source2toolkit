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

#ifndef _INCLUDE_CCSPLAYERCONTROLLER_ACTIONTRACKINGSERVICESIMPL_H
#define _INCLUDE_CCSPLAYERCONTROLLER_ACTIONTRACKINGSERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayerController_ActionTrackingServices.h"
#include "schema/entity/classes/CCSPlayerController_ActionTrackingServices.h"
#include "CPlayerControllerComponentImpl.h"

class CCSPlayerController_ActionTrackingServicesImpl : public CPlayerControllerComponentImpl, public ICSPlayerController_ActionTrackingServices
{

public:
    explicit CCSPlayerController_ActionTrackingServicesImpl(CCSPlayerController_ActionTrackingServices* p) : CPlayerControllerComponentImpl(p) {}

private:
    CCSPlayerController_ActionTrackingServices* Real() { return static_cast<CCSPlayerController_ActionTrackingServices*>(m_pReal); }

public:
    CUtlVector<CSPerRoundStats_t>& PerRoundStats() override { return Real()->m_perRoundStats(); }
    void PerRoundStatsUpdated() override { Real()->m_perRoundStats.NetworkStateChanged(); }
    CSMatchStats_t& MatchStats() override { return Real()->m_matchStats(); }
    void MatchStatsUpdated() override { Real()->m_matchStats.NetworkStateChanged(); }
    int32_t& NumRoundKills() override { return Real()->m_iNumRoundKills(); }
    void NumRoundKillsUpdated() override { Real()->m_iNumRoundKills.NetworkStateChanged(); }
    int32_t& NumRoundKillsHeadshots() override { return Real()->m_iNumRoundKillsHeadshots(); }
    void NumRoundKillsHeadshotsUpdated() override { Real()->m_iNumRoundKillsHeadshots.NetworkStateChanged(); }
    float& TotalRoundDamageDealt() override { return Real()->m_flTotalRoundDamageDealt(); }
    void TotalRoundDamageDealtUpdated() override { Real()->m_flTotalRoundDamageDealt.NetworkStateChanged(); }
};

#endif // _INCLUDE_CCSPLAYERCONTROLLER_ACTIONTRACKINGSERVICESIMPL_H
