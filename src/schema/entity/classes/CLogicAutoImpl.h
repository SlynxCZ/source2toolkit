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

#ifndef _INCLUDE_CLOGICAUTOIMPL_H
#define _INCLUDE_CLOGICAUTOIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ILogicAuto.h"
#include "schema/entity/classes/CLogicAuto.h"
#include "CBaseEntityImpl.h"

class CLogicAutoImpl : public CBaseEntityImpl, public ILogicAuto
{

public:
    explicit CLogicAutoImpl(CLogicAuto* p) : CBaseEntityImpl(p) {}

private:
    CLogicAuto* Real() { return static_cast<CLogicAuto*>(m_pReal); }

public:
    CEntityIOOutput& OnMapSpawn() override { return Real()->m_OnMapSpawn(); }
    void OnMapSpawnUpdated() override { Real()->m_OnMapSpawn.NetworkStateChanged(); }
    CEntityIOOutput& OnDemoMapSpawn() override { return Real()->m_OnDemoMapSpawn(); }
    void OnDemoMapSpawnUpdated() override { Real()->m_OnDemoMapSpawn.NetworkStateChanged(); }
    CEntityIOOutput& OnNewGame() override { return Real()->m_OnNewGame(); }
    void OnNewGameUpdated() override { Real()->m_OnNewGame.NetworkStateChanged(); }
    CEntityIOOutput& OnLoadGame() override { return Real()->m_OnLoadGame(); }
    void OnLoadGameUpdated() override { Real()->m_OnLoadGame.NetworkStateChanged(); }
    CEntityIOOutput& OnMapTransition() override { return Real()->m_OnMapTransition(); }
    void OnMapTransitionUpdated() override { Real()->m_OnMapTransition.NetworkStateChanged(); }
    CEntityIOOutput& OnBackgroundMap() override { return Real()->m_OnBackgroundMap(); }
    void OnBackgroundMapUpdated() override { Real()->m_OnBackgroundMap.NetworkStateChanged(); }
    CEntityIOOutput& OnMultiNewMap() override { return Real()->m_OnMultiNewMap(); }
    void OnMultiNewMapUpdated() override { Real()->m_OnMultiNewMap.NetworkStateChanged(); }
    CEntityIOOutput& OnMultiNewRound() override { return Real()->m_OnMultiNewRound(); }
    void OnMultiNewRoundUpdated() override { Real()->m_OnMultiNewRound.NetworkStateChanged(); }
    CEntityIOOutput& OnVREnabled() override { return Real()->m_OnVREnabled(); }
    void OnVREnabledUpdated() override { Real()->m_OnVREnabled.NetworkStateChanged(); }
    CEntityIOOutput& OnVRNotEnabled() override { return Real()->m_OnVRNotEnabled(); }
    void OnVRNotEnabledUpdated() override { Real()->m_OnVRNotEnabled.NetworkStateChanged(); }
    CUtlSymbolLarge& Globalstate() override { return Real()->m_globalstate(); }
    void GlobalstateUpdated() override { Real()->m_globalstate.NetworkStateChanged(); }
};

#endif // _INCLUDE_CLOGICAUTOIMPL_H
