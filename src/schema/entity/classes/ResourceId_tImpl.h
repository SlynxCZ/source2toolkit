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

#ifndef _INCLUDE_RESOURCEID_TIMPL_H
#define _INCLUDE_RESOURCEID_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IResourceId_t.h"
#include "schema/entity/classes/ResourceId_t.h"

class ResourceId_tImpl : public virtual IResourceId_t
{

protected:
    void* m_pReal;

public:
    explicit ResourceId_tImpl(void* p) : m_pReal(p) {}

private:
    ResourceId_t* Real() { return static_cast<ResourceId_t*>(m_pReal); }
    ResourceId_t* Real() const { return static_cast<ResourceId_t*>(m_pReal); }

public:
    ResourceId_t* GetOriginal() const override { return Real(); }
    uint64_t& Value() override { return Real()->m_Value(); }
    void ValueUpdated() override { Real()->m_Value.NetworkStateChanged(); }
};

inline IResourceId_t* ResourceId_t::ToInterface() { return new ResourceId_tImpl(this); }
inline IResourceId_t* IResourceId_t::FromRaw(CEntityInstance*) { return nullptr; }
inline IResourceId_t* IResourceId_t::FromOriginal(ResourceId_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_RESOURCEID_TIMPL_H
