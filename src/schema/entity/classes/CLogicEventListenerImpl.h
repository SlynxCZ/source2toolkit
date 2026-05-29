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

#ifndef _INCLUDE_CLOGICEVENTLISTENERIMPL_H
#define _INCLUDE_CLOGICEVENTLISTENERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ILogicEventListener.h"
#include "schema/entity/classes/CLogicEventListener.h"
#include "CLogicalEntityImpl.h"

class CLogicEventListenerImpl : public CLogicalEntityImpl, public virtual ILogicEventListener
{

public:
    explicit CLogicEventListenerImpl(CLogicEventListener* p) : CLogicalEntityImpl(p) {}

private:
    CLogicEventListener* Real() { return static_cast<CLogicEventListener*>(m_pReal); }
    CLogicEventListener* Real() const { return static_cast<CLogicEventListener*>(m_pReal); }

public:
    CLogicEventListener* GetOriginal() const override { return Real(); }
    CUtlString& StrEventName() override { return Real()->m_strEventName(); }
    void StrEventNameUpdated() override { Real()->m_strEventName.NetworkStateChanged(); }
    bool& IsEnabled() override { return Real()->m_bIsEnabled(); }
    void IsEnabledUpdated() override { Real()->m_bIsEnabled.NetworkStateChanged(); }
    int32_t& Team() override { return Real()->m_nTeam(); }
    void TeamUpdated() override { Real()->m_nTeam.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline ILogicEventListener* CLogicEventListener::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ILogicEventListener*>(tagIt->second.ptr_for_return);
    auto* impl = new CLogicEventListenerImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ILogicEventListener*>(impl));
    return impl;
}
inline ILogicEventListener* ILogicEventListener::FromRaw(CEntityInstance* p) { return p ? static_cast<CLogicEventListener*>(p)->ToInterface() : nullptr; }
inline ILogicEventListener* ILogicEventListener::FromOriginal(CLogicEventListener* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CLOGICEVENTLISTENERIMPL_H
