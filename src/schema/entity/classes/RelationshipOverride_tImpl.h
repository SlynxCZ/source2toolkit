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

#ifndef _INCLUDE_RELATIONSHIPOVERRIDE_TIMPL_H
#define _INCLUDE_RELATIONSHIPOVERRIDE_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IRelationshipOverride_t.h"
#include "schema/entity/classes/RelationshipOverride_t.h"
#include "Relationship_tImpl.h"

class RelationshipOverride_tImpl : public Relationship_tImpl, public IRelationshipOverride_t
{

public:
    explicit RelationshipOverride_tImpl(RelationshipOverride_t* p) : Relationship_tImpl(p) {}

private:
    RelationshipOverride_t* Real() { return static_cast<RelationshipOverride_t*>(m_pReal); }
    RelationshipOverride_t* Real() const { return static_cast<RelationshipOverride_t*>(m_pReal); }

public:
    RelationshipOverride_t* GetOriginal() const override { return Real(); }
    CHandle<CBaseEntity>& Entity() override { return Real()->entity(); }
    void EntityUpdated() override { Real()->entity.NetworkStateChanged(); }
    Class_T& ClassType() override { return Real()->classType(); }
    void ClassTypeUpdated() override { Real()->classType.NetworkStateChanged(); }
};

inline IRelationshipOverride_t* RelationshipOverride_t::ToInterface() { return new RelationshipOverride_tImpl(this); }
inline IRelationshipOverride_t* IRelationshipOverride_t::FromOriginal(RelationshipOverride_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_RELATIONSHIPOVERRIDE_TIMPL_H
