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

#ifndef _INCLUDE_CPUSHABLEIMPL_H
#define _INCLUDE_CPUSHABLEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPushable.h"
#include "schema/entity/classes/CPushable.h"
#include "CBreakableImpl.h"

class CPushableImpl : public CBreakableImpl, public virtual IPushable
{

public:
    explicit CPushableImpl(CPushable* p) : CBreakableImpl(p) {}

private:
    CPushable* Real() { return static_cast<CPushable*>(m_pReal); }
    CPushable* Real() const { return static_cast<CPushable*>(m_pReal); }

public:
    CPushable* GetOriginal() const override { return Real(); }
};

#include "core/virtualhooks.h"

inline IPushable* CPushable::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPushable*>(tagIt->second.ptr_for_return);
    auto* impl = new CPushableImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPushable*>(impl));
    return impl;
}
inline IPushable* IPushable::FromRaw(CEntityInstance* p) { return p ? static_cast<CPushable*>(p)->ToInterface() : nullptr; }
inline IPushable* IPushable::FromOriginal(CPushable* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPUSHABLEIMPL_H
