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

#ifndef _INCLUDE_CLOGICAUTOSAVEIMPL_H
#define _INCLUDE_CLOGICAUTOSAVEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ILogicAutosave.h"
#include "schema/entity/classes/CLogicAutosave.h"
#include "CLogicalEntityImpl.h"

class CLogicAutosaveImpl : public CLogicalEntityImpl, public virtual ILogicAutosave
{

public:
    explicit CLogicAutosaveImpl(CLogicAutosave* p) : CLogicalEntityImpl(p) {}

private:
    CLogicAutosave* Real() { return static_cast<CLogicAutosave*>(m_pReal); }
    CLogicAutosave* Real() const { return static_cast<CLogicAutosave*>(m_pReal); }

public:
    CLogicAutosave* GetOriginal() const override { return Real(); }
    bool& ForceNewLevelUnit() override { return Real()->m_bForceNewLevelUnit(); }
    void ForceNewLevelUnitUpdated() override { Real()->m_bForceNewLevelUnit.NetworkStateChanged(); }
    int32_t& MinHitPoints() override { return Real()->m_minHitPoints(); }
    void MinHitPointsUpdated() override { Real()->m_minHitPoints.NetworkStateChanged(); }
    int32_t& MinHitPointsToCommit() override { return Real()->m_minHitPointsToCommit(); }
    void MinHitPointsToCommitUpdated() override { Real()->m_minHitPointsToCommit.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline ILogicAutosave* CLogicAutosave::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ILogicAutosave*>(tagIt->second.ptr_for_return);
    auto* impl = new CLogicAutosaveImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ILogicAutosave*>(impl));
    return impl;
}
inline ILogicAutosave* ILogicAutosave::FromRaw(CEntityInstance* p) { return p ? static_cast<CLogicAutosave*>(p)->ToInterface() : nullptr; }
inline ILogicAutosave* ILogicAutosave::FromOriginal(CLogicAutosave* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CLOGICAUTOSAVEIMPL_H
