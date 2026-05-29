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

#ifndef _INCLUDE_CPOINTENTITYFINDERIMPL_H
#define _INCLUDE_CPOINTENTITYFINDERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPointEntityFinder.h"
#include "schema/entity/classes/CPointEntityFinder.h"
#include "CBaseEntityImpl.h"

class CPointEntityFinderImpl : public CBaseEntityImpl, public IPointEntityFinder
{

public:
    explicit CPointEntityFinderImpl(CPointEntityFinder* p) : CBaseEntityImpl(p) {}

private:
    CPointEntityFinder* Real() { return static_cast<CPointEntityFinder*>(m_pReal); }
    CPointEntityFinder* Real() const { return static_cast<CPointEntityFinder*>(m_pReal); }

public:
    CPointEntityFinder* GetOriginal() const override { return Real(); }
    CHandle<CBaseEntity>& Entity() override { return Real()->m_hEntity(); }
    void EntityUpdated() override { Real()->m_hEntity.NetworkStateChanged(); }
    CUtlSymbolLarge& FilterName() override { return Real()->m_iFilterName(); }
    void FilterNameUpdated() override { Real()->m_iFilterName.NetworkStateChanged(); }
    CHandle<CBaseFilter>& Filter() override { return Real()->m_hFilter(); }
    void FilterUpdated() override { Real()->m_hFilter.NetworkStateChanged(); }
    CUtlSymbolLarge& RefName() override { return Real()->m_iRefName(); }
    void RefNameUpdated() override { Real()->m_iRefName.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Reference() override { return Real()->m_hReference(); }
    void ReferenceUpdated() override { Real()->m_hReference.NetworkStateChanged(); }
    ::EntFinderMethod_t& FindMethod() override { return Real()->m_FindMethod(); }
    void FindMethodUpdated() override { Real()->m_FindMethod.NetworkStateChanged(); }
    ::CEntityIOOutput& OnFoundEntity() override { return Real()->m_OnFoundEntity(); }
    void OnFoundEntityUpdated() override { Real()->m_OnFoundEntity.NetworkStateChanged(); }
};

inline IPointEntityFinder* CPointEntityFinder::ToInterface() { return new CPointEntityFinderImpl(this); }
inline IPointEntityFinder* IPointEntityFinder::FromOriginal(CPointEntityFinder* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPOINTENTITYFINDERIMPL_H
