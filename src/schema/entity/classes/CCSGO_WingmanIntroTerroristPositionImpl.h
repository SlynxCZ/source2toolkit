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

#ifndef _INCLUDE_CCSGO_WINGMANINTROTERRORISTPOSITIONIMPL_H
#define _INCLUDE_CCSGO_WINGMANINTROTERRORISTPOSITIONIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSGO_WingmanIntroTerroristPosition.h"
#include "schema/entity/classes/CCSGO_WingmanIntroTerroristPosition.h"
#include "CCSGO_WingmanIntroCharacterPositionImpl.h"

class CCSGO_WingmanIntroTerroristPositionImpl : public CCSGO_WingmanIntroCharacterPositionImpl, public virtual ICSGO_WingmanIntroTerroristPosition
{

public:
    explicit CCSGO_WingmanIntroTerroristPositionImpl(CCSGO_WingmanIntroTerroristPosition* p) : CCSGO_WingmanIntroCharacterPositionImpl(p) {}

private:
    CCSGO_WingmanIntroTerroristPosition* Real() { return static_cast<CCSGO_WingmanIntroTerroristPosition*>(m_pReal); }
    CCSGO_WingmanIntroTerroristPosition* Real() const { return static_cast<CCSGO_WingmanIntroTerroristPosition*>(m_pReal); }

public:
    CCSGO_WingmanIntroTerroristPosition* GetOriginal() const override { return Real(); }
};

#include "core/virtualhooks.h"

inline ICSGO_WingmanIntroTerroristPosition* CCSGO_WingmanIntroTerroristPosition::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ICSGO_WingmanIntroTerroristPosition*>(tagIt->second.ptr_for_return);
    auto* impl = new CCSGO_WingmanIntroTerroristPositionImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ICSGO_WingmanIntroTerroristPosition*>(impl));
    return impl;
}
inline ICSGO_WingmanIntroTerroristPosition* ICSGO_WingmanIntroTerroristPosition::FromRaw(CEntityInstance* p) { return p ? static_cast<CCSGO_WingmanIntroTerroristPosition*>(p)->ToInterface() : nullptr; }
inline ICSGO_WingmanIntroTerroristPosition* ICSGO_WingmanIntroTerroristPosition::FromOriginal(CCSGO_WingmanIntroTerroristPosition* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSGO_WINGMANINTROTERRORISTPOSITIONIMPL_H
