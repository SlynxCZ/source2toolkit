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

#ifndef _INCLUDE_CPOINTCLIENTCOMMANDIMPL_H
#define _INCLUDE_CPOINTCLIENTCOMMANDIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPointClientCommand.h"
#include "schema/entity/classes/CPointClientCommand.h"
#include "CPointEntityImpl.h"

class CPointClientCommandImpl : public CPointEntityImpl, public virtual IPointClientCommand
{

public:
    explicit CPointClientCommandImpl(CPointClientCommand* p) : CPointEntityImpl(p) {}

private:
    CPointClientCommand* Real() { return static_cast<CPointClientCommand*>(m_pReal); }
    CPointClientCommand* Real() const { return static_cast<CPointClientCommand*>(m_pReal); }

public:
    CPointClientCommand* GetOriginal() const override { return Real(); }
};

#include "core/virtualhooks.h"

inline IPointClientCommand* CPointClientCommand::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPointClientCommand*>(tagIt->second.ptr_for_return);
    auto* impl = new CPointClientCommandImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPointClientCommand*>(impl));
    return impl;
}
inline IPointClientCommand* IPointClientCommand::FromRaw(CEntityInstance* p) { return p ? static_cast<CPointClientCommand*>(p)->ToInterface() : nullptr; }
inline IPointClientCommand* IPointClientCommand::FromOriginal(CPointClientCommand* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPOINTCLIENTCOMMANDIMPL_H
