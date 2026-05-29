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

#ifndef _INCLUDE_MAGNETTED_OBJECTS_TIMPL_H
#define _INCLUDE_MAGNETTED_OBJECTS_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/Imagnetted_objects_t.h"
#include "schema/entity/classes/magnetted_objects_t.h"

class magnetted_objects_tImpl : public virtual Imagnetted_objects_t
{

protected:
    void* m_pReal;

public:
    explicit magnetted_objects_tImpl(void* p) : m_pReal(p) {}

private:
    magnetted_objects_t* Real() { return static_cast<magnetted_objects_t*>(m_pReal); }
    magnetted_objects_t* Real() const { return static_cast<magnetted_objects_t*>(m_pReal); }

public:
    magnetted_objects_t* GetOriginal() const override { return Real(); }
    CHandle<CBaseEntity>& Entity() override { return Real()->hEntity(); }
    void EntityUpdated() override { Real()->hEntity.NetworkStateChanged(); }
};

inline Imagnetted_objects_t* magnetted_objects_t::ToInterface() { return new magnetted_objects_tImpl(this); }
inline Imagnetted_objects_t* Imagnetted_objects_t::FromRaw(CEntityInstance*) { return nullptr; }
inline Imagnetted_objects_t* Imagnetted_objects_t::FromOriginal(magnetted_objects_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_MAGNETTED_OBJECTS_TIMPL_H
