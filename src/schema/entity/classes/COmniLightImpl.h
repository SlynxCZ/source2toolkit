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

#ifndef _INCLUDE_COMNILIGHTIMPL_H
#define _INCLUDE_COMNILIGHTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IOmniLight.h"
#include "schema/entity/classes/COmniLight.h"
#include "CBarnLightImpl.h"

class COmniLightImpl : public CBarnLightImpl, public virtual IOmniLight
{

public:
    explicit COmniLightImpl(COmniLight* p) : CBarnLightImpl(p) {}

private:
    COmniLight* Real() { return static_cast<COmniLight*>(m_pReal); }
    COmniLight* Real() const { return static_cast<COmniLight*>(m_pReal); }

public:
    COmniLight* GetOriginal() const override { return Real(); }
    float& InnerAngle() override { return Real()->m_flInnerAngle(); }
    void InnerAngleUpdated() override { Real()->m_flInnerAngle.NetworkStateChanged(); }
    float& OuterAngle() override { return Real()->m_flOuterAngle(); }
    void OuterAngleUpdated() override { Real()->m_flOuterAngle.NetworkStateChanged(); }
    bool& ShowLight() override { return Real()->m_bShowLight(); }
    void ShowLightUpdated() override { Real()->m_bShowLight.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IOmniLight* COmniLight::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IOmniLight*>(tagIt->second.ptr_for_return);
    auto* impl = new COmniLightImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IOmniLight*>(impl));
    return impl;
}
inline IOmniLight* IOmniLight::FromRaw(CEntityInstance* p) { return p ? static_cast<COmniLight*>(p)->ToInterface() : nullptr; }
inline IOmniLight* IOmniLight::FromOriginal(COmniLight* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_COMNILIGHTIMPL_H
