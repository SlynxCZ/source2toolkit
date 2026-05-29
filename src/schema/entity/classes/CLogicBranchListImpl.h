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

#ifndef _INCLUDE_CLOGICBRANCHLISTIMPL_H
#define _INCLUDE_CLOGICBRANCHLISTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ILogicBranchList.h"
#include "schema/entity/classes/CLogicBranchList.h"
#include "CLogicalEntityImpl.h"

class CLogicBranchListImpl : public CLogicalEntityImpl, public virtual ILogicBranchList
{

public:
    explicit CLogicBranchListImpl(CLogicBranchList* p) : CLogicalEntityImpl(p) {}

private:
    CLogicBranchList* Real() { return static_cast<CLogicBranchList*>(m_pReal); }
    CLogicBranchList* Real() const { return static_cast<CLogicBranchList*>(m_pReal); }

public:
    CLogicBranchList* GetOriginal() const override { return Real(); }
    CUtlSymbolLarge* LogicBranchNames() override { return Real()->m_nLogicBranchNames(); }
    CUtlVector<CHandle<CBaseEntity>>& LogicBranchList() override { return Real()->m_LogicBranchList(); }
    void LogicBranchListUpdated() override { Real()->m_LogicBranchList.NetworkStateChanged(); }
    ::CLogicBranchList__LogicBranchListenerLastState_t& LastState() override { return Real()->m_eLastState(); }
    void LastStateUpdated() override { Real()->m_eLastState.NetworkStateChanged(); }
    ::CEntityIOOutput& OnAllTrue() override { return Real()->m_OnAllTrue(); }
    void OnAllTrueUpdated() override { Real()->m_OnAllTrue.NetworkStateChanged(); }
    ::CEntityIOOutput& OnAllFalse() override { return Real()->m_OnAllFalse(); }
    void OnAllFalseUpdated() override { Real()->m_OnAllFalse.NetworkStateChanged(); }
    ::CEntityIOOutput& OnMixed() override { return Real()->m_OnMixed(); }
    void OnMixedUpdated() override { Real()->m_OnMixed.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline ILogicBranchList* CLogicBranchList::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ILogicBranchList*>(tagIt->second.ptr_for_return);
    auto* impl = new CLogicBranchListImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ILogicBranchList*>(impl));
    return impl;
}
inline ILogicBranchList* ILogicBranchList::FromRaw(CEntityInstance* p) { return p ? static_cast<CLogicBranchList*>(p)->ToInterface() : nullptr; }
inline ILogicBranchList* ILogicBranchList::FromOriginal(CLogicBranchList* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CLOGICBRANCHLISTIMPL_H
