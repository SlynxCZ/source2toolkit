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

#ifndef _INCLUDE_CMESSAGEENTITYIMPL_H
#define _INCLUDE_CMESSAGEENTITYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IMessageEntity.h"
#include "schema/entity/classes/CMessageEntity.h"
#include "CPointEntityImpl.h"

class CMessageEntityImpl : public CPointEntityImpl, public virtual IMessageEntity
{

public:
    explicit CMessageEntityImpl(CMessageEntity* p) : CPointEntityImpl(p) {}

private:
    CMessageEntity* Real() { return static_cast<CMessageEntity*>(m_pReal); }
    CMessageEntity* Real() const { return static_cast<CMessageEntity*>(m_pReal); }

public:
    CMessageEntity* GetOriginal() const override { return Real(); }
    int32_t& Radius() override { return Real()->m_radius(); }
    void RadiusUpdated() override { Real()->m_radius.NetworkStateChanged(); }
    CUtlSymbolLarge& MessageText() override { return Real()->m_messageText(); }
    void MessageTextUpdated() override { Real()->m_messageText.NetworkStateChanged(); }
    bool& DrawText() override { return Real()->m_drawText(); }
    void DrawTextUpdated() override { Real()->m_drawText.NetworkStateChanged(); }
    bool& DeveloperOnly() override { return Real()->m_bDeveloperOnly(); }
    void DeveloperOnlyUpdated() override { Real()->m_bDeveloperOnly.NetworkStateChanged(); }
    bool& Enabled() override { return Real()->m_bEnabled(); }
    void EnabledUpdated() override { Real()->m_bEnabled.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IMessageEntity* CMessageEntity::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IMessageEntity*>(tagIt->second.ptr_for_return);
    auto* impl = new CMessageEntityImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IMessageEntity*>(impl));
    return impl;
}
inline IMessageEntity* IMessageEntity::FromRaw(CEntityInstance* p) { return p ? static_cast<CMessageEntity*>(p)->ToInterface() : nullptr; }
inline IMessageEntity* IMessageEntity::FromOriginal(CMessageEntity* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CMESSAGEENTITYIMPL_H
