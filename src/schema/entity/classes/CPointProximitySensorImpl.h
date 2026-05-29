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

#ifndef _INCLUDE_CPOINTPROXIMITYSENSORIMPL_H
#define _INCLUDE_CPOINTPROXIMITYSENSORIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPointProximitySensor.h"
#include "schema/entity/classes/CPointProximitySensor.h"
#include "CPointEntityImpl.h"

class CPointProximitySensorImpl : public CPointEntityImpl, public virtual IPointProximitySensor
{

public:
    explicit CPointProximitySensorImpl(CPointProximitySensor* p) : CPointEntityImpl(p) {}

private:
    CPointProximitySensor* Real() { return static_cast<CPointProximitySensor*>(m_pReal); }
    CPointProximitySensor* Real() const { return static_cast<CPointProximitySensor*>(m_pReal); }

public:
    CPointProximitySensor* GetOriginal() const override { return Real(); }
    bool& Disabled() override { return Real()->m_bDisabled(); }
    void DisabledUpdated() override { Real()->m_bDisabled.NetworkStateChanged(); }
    CHandle<CBaseEntity>& TargetEntity() override { return Real()->m_hTargetEntity(); }
    void TargetEntityUpdated() override { Real()->m_hTargetEntity.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IPointProximitySensor* CPointProximitySensor::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPointProximitySensor*>(tagIt->second.ptr_for_return);
    auto* impl = new CPointProximitySensorImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPointProximitySensor*>(impl));
    return impl;
}
inline IPointProximitySensor* IPointProximitySensor::FromRaw(CEntityInstance* p) { return p ? static_cast<CPointProximitySensor*>(p)->ToInterface() : nullptr; }
inline IPointProximitySensor* IPointProximitySensor::FromOriginal(CPointProximitySensor* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPOINTPROXIMITYSENSORIMPL_H
