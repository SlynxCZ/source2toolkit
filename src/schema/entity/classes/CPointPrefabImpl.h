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

#ifndef _INCLUDE_CPOINTPREFABIMPL_H
#define _INCLUDE_CPOINTPREFABIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPointPrefab.h"
#include "schema/entity/classes/CPointPrefab.h"
#include "CServerOnlyPointEntityImpl.h"

class CPointPrefabImpl : public CServerOnlyPointEntityImpl, public virtual IPointPrefab
{

public:
    explicit CPointPrefabImpl(CPointPrefab* p) : CServerOnlyPointEntityImpl(p) {}

private:
    CPointPrefab* Real() { return static_cast<CPointPrefab*>(m_pReal); }
    CPointPrefab* Real() const { return static_cast<CPointPrefab*>(m_pReal); }

public:
    CPointPrefab* GetOriginal() const override { return Real(); }
    CUtlSymbolLarge& TargetMapName() override { return Real()->m_targetMapName(); }
    void TargetMapNameUpdated() override { Real()->m_targetMapName.NetworkStateChanged(); }
    CUtlSymbolLarge& ForceWorldGroupID() override { return Real()->m_forceWorldGroupID(); }
    void ForceWorldGroupIDUpdated() override { Real()->m_forceWorldGroupID.NetworkStateChanged(); }
    CUtlSymbolLarge& AssociatedRelayTargetName() override { return Real()->m_associatedRelayTargetName(); }
    void AssociatedRelayTargetNameUpdated() override { Real()->m_associatedRelayTargetName.NetworkStateChanged(); }
    bool& FixupNames() override { return Real()->m_fixupNames(); }
    void FixupNamesUpdated() override { Real()->m_fixupNames.NetworkStateChanged(); }
    bool& LoadDynamic() override { return Real()->m_bLoadDynamic(); }
    void LoadDynamicUpdated() override { Real()->m_bLoadDynamic.NetworkStateChanged(); }
    CHandle<CPointPrefab>& AssociatedRelayEntity() override { return Real()->m_associatedRelayEntity(); }
    void AssociatedRelayEntityUpdated() override { Real()->m_associatedRelayEntity.NetworkStateChanged(); }
    CUtlVector<CHandle<CBaseEntity>>& ProceduralRelaySources() override { return Real()->m_ProceduralRelaySources(); }
    void ProceduralRelaySourcesUpdated() override { Real()->m_ProceduralRelaySources.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IPointPrefab* CPointPrefab::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPointPrefab*>(tagIt->second.ptr_for_return);
    auto* impl = new CPointPrefabImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPointPrefab*>(impl));
    return impl;
}
inline IPointPrefab* IPointPrefab::FromRaw(CEntityInstance* p) { return p ? static_cast<CPointPrefab*>(p)->ToInterface() : nullptr; }
inline IPointPrefab* IPointPrefab::FromOriginal(CPointPrefab* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPOINTPREFABIMPL_H
