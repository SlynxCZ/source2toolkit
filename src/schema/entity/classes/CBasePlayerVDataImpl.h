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

#ifndef _INCLUDE_CBASEPLAYERVDATAIMPL_H
#define _INCLUDE_CBASEPLAYERVDATAIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBasePlayerVData.h"
#include "schema/entity/classes/CBasePlayerVData.h"
#include "CEntitySubclassVDataBaseImpl.h"

class CBasePlayerVDataImpl : public CEntitySubclassVDataBaseImpl, public IBasePlayerVData
{

public:
    explicit CBasePlayerVDataImpl(CBasePlayerVData* p) : CEntitySubclassVDataBaseImpl(p) {}

private:
    CBasePlayerVData* Real() { return static_cast<CBasePlayerVData*>(m_pReal); }
    CBasePlayerVData* Real() const { return static_cast<CBasePlayerVData*>(m_pReal); }

public:
    CBasePlayerVData* GetOriginal() const override { return Real(); }
    CSkillFloat& HeadDamageMultiplier() override { return Real()->m_flHeadDamageMultiplier(); }
    void HeadDamageMultiplierUpdated() override { Real()->m_flHeadDamageMultiplier.NetworkStateChanged(); }
    CSkillFloat& ChestDamageMultiplier() override { return Real()->m_flChestDamageMultiplier(); }
    void ChestDamageMultiplierUpdated() override { Real()->m_flChestDamageMultiplier.NetworkStateChanged(); }
    CSkillFloat& StomachDamageMultiplier() override { return Real()->m_flStomachDamageMultiplier(); }
    void StomachDamageMultiplierUpdated() override { Real()->m_flStomachDamageMultiplier.NetworkStateChanged(); }
    CSkillFloat& ArmDamageMultiplier() override { return Real()->m_flArmDamageMultiplier(); }
    void ArmDamageMultiplierUpdated() override { Real()->m_flArmDamageMultiplier.NetworkStateChanged(); }
    CSkillFloat& LegDamageMultiplier() override { return Real()->m_flLegDamageMultiplier(); }
    void LegDamageMultiplierUpdated() override { Real()->m_flLegDamageMultiplier.NetworkStateChanged(); }
    float& HoldBreathTime() override { return Real()->m_flHoldBreathTime(); }
    void HoldBreathTimeUpdated() override { Real()->m_flHoldBreathTime.NetworkStateChanged(); }
    float& DrowningDamageInterval() override { return Real()->m_flDrowningDamageInterval(); }
    void DrowningDamageIntervalUpdated() override { Real()->m_flDrowningDamageInterval.NetworkStateChanged(); }
    int32_t& DrowningDamageInitial() override { return Real()->m_nDrowningDamageInitial(); }
    void DrowningDamageInitialUpdated() override { Real()->m_nDrowningDamageInitial.NetworkStateChanged(); }
    int32_t& DrowningDamageMax() override { return Real()->m_nDrowningDamageMax(); }
    void DrowningDamageMaxUpdated() override { Real()->m_nDrowningDamageMax.NetworkStateChanged(); }
    int32_t& WaterSpeed() override { return Real()->m_nWaterSpeed(); }
    void WaterSpeedUpdated() override { Real()->m_nWaterSpeed.NetworkStateChanged(); }
    float& UseRange() override { return Real()->m_flUseRange(); }
    void UseRangeUpdated() override { Real()->m_flUseRange.NetworkStateChanged(); }
    float& UseAngleTolerance() override { return Real()->m_flUseAngleTolerance(); }
    void UseAngleToleranceUpdated() override { Real()->m_flUseAngleTolerance.NetworkStateChanged(); }
    float& CrouchTime() override { return Real()->m_flCrouchTime(); }
    void CrouchTimeUpdated() override { Real()->m_flCrouchTime.NetworkStateChanged(); }
};

inline IBasePlayerVData* CBasePlayerVData::ToInterface() { return new CBasePlayerVDataImpl(this); }
inline IBasePlayerVData* IBasePlayerVData::FromOriginal(CBasePlayerVData* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBASEPLAYERVDATAIMPL_H
