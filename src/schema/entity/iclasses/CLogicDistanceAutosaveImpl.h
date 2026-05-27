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

#ifndef _INCLUDE_CLOGICDISTANCEAUTOSAVEIMPL_H
#define _INCLUDE_CLOGICDISTANCEAUTOSAVEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/ILogicDistanceAutosave.h"
#include "schema/entity/classes/CLogicDistanceAutosave.h"
#include "CLogicalEntityImpl.h"

class CLogicDistanceAutosaveImpl : public CLogicalEntityImpl, public ILogicDistanceAutosave
{

public:
    explicit CLogicDistanceAutosaveImpl(CLogicDistanceAutosave* p) : CLogicalEntityImpl(p) {}

private:
    CLogicDistanceAutosave* Real() { return static_cast<CLogicDistanceAutosave*>(m_pReal); }

public:
    CUtlSymbolLarge& TargetEntity() override { return Real()->m_iszTargetEntity(); }
    void TargetEntityUpdated() override { Real()->m_iszTargetEntity.NetworkStateChanged(); }
    float& DistanceToPlayer() override { return Real()->m_flDistanceToPlayer(); }
    void DistanceToPlayerUpdated() override { Real()->m_flDistanceToPlayer.NetworkStateChanged(); }
    bool& ForceNewLevelUnit() override { return Real()->m_bForceNewLevelUnit(); }
    void ForceNewLevelUnitUpdated() override { Real()->m_bForceNewLevelUnit.NetworkStateChanged(); }
    bool& CheckCough() override { return Real()->m_bCheckCough(); }
    void CheckCoughUpdated() override { Real()->m_bCheckCough.NetworkStateChanged(); }
    bool& ThinkDangerous() override { return Real()->m_bThinkDangerous(); }
    void ThinkDangerousUpdated() override { Real()->m_bThinkDangerous.NetworkStateChanged(); }
    float& DangerousTime() override { return Real()->m_flDangerousTime(); }
    void DangerousTimeUpdated() override { Real()->m_flDangerousTime.NetworkStateChanged(); }
};

#endif // _INCLUDE_CLOGICDISTANCEAUTOSAVEIMPL_H
