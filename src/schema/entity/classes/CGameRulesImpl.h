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

#ifndef _INCLUDE_CGAMERULESIMPL_H
#define _INCLUDE_CGAMERULESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IGameRules.h"
#include "schema/entity/classes/CGameRules.h"

class CGameRulesImpl : public virtual IGameRules
{

protected:
    void* m_pReal;

public:
    explicit CGameRulesImpl(void* p) : m_pReal(p) {}

private:
    CGameRules* Real() { return static_cast<CGameRules*>(m_pReal); }
    CGameRules* Real() const { return static_cast<CGameRules*>(m_pReal); }

public:
    CGameRules* GetOriginal() const override { return Real(); }
    CEntityInstance*& __m_pChainEntity() override { return Real()->__m_pChainEntity(); }
    void __m_pChainEntityUpdated() override { Real()->__m_pChainEntity.NetworkStateChanged(); }
    char* QuestName() override { return Real()->m_szQuestName(); }
    int32_t& QuestPhase() override { return Real()->m_nQuestPhase(); }
    void QuestPhaseUpdated() override { Real()->m_nQuestPhase.NetworkStateChanged(); }
    uint32_t& LastMatchTime() override { return Real()->m_nLastMatchTime(); }
    void LastMatchTimeUpdated() override { Real()->m_nLastMatchTime.NetworkStateChanged(); }
    uint64_t& LastMatchTime_MatchID64() override { return Real()->m_nLastMatchTime_MatchID64(); }
    void LastMatchTime_MatchID64Updated() override { Real()->m_nLastMatchTime_MatchID64.NetworkStateChanged(); }
    int32_t& TotalPausedTicks() override { return Real()->m_nTotalPausedTicks(); }
    void TotalPausedTicksUpdated() override { Real()->m_nTotalPausedTicks.NetworkStateChanged(); }
    int32_t& PauseStartTick() override { return Real()->m_nPauseStartTick(); }
    void PauseStartTickUpdated() override { Real()->m_nPauseStartTick.NetworkStateChanged(); }
    bool& GamePaused() override { return Real()->m_bGamePaused(); }
    void GamePausedUpdated() override { Real()->m_bGamePaused.NetworkStateChanged(); }
};

inline IGameRules* CGameRules::ToInterface() { return new CGameRulesImpl(this); }
inline IGameRules* IGameRules::FromOriginal(CGameRules* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CGAMERULESIMPL_H
