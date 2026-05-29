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

#ifndef _INCLUDE_FILTERHEALTHIMPL_H
#define _INCLUDE_FILTERHEALTHIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IFilterHealth.h"
#include "schema/entity/classes/FilterHealth.h"
#include "CBaseFilterImpl.h"

class FilterHealthImpl : public CBaseFilterImpl, public virtual IFilterHealth
{

public:
    explicit FilterHealthImpl(FilterHealth* p) : CBaseFilterImpl(p) {}

private:
    FilterHealth* Real() { return static_cast<FilterHealth*>(m_pReal); }
    FilterHealth* Real() const { return static_cast<FilterHealth*>(m_pReal); }

public:
    FilterHealth* GetOriginal() const override { return Real(); }
    bool& AdrenalineActive() override { return Real()->m_bAdrenalineActive(); }
    void AdrenalineActiveUpdated() override { Real()->m_bAdrenalineActive.NetworkStateChanged(); }
    int32_t& HealthMin() override { return Real()->m_iHealthMin(); }
    void HealthMinUpdated() override { Real()->m_iHealthMin.NetworkStateChanged(); }
    int32_t& HealthMax() override { return Real()->m_iHealthMax(); }
    void HealthMaxUpdated() override { Real()->m_iHealthMax.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IFilterHealth* FilterHealth::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IFilterHealth*>(tagIt->second.ptr_for_return);
    auto* impl = new FilterHealthImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IFilterHealth*>(impl));
    return impl;
}
inline IFilterHealth* IFilterHealth::FromRaw(CEntityInstance* p) { return p ? static_cast<FilterHealth*>(p)->ToInterface() : nullptr; }
inline IFilterHealth* IFilterHealth::FromOriginal(FilterHealth* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_FILTERHEALTHIMPL_H
