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

#ifndef _INCLUDE_CLOGICDISTANCECHECKIMPL_H
#define _INCLUDE_CLOGICDISTANCECHECKIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ILogicDistanceCheck.h"
#include "schema/entity/classes/CLogicDistanceCheck.h"
#include "CLogicalEntityImpl.h"

class CLogicDistanceCheckImpl : public CLogicalEntityImpl, public ILogicDistanceCheck
{

public:
    explicit CLogicDistanceCheckImpl(CLogicDistanceCheck* p) : CLogicalEntityImpl(p) {}

private:
    CLogicDistanceCheck* Real() { return static_cast<CLogicDistanceCheck*>(m_pReal); }

public:
    CUtlSymbolLarge& EntityA() override { return Real()->m_iszEntityA(); }
    void EntityAUpdated() override { Real()->m_iszEntityA.NetworkStateChanged(); }
    CUtlSymbolLarge& EntityB() override { return Real()->m_iszEntityB(); }
    void EntityBUpdated() override { Real()->m_iszEntityB.NetworkStateChanged(); }
    float& Zone1Distance() override { return Real()->m_flZone1Distance(); }
    void Zone1DistanceUpdated() override { Real()->m_flZone1Distance.NetworkStateChanged(); }
    float& Zone2Distance() override { return Real()->m_flZone2Distance(); }
    void Zone2DistanceUpdated() override { Real()->m_flZone2Distance.NetworkStateChanged(); }
    CEntityIOOutput& InZone1() override { return Real()->m_InZone1(); }
    void InZone1Updated() override { Real()->m_InZone1.NetworkStateChanged(); }
    CEntityIOOutput& InZone2() override { return Real()->m_InZone2(); }
    void InZone2Updated() override { Real()->m_InZone2.NetworkStateChanged(); }
    CEntityIOOutput& InZone3() override { return Real()->m_InZone3(); }
    void InZone3Updated() override { Real()->m_InZone3.NetworkStateChanged(); }
};

#endif // _INCLUDE_CLOGICDISTANCECHECKIMPL_H
