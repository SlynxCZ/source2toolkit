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

#ifndef _INCLUDE_CWEAPONBASEITEMIMPL_H
#define _INCLUDE_CWEAPONBASEITEMIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IWeaponBaseItem.h"
#include "schema/entity/classes/CWeaponBaseItem.h"
#include "CCSWeaponBaseImpl.h"

class CWeaponBaseItemImpl : public CCSWeaponBaseImpl, public virtual IWeaponBaseItem
{

public:
    explicit CWeaponBaseItemImpl(CWeaponBaseItem* p) : CCSWeaponBaseImpl(p) {}

private:
    CWeaponBaseItem* Real() { return static_cast<CWeaponBaseItem*>(m_pReal); }
    CWeaponBaseItem* Real() const { return static_cast<CWeaponBaseItem*>(m_pReal); }

public:
    CWeaponBaseItem* GetOriginal() const override { return Real(); }
    bool& SequenceInProgress() override { return Real()->m_bSequenceInProgress(); }
    void SequenceInProgressUpdated() override { Real()->m_bSequenceInProgress.NetworkStateChanged(); }
    bool& Redraw() override { return Real()->m_bRedraw(); }
    void RedrawUpdated() override { Real()->m_bRedraw.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IWeaponBaseItem* CWeaponBaseItem::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IWeaponBaseItem*>(tagIt->second.ptr_for_return);
    auto* impl = new CWeaponBaseItemImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IWeaponBaseItem*>(impl));
    return impl;
}
inline IWeaponBaseItem* IWeaponBaseItem::FromRaw(CEntityInstance* p) { return p ? static_cast<CWeaponBaseItem*>(p)->ToInterface() : nullptr; }
inline IWeaponBaseItem* IWeaponBaseItem::FromOriginal(CWeaponBaseItem* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CWEAPONBASEITEMIMPL_H
