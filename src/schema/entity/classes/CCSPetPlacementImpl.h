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

#ifndef _INCLUDE_CCSPETPLACEMENTIMPL_H
#define _INCLUDE_CCSPETPLACEMENTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPetPlacement.h"
#include "schema/entity/classes/CCSPetPlacement.h"
#include "CBaseEntityImpl.h"

class CCSPetPlacementImpl : public CBaseEntityImpl, public virtual ICSPetPlacement
{

public:
    explicit CCSPetPlacementImpl(CCSPetPlacement* p) : CBaseEntityImpl(p) {}

private:
    CCSPetPlacement* Real() { return static_cast<CCSPetPlacement*>(m_pReal); }
    CCSPetPlacement* Real() const { return static_cast<CCSPetPlacement*>(m_pReal); }

public:
    CCSPetPlacement* GetOriginal() const override { return Real(); }
};

#include "core/virtualhooks.h"

inline ICSPetPlacement* CCSPetPlacement::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ICSPetPlacement*>(tagIt->second.ptr_for_return);
    auto* impl = new CCSPetPlacementImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ICSPetPlacement*>(impl));
    return impl;
}
inline ICSPetPlacement* ICSPetPlacement::FromRaw(CEntityInstance* p) { return p ? static_cast<CCSPetPlacement*>(p)->ToInterface() : nullptr; }
inline ICSPetPlacement* ICSPetPlacement::FromOriginal(CCSPetPlacement* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSPETPLACEMENTIMPL_H
