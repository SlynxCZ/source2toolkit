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

#ifndef _INCLUDE_CRAGDOLLMAGNETIMPL_H
#define _INCLUDE_CRAGDOLLMAGNETIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IRagdollMagnet.h"
#include "schema/entity/classes/CRagdollMagnet.h"
#include "CPointEntityImpl.h"

class CRagdollMagnetImpl : public CPointEntityImpl, public virtual IRagdollMagnet
{

public:
    explicit CRagdollMagnetImpl(CRagdollMagnet* p) : CPointEntityImpl(p) {}

private:
    CRagdollMagnet* Real() { return static_cast<CRagdollMagnet*>(m_pReal); }
    CRagdollMagnet* Real() const { return static_cast<CRagdollMagnet*>(m_pReal); }

public:
    CRagdollMagnet* GetOriginal() const override { return Real(); }
    bool& Disabled() override { return Real()->m_bDisabled(); }
    void DisabledUpdated() override { Real()->m_bDisabled.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_radius(); }
    void RadiusUpdated() override { Real()->m_radius.NetworkStateChanged(); }
    float& Force() override { return Real()->m_force(); }
    void ForceUpdated() override { Real()->m_force.NetworkStateChanged(); }
    Vector& Axis() override { return Real()->m_axis(); }
    void AxisUpdated() override { Real()->m_axis.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IRagdollMagnet* CRagdollMagnet::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IRagdollMagnet*>(tagIt->second.ptr_for_return);
    auto* impl = new CRagdollMagnetImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IRagdollMagnet*>(impl));
    return impl;
}
inline IRagdollMagnet* IRagdollMagnet::FromRaw(CEntityInstance* p) { return p ? static_cast<CRagdollMagnet*>(p)->ToInterface() : nullptr; }
inline IRagdollMagnet* IRagdollMagnet::FromOriginal(CRagdollMagnet* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CRAGDOLLMAGNETIMPL_H
