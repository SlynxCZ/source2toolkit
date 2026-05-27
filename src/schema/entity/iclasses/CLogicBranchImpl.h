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

#ifndef _INCLUDE_CLOGICBRANCHIMPL_H
#define _INCLUDE_CLOGICBRANCHIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/ILogicBranch.h"
#include "schema/entity/classes/CLogicBranch.h"
#include "CLogicalEntityImpl.h"

class CLogicBranchImpl : public CLogicalEntityImpl, public ILogicBranch
{

public:
    explicit CLogicBranchImpl(CLogicBranch* p) : CLogicalEntityImpl(p) {}

private:
    CLogicBranch* Real() { return static_cast<CLogicBranch*>(m_pReal); }

public:
    bool& InValue() override { return Real()->m_bInValue(); }
    void InValueUpdated() override { Real()->m_bInValue.NetworkStateChanged(); }
    CUtlVector<CHandle<CBaseEntity>>& Listeners() override { return Real()->m_Listeners(); }
    void ListenersUpdated() override { Real()->m_Listeners.NetworkStateChanged(); }
    CEntityIOOutput& OnTrue() override { return Real()->m_OnTrue(); }
    void OnTrueUpdated() override { Real()->m_OnTrue.NetworkStateChanged(); }
    CEntityIOOutput& OnFalse() override { return Real()->m_OnFalse(); }
    void OnFalseUpdated() override { Real()->m_OnFalse.NetworkStateChanged(); }
};

#endif // _INCLUDE_CLOGICBRANCHIMPL_H
