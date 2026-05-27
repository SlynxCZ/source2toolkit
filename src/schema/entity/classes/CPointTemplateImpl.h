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

#ifndef _INCLUDE_CPOINTTEMPLATEIMPL_H
#define _INCLUDE_CPOINTTEMPLATEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPointTemplate.h"
#include "schema/entity/classes/CPointTemplate.h"
#include "CLogicalEntityImpl.h"

class CPointTemplateImpl : public CLogicalEntityImpl, public IPointTemplate
{

public:
    explicit CPointTemplateImpl(CPointTemplate* p) : CLogicalEntityImpl(p) {}

private:
    CPointTemplate* Real() { return static_cast<CPointTemplate*>(m_pReal); }

public:
    CUtlSymbolLarge& WorldName() override { return Real()->m_iszWorldName(); }
    void WorldNameUpdated() override { Real()->m_iszWorldName.NetworkStateChanged(); }
    CUtlSymbolLarge& Source2EntityLumpName() override { return Real()->m_iszSource2EntityLumpName(); }
    void Source2EntityLumpNameUpdated() override { Real()->m_iszSource2EntityLumpName.NetworkStateChanged(); }
    CUtlSymbolLarge& EntityFilterName() override { return Real()->m_iszEntityFilterName(); }
    void EntityFilterNameUpdated() override { Real()->m_iszEntityFilterName.NetworkStateChanged(); }
    float& TimeoutInterval() override { return Real()->m_flTimeoutInterval(); }
    void TimeoutIntervalUpdated() override { Real()->m_flTimeoutInterval.NetworkStateChanged(); }
    bool& AsynchronouslySpawnEntities() override { return Real()->m_bAsynchronouslySpawnEntities(); }
    void AsynchronouslySpawnEntitiesUpdated() override { Real()->m_bAsynchronouslySpawnEntities.NetworkStateChanged(); }
    PointTemplateClientOnlyEntityBehavior_t& ClientOnlyEntityBehavior() override { return Real()->m_clientOnlyEntityBehavior(); }
    void ClientOnlyEntityBehaviorUpdated() override { Real()->m_clientOnlyEntityBehavior.NetworkStateChanged(); }
    PointTemplateOwnerSpawnGroupType_t& OwnerSpawnGroupType() override { return Real()->m_ownerSpawnGroupType(); }
    void OwnerSpawnGroupTypeUpdated() override { Real()->m_ownerSpawnGroupType.NetworkStateChanged(); }
    CUtlVector<uint32_t>& CreatedSpawnGroupHandles() override { return Real()->m_createdSpawnGroupHandles(); }
    void CreatedSpawnGroupHandlesUpdated() override { Real()->m_createdSpawnGroupHandles.NetworkStateChanged(); }
    CUtlVector<CEntityHandle>& SpawnedEntityHandles() override { return Real()->m_SpawnedEntityHandles(); }
    void SpawnedEntityHandlesUpdated() override { Real()->m_SpawnedEntityHandles.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPOINTTEMPLATEIMPL_H
