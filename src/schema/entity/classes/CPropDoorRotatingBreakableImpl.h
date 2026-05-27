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

#ifndef _INCLUDE_CPROPDOORROTATINGBREAKABLEIMPL_H
#define _INCLUDE_CPROPDOORROTATINGBREAKABLEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPropDoorRotatingBreakable.h"
#include "schema/entity/classes/CPropDoorRotatingBreakable.h"
#include "CPropDoorRotatingImpl.h"

class CPropDoorRotatingBreakableImpl : public CPropDoorRotatingImpl, public IPropDoorRotatingBreakable
{

public:
    explicit CPropDoorRotatingBreakableImpl(CPropDoorRotatingBreakable* p) : CPropDoorRotatingImpl(p) {}

private:
    CPropDoorRotatingBreakable* Real() { return static_cast<CPropDoorRotatingBreakable*>(m_pReal); }

public:
    bool& Breakable() override { return Real()->m_bBreakable(); }
    void BreakableUpdated() override { Real()->m_bBreakable.NetworkStateChanged(); }
    bool& IsAbleToCloseAreaPortals() override { return Real()->m_isAbleToCloseAreaPortals(); }
    void IsAbleToCloseAreaPortalsUpdated() override { Real()->m_isAbleToCloseAreaPortals.NetworkStateChanged(); }
    int32_t& CurrentDamageState() override { return Real()->m_currentDamageState(); }
    void CurrentDamageStateUpdated() override { Real()->m_currentDamageState.NetworkStateChanged(); }
    CUtlVector<CUtlSymbolLarge>& DamageStates() override { return Real()->m_damageStates(); }
    void DamageStatesUpdated() override { Real()->m_damageStates.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPROPDOORROTATINGBREAKABLEIMPL_H
