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

#ifndef _INCLUDE_CBUYZONEIMPL_H
#define _INCLUDE_CBUYZONEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBuyZone.h"
#include "schema/entity/classes/CBuyZone.h"
#include "CBaseTriggerImpl.h"

class CBuyZoneImpl : public CBaseTriggerImpl, public virtual IBuyZone
{

public:
    explicit CBuyZoneImpl(CBuyZone* p) : CBaseTriggerImpl(p) {}

private:
    CBuyZone* Real() { return static_cast<CBuyZone*>(m_pReal); }
    CBuyZone* Real() const { return static_cast<CBuyZone*>(m_pReal); }

public:
    CBuyZone* GetOriginal() const override { return Real(); }
    int32_t& LegacyTeamNum() override { return Real()->m_LegacyTeamNum(); }
    void LegacyTeamNumUpdated() override { Real()->m_LegacyTeamNum.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IBuyZone* CBuyZone::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IBuyZone*>(tagIt->second.ptr_for_return);
    auto* impl = new CBuyZoneImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IBuyZone*>(impl));
    return impl;
}
inline IBuyZone* IBuyZone::FromRaw(CEntityInstance* p) { return p ? static_cast<CBuyZone*>(p)->ToInterface() : nullptr; }
inline IBuyZone* IBuyZone::FromOriginal(CBuyZone* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBUYZONEIMPL_H
