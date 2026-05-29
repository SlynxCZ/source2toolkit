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

#ifndef _INCLUDE_CSPERROUNDSTATS_TIMPL_H
#define _INCLUDE_CSPERROUNDSTATS_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISPerRoundStats_t.h"
#include "schema/entity/classes/CSPerRoundStats_t.h"

class CSPerRoundStats_tImpl : public virtual ISPerRoundStats_t
{

protected:
    void* m_pReal;

public:
    explicit CSPerRoundStats_tImpl(void* p) : m_pReal(p) {}

private:
    CSPerRoundStats_t* Real() { return static_cast<CSPerRoundStats_t*>(m_pReal); }
    CSPerRoundStats_t* Real() const { return static_cast<CSPerRoundStats_t*>(m_pReal); }

public:
    CSPerRoundStats_t* GetOriginal() const override { return Real(); }
    int32_t& Kills() override { return Real()->m_iKills(); }
    void KillsUpdated() override { Real()->m_iKills.NetworkStateChanged(); }
    int32_t& Deaths() override { return Real()->m_iDeaths(); }
    void DeathsUpdated() override { Real()->m_iDeaths.NetworkStateChanged(); }
    int32_t& Assists() override { return Real()->m_iAssists(); }
    void AssistsUpdated() override { Real()->m_iAssists.NetworkStateChanged(); }
    int32_t& Damage() override { return Real()->m_iDamage(); }
    void DamageUpdated() override { Real()->m_iDamage.NetworkStateChanged(); }
    int32_t& EquipmentValue() override { return Real()->m_iEquipmentValue(); }
    void EquipmentValueUpdated() override { Real()->m_iEquipmentValue.NetworkStateChanged(); }
    int32_t& MoneySaved() override { return Real()->m_iMoneySaved(); }
    void MoneySavedUpdated() override { Real()->m_iMoneySaved.NetworkStateChanged(); }
    int32_t& KillReward() override { return Real()->m_iKillReward(); }
    void KillRewardUpdated() override { Real()->m_iKillReward.NetworkStateChanged(); }
    int32_t& LiveTime() override { return Real()->m_iLiveTime(); }
    void LiveTimeUpdated() override { Real()->m_iLiveTime.NetworkStateChanged(); }
    int32_t& HeadShotKills() override { return Real()->m_iHeadShotKills(); }
    void HeadShotKillsUpdated() override { Real()->m_iHeadShotKills.NetworkStateChanged(); }
    int32_t& Objective() override { return Real()->m_iObjective(); }
    void ObjectiveUpdated() override { Real()->m_iObjective.NetworkStateChanged(); }
    int32_t& CashEarned() override { return Real()->m_iCashEarned(); }
    void CashEarnedUpdated() override { Real()->m_iCashEarned.NetworkStateChanged(); }
    int32_t& UtilityDamage() override { return Real()->m_iUtilityDamage(); }
    void UtilityDamageUpdated() override { Real()->m_iUtilityDamage.NetworkStateChanged(); }
    int32_t& EnemiesFlashed() override { return Real()->m_iEnemiesFlashed(); }
    void EnemiesFlashedUpdated() override { Real()->m_iEnemiesFlashed.NetworkStateChanged(); }
};

inline ISPerRoundStats_t* CSPerRoundStats_t::ToInterface() { return new CSPerRoundStats_tImpl(this); }
inline ISPerRoundStats_t* ISPerRoundStats_t::FromRaw(CEntityInstance*) { return nullptr; }
inline ISPerRoundStats_t* ISPerRoundStats_t::FromOriginal(CSPerRoundStats_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CSPERROUNDSTATS_TIMPL_H
