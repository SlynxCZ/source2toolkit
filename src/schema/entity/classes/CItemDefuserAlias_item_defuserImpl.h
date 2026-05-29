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

#ifndef _INCLUDE_CITEMDEFUSERALIAS_ITEM_DEFUSERIMPL_H
#define _INCLUDE_CITEMDEFUSERALIAS_ITEM_DEFUSERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IItemDefuserAlias_item_defuser.h"
#include "schema/entity/classes/CItemDefuserAlias_item_defuser.h"
#include "CItemDefuserImpl.h"

class CItemDefuserAlias_item_defuserImpl : public CItemDefuserImpl, public virtual IItemDefuserAlias_item_defuser
{

public:
    explicit CItemDefuserAlias_item_defuserImpl(CItemDefuserAlias_item_defuser* p) : CItemDefuserImpl(p) {}

private:
    CItemDefuserAlias_item_defuser* Real() { return static_cast<CItemDefuserAlias_item_defuser*>(m_pReal); }
    CItemDefuserAlias_item_defuser* Real() const { return static_cast<CItemDefuserAlias_item_defuser*>(m_pReal); }

public:
    CItemDefuserAlias_item_defuser* GetOriginal() const override { return Real(); }
};

#include "core/virtualhooks.h"

inline IItemDefuserAlias_item_defuser* CItemDefuserAlias_item_defuser::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IItemDefuserAlias_item_defuser*>(tagIt->second.ptr_for_return);
    auto* impl = new CItemDefuserAlias_item_defuserImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IItemDefuserAlias_item_defuser*>(impl));
    return impl;
}
inline IItemDefuserAlias_item_defuser* IItemDefuserAlias_item_defuser::FromRaw(CEntityInstance* p) { return p ? static_cast<CItemDefuserAlias_item_defuser*>(p)->ToInterface() : nullptr; }
inline IItemDefuserAlias_item_defuser* IItemDefuserAlias_item_defuser::FromOriginal(CItemDefuserAlias_item_defuser* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CITEMDEFUSERALIAS_ITEM_DEFUSERIMPL_H
