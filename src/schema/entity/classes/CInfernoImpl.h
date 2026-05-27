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

#ifndef _INCLUDE_CINFERNOIMPL_H
#define _INCLUDE_CINFERNOIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IInferno.h"
#include "schema/entity/classes/CInferno.h"
#include "CBaseModelEntityImpl.h"

class CInfernoImpl : public CBaseModelEntityImpl, public IInferno
{

public:
    explicit CInfernoImpl(CInferno* p) : CBaseModelEntityImpl(p) {}

private:
    CInferno* Real() { return static_cast<CInferno*>(m_pReal); }

public:
    Vector* FirePositions() override { return Real()->m_firePositions(); }
    Vector* FireParentPositions() override { return Real()->m_fireParentPositions(); }
    bool* FireIsBurning() override { return Real()->m_bFireIsBurning(); }
    Vector* BurnNormal() override { return Real()->m_BurnNormal(); }
    int32_t& FireCount() override { return Real()->m_fireCount(); }
    void FireCountUpdated() override { Real()->m_fireCount.NetworkStateChanged(); }
    int32_t& InfernoType() override { return Real()->m_nInfernoType(); }
    void InfernoTypeUpdated() override { Real()->m_nInfernoType.NetworkStateChanged(); }
    int32_t& FireEffectTickBegin() override { return Real()->m_nFireEffectTickBegin(); }
    void FireEffectTickBeginUpdated() override { Real()->m_nFireEffectTickBegin.NetworkStateChanged(); }
    float& FireLifetime() override { return Real()->m_nFireLifetime(); }
    void FireLifetimeUpdated() override { Real()->m_nFireLifetime.NetworkStateChanged(); }
    bool& InPostEffectTime() override { return Real()->m_bInPostEffectTime(); }
    void InPostEffectTimeUpdated() override { Real()->m_bInPostEffectTime.NetworkStateChanged(); }
    bool& WasCreatedInSmoke() override { return Real()->m_bWasCreatedInSmoke(); }
    void WasCreatedInSmokeUpdated() override { Real()->m_bWasCreatedInSmoke.NetworkStateChanged(); }
    Extent& Extent() override { return Real()->m_extent(); }
    void ExtentUpdated() override { Real()->m_extent.NetworkStateChanged(); }
    CountdownTimer& DamageTimer() override { return Real()->m_damageTimer(); }
    void DamageTimerUpdated() override { Real()->m_damageTimer.NetworkStateChanged(); }
    CountdownTimer& DamageRampTimer() override { return Real()->m_damageRampTimer(); }
    void DamageRampTimerUpdated() override { Real()->m_damageRampTimer.NetworkStateChanged(); }
    Vector& SplashVelocity() override { return Real()->m_splashVelocity(); }
    void SplashVelocityUpdated() override { Real()->m_splashVelocity.NetworkStateChanged(); }
    Vector& InitialSplashVelocity() override { return Real()->m_InitialSplashVelocity(); }
    void InitialSplashVelocityUpdated() override { Real()->m_InitialSplashVelocity.NetworkStateChanged(); }
    Vector& StartPos() override { return Real()->m_startPos(); }
    void StartPosUpdated() override { Real()->m_startPos.NetworkStateChanged(); }
    Vector& OriginalSpawnLocation() override { return Real()->m_vecOriginalSpawnLocation(); }
    void OriginalSpawnLocationUpdated() override { Real()->m_vecOriginalSpawnLocation.NetworkStateChanged(); }
    IntervalTimer& ActiveTimer() override { return Real()->m_activeTimer(); }
    void ActiveTimerUpdated() override { Real()->m_activeTimer.NetworkStateChanged(); }
    int32_t& FireSpawnOffset() override { return Real()->m_fireSpawnOffset(); }
    void FireSpawnOffsetUpdated() override { Real()->m_fireSpawnOffset.NetworkStateChanged(); }
    int32_t& MaxFlames() override { return Real()->m_nMaxFlames(); }
    void MaxFlamesUpdated() override { Real()->m_nMaxFlames.NetworkStateChanged(); }
    int32_t& SpreadCount() override { return Real()->m_nSpreadCount(); }
    void SpreadCountUpdated() override { Real()->m_nSpreadCount.NetworkStateChanged(); }
    CountdownTimer& BookkeepingTimer() override { return Real()->m_BookkeepingTimer(); }
    void BookkeepingTimerUpdated() override { Real()->m_BookkeepingTimer.NetworkStateChanged(); }
    CountdownTimer& NextSpreadTimer() override { return Real()->m_NextSpreadTimer(); }
    void NextSpreadTimerUpdated() override { Real()->m_NextSpreadTimer.NetworkStateChanged(); }
    uint16_t& SourceItemDefIndex() override { return Real()->m_nSourceItemDefIndex(); }
    void SourceItemDefIndexUpdated() override { Real()->m_nSourceItemDefIndex.NetworkStateChanged(); }
};

#endif // _INCLUDE_CINFERNOIMPL_H
