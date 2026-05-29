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

#ifndef _INCLUDE_CENVBEVERAGEIMPL_H
#define _INCLUDE_CENVBEVERAGEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvBeverage.h"
#include "schema/entity/classes/CEnvBeverage.h"
#include "CBaseEntityImpl.h"

class CEnvBeverageImpl : public CBaseEntityImpl, public virtual IEnvBeverage
{

public:
    explicit CEnvBeverageImpl(CEnvBeverage* p) : CBaseEntityImpl(p) {}

private:
    CEnvBeverage* Real() { return static_cast<CEnvBeverage*>(m_pReal); }
    CEnvBeverage* Real() const { return static_cast<CEnvBeverage*>(m_pReal); }

public:
    CEnvBeverage* GetOriginal() const override { return Real(); }
    bool& CanInDispenser() override { return Real()->m_CanInDispenser(); }
    void CanInDispenserUpdated() override { Real()->m_CanInDispenser.NetworkStateChanged(); }
    int32_t& BeverageType() override { return Real()->m_nBeverageType(); }
    void BeverageTypeUpdated() override { Real()->m_nBeverageType.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IEnvBeverage* CEnvBeverage::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IEnvBeverage*>(tagIt->second.ptr_for_return);
    auto* impl = new CEnvBeverageImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IEnvBeverage*>(impl));
    return impl;
}
inline IEnvBeverage* IEnvBeverage::FromRaw(CEntityInstance* p) { return p ? static_cast<CEnvBeverage*>(p)->ToInterface() : nullptr; }
inline IEnvBeverage* IEnvBeverage::FromOriginal(CEnvBeverage* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CENVBEVERAGEIMPL_H
