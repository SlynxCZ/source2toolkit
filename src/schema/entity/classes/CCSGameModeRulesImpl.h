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

#ifndef _INCLUDE_CCSGAMEMODERULESIMPL_H
#define _INCLUDE_CCSGAMEMODERULESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSGameModeRules.h"
#include "schema/entity/classes/CCSGameModeRules.h"

class CCSGameModeRulesImpl : public virtual ICSGameModeRules
{

protected:
    void* m_pReal;

public:
    explicit CCSGameModeRulesImpl(void* p) : m_pReal(p) {}

private:
    CCSGameModeRules* Real() { return static_cast<CCSGameModeRules*>(m_pReal); }
    CCSGameModeRules* Real() const { return static_cast<CCSGameModeRules*>(m_pReal); }

public:
    CCSGameModeRules* GetOriginal() const override { return Real(); }
    CEntityInstance*& __m_pChainEntity() override { return Real()->__m_pChainEntity(); }
    void __m_pChainEntityUpdated() override { Real()->__m_pChainEntity.NetworkStateChanged(); }
};

inline ICSGameModeRules* CCSGameModeRules::ToInterface() { return new CCSGameModeRulesImpl(this); }
inline ICSGameModeRules* ICSGameModeRules::FromOriginal(CCSGameModeRules* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSGAMEMODERULESIMPL_H
