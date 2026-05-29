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

#ifndef _INCLUDE_CSMATCHSTATS_TIMPL_H
#define _INCLUDE_CSMATCHSTATS_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISMatchStats_t.h"
#include "schema/entity/classes/CSMatchStats_t.h"
#include "CSPerRoundStats_tImpl.h"

class CSMatchStats_tImpl : public CSPerRoundStats_tImpl, public virtual ISMatchStats_t
{

public:
    explicit CSMatchStats_tImpl(CSMatchStats_t* p) : CSPerRoundStats_tImpl(p) {}

private:
    CSMatchStats_t* Real() { return static_cast<CSMatchStats_t*>(m_pReal); }
    CSMatchStats_t* Real() const { return static_cast<CSMatchStats_t*>(m_pReal); }

public:
    CSMatchStats_t* GetOriginal() const override { return Real(); }
    int32_t& Enemy5Ks() override { return Real()->m_iEnemy5Ks(); }
    void Enemy5KsUpdated() override { Real()->m_iEnemy5Ks.NetworkStateChanged(); }
    int32_t& Enemy4Ks() override { return Real()->m_iEnemy4Ks(); }
    void Enemy4KsUpdated() override { Real()->m_iEnemy4Ks.NetworkStateChanged(); }
    int32_t& Enemy3Ks() override { return Real()->m_iEnemy3Ks(); }
    void Enemy3KsUpdated() override { Real()->m_iEnemy3Ks.NetworkStateChanged(); }
    int32_t& EnemyKnifeKills() override { return Real()->m_iEnemyKnifeKills(); }
    void EnemyKnifeKillsUpdated() override { Real()->m_iEnemyKnifeKills.NetworkStateChanged(); }
    int32_t& EnemyTaserKills() override { return Real()->m_iEnemyTaserKills(); }
    void EnemyTaserKillsUpdated() override { Real()->m_iEnemyTaserKills.NetworkStateChanged(); }
    int32_t& Enemy2Ks() override { return Real()->m_iEnemy2Ks(); }
    void Enemy2KsUpdated() override { Real()->m_iEnemy2Ks.NetworkStateChanged(); }
    int32_t& Utility_Count() override { return Real()->m_iUtility_Count(); }
    void Utility_CountUpdated() override { Real()->m_iUtility_Count.NetworkStateChanged(); }
    int32_t& Utility_Successes() override { return Real()->m_iUtility_Successes(); }
    void Utility_SuccessesUpdated() override { Real()->m_iUtility_Successes.NetworkStateChanged(); }
    int32_t& Utility_Enemies() override { return Real()->m_iUtility_Enemies(); }
    void Utility_EnemiesUpdated() override { Real()->m_iUtility_Enemies.NetworkStateChanged(); }
    int32_t& Flash_Count() override { return Real()->m_iFlash_Count(); }
    void Flash_CountUpdated() override { Real()->m_iFlash_Count.NetworkStateChanged(); }
    int32_t& Flash_Successes() override { return Real()->m_iFlash_Successes(); }
    void Flash_SuccessesUpdated() override { Real()->m_iFlash_Successes.NetworkStateChanged(); }
    float& HealthPointsRemovedTotal() override { return Real()->m_flHealthPointsRemovedTotal(); }
    void HealthPointsRemovedTotalUpdated() override { Real()->m_flHealthPointsRemovedTotal.NetworkStateChanged(); }
    float& HealthPointsDealtTotal() override { return Real()->m_flHealthPointsDealtTotal(); }
    void HealthPointsDealtTotalUpdated() override { Real()->m_flHealthPointsDealtTotal.NetworkStateChanged(); }
    int32_t& ShotsFiredTotal() override { return Real()->m_nShotsFiredTotal(); }
    void ShotsFiredTotalUpdated() override { Real()->m_nShotsFiredTotal.NetworkStateChanged(); }
    int32_t& ShotsOnTargetTotal() override { return Real()->m_nShotsOnTargetTotal(); }
    void ShotsOnTargetTotalUpdated() override { Real()->m_nShotsOnTargetTotal.NetworkStateChanged(); }
    int32_t& I1v1Count() override { return Real()->m_i1v1Count(); }
    void I1v1CountUpdated() override { Real()->m_i1v1Count.NetworkStateChanged(); }
    int32_t& I1v1Wins() override { return Real()->m_i1v1Wins(); }
    void I1v1WinsUpdated() override { Real()->m_i1v1Wins.NetworkStateChanged(); }
    int32_t& I1v2Count() override { return Real()->m_i1v2Count(); }
    void I1v2CountUpdated() override { Real()->m_i1v2Count.NetworkStateChanged(); }
    int32_t& I1v2Wins() override { return Real()->m_i1v2Wins(); }
    void I1v2WinsUpdated() override { Real()->m_i1v2Wins.NetworkStateChanged(); }
    int32_t& EntryCount() override { return Real()->m_iEntryCount(); }
    void EntryCountUpdated() override { Real()->m_iEntryCount.NetworkStateChanged(); }
    int32_t& EntryWins() override { return Real()->m_iEntryWins(); }
    void EntryWinsUpdated() override { Real()->m_iEntryWins.NetworkStateChanged(); }
};

inline ISMatchStats_t* CSMatchStats_t::ToInterface() { return new CSMatchStats_tImpl(this); }
inline ISMatchStats_t* ISMatchStats_t::FromRaw(CEntityInstance*) { return nullptr; }
inline ISMatchStats_t* ISMatchStats_t::FromOriginal(CSMatchStats_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CSMATCHSTATS_TIMPL_H
