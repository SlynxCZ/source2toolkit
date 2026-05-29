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

#ifndef _INCLUDE_CWEAPONMP7IMPL_H
#define _INCLUDE_CWEAPONMP7IMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IWeaponMP7.h"
#include "schema/entity/classes/CWeaponMP7.h"
#include "CCSWeaponBaseGunImpl.h"

class CWeaponMP7Impl : public CCSWeaponBaseGunImpl, public virtual IWeaponMP7
{

public:
    explicit CWeaponMP7Impl(CWeaponMP7* p) : CCSWeaponBaseGunImpl(p) {}

private:
    CWeaponMP7* Real() { return static_cast<CWeaponMP7*>(m_pReal); }
    CWeaponMP7* Real() const { return static_cast<CWeaponMP7*>(m_pReal); }

public:
    CWeaponMP7* GetOriginal() const override { return Real(); }
};

#include "core/virtualhooks.h"

inline IWeaponMP7* CWeaponMP7::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IWeaponMP7*>(tagIt->second.ptr_for_return);
    auto* impl = new CWeaponMP7Impl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IWeaponMP7*>(impl));
    return impl;
}
inline IWeaponMP7* IWeaponMP7::FromRaw(CEntityInstance* p) { return p ? static_cast<CWeaponMP7*>(p)->ToInterface() : nullptr; }
inline IWeaponMP7* IWeaponMP7::FromOriginal(CWeaponMP7* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CWEAPONMP7IMPL_H
