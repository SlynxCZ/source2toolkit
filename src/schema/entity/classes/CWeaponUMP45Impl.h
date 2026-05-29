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

#ifndef _INCLUDE_CWEAPONUMP45IMPL_H
#define _INCLUDE_CWEAPONUMP45IMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IWeaponUMP45.h"
#include "schema/entity/classes/CWeaponUMP45.h"
#include "CCSWeaponBaseGunImpl.h"

class CWeaponUMP45Impl : public CCSWeaponBaseGunImpl, public virtual IWeaponUMP45
{

public:
    explicit CWeaponUMP45Impl(CWeaponUMP45* p) : CCSWeaponBaseGunImpl(p) {}

private:
    CWeaponUMP45* Real() { return static_cast<CWeaponUMP45*>(m_pReal); }
    CWeaponUMP45* Real() const { return static_cast<CWeaponUMP45*>(m_pReal); }

public:
    CWeaponUMP45* GetOriginal() const override { return Real(); }
};

#include "core/virtualhooks.h"

inline IWeaponUMP45* CWeaponUMP45::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IWeaponUMP45*>(tagIt->second.ptr_for_return);
    auto* impl = new CWeaponUMP45Impl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IWeaponUMP45*>(impl));
    return impl;
}
inline IWeaponUMP45* IWeaponUMP45::FromRaw(CEntityInstance* p) { return p ? static_cast<CWeaponUMP45*>(p)->ToInterface() : nullptr; }
inline IWeaponUMP45* IWeaponUMP45::FromOriginal(CWeaponUMP45* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CWEAPONUMP45IMPL_H
