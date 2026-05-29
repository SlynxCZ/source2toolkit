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

#ifndef _INCLUDE_CLOGICCOLLISIONPAIRIMPL_H
#define _INCLUDE_CLOGICCOLLISIONPAIRIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ILogicCollisionPair.h"
#include "schema/entity/classes/CLogicCollisionPair.h"
#include "CLogicalEntityImpl.h"

class CLogicCollisionPairImpl : public CLogicalEntityImpl, public ILogicCollisionPair
{

public:
    explicit CLogicCollisionPairImpl(CLogicCollisionPair* p) : CLogicalEntityImpl(p) {}

private:
    CLogicCollisionPair* Real() { return static_cast<CLogicCollisionPair*>(m_pReal); }
    CLogicCollisionPair* Real() const { return static_cast<CLogicCollisionPair*>(m_pReal); }

public:
    CLogicCollisionPair* GetOriginal() const override { return Real(); }
    CUtlSymbolLarge& NameAttach1() override { return Real()->m_nameAttach1(); }
    void NameAttach1Updated() override { Real()->m_nameAttach1.NetworkStateChanged(); }
    CUtlSymbolLarge& NameAttach2() override { return Real()->m_nameAttach2(); }
    void NameAttach2Updated() override { Real()->m_nameAttach2.NetworkStateChanged(); }
    bool& IncludeHierarchy() override { return Real()->m_includeHierarchy(); }
    void IncludeHierarchyUpdated() override { Real()->m_includeHierarchy.NetworkStateChanged(); }
    bool& SupportMultipleEntitiesWithSameName() override { return Real()->m_supportMultipleEntitiesWithSameName(); }
    void SupportMultipleEntitiesWithSameNameUpdated() override { Real()->m_supportMultipleEntitiesWithSameName.NetworkStateChanged(); }
    bool& Disabled() override { return Real()->m_disabled(); }
    void DisabledUpdated() override { Real()->m_disabled.NetworkStateChanged(); }
    bool& Succeeded() override { return Real()->m_succeeded(); }
    void SucceededUpdated() override { Real()->m_succeeded.NetworkStateChanged(); }
};

inline ILogicCollisionPair* CLogicCollisionPair::ToInterface() { return new CLogicCollisionPairImpl(this); }
inline ILogicCollisionPair* ILogicCollisionPair::FromOriginal(CLogicCollisionPair* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CLOGICCOLLISIONPAIRIMPL_H
