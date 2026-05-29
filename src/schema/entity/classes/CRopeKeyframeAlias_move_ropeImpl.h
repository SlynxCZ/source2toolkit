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

#ifndef _INCLUDE_CROPEKEYFRAMEALIAS_MOVE_ROPEIMPL_H
#define _INCLUDE_CROPEKEYFRAMEALIAS_MOVE_ROPEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IRopeKeyframeAlias_move_rope.h"
#include "schema/entity/classes/CRopeKeyframeAlias_move_rope.h"
#include "CRopeKeyframeImpl.h"

class CRopeKeyframeAlias_move_ropeImpl : public CRopeKeyframeImpl, public virtual IRopeKeyframeAlias_move_rope
{

public:
    explicit CRopeKeyframeAlias_move_ropeImpl(CRopeKeyframeAlias_move_rope* p) : CRopeKeyframeImpl(p) {}

private:
    CRopeKeyframeAlias_move_rope* Real() { return static_cast<CRopeKeyframeAlias_move_rope*>(m_pReal); }
    CRopeKeyframeAlias_move_rope* Real() const { return static_cast<CRopeKeyframeAlias_move_rope*>(m_pReal); }

public:
    CRopeKeyframeAlias_move_rope* GetOriginal() const override { return Real(); }
};

#include "core/virtualhooks.h"

inline IRopeKeyframeAlias_move_rope* CRopeKeyframeAlias_move_rope::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IRopeKeyframeAlias_move_rope*>(tagIt->second.ptr_for_return);
    auto* impl = new CRopeKeyframeAlias_move_ropeImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IRopeKeyframeAlias_move_rope*>(impl));
    return impl;
}
inline IRopeKeyframeAlias_move_rope* IRopeKeyframeAlias_move_rope::FromRaw(CEntityInstance* p) { return p ? static_cast<CRopeKeyframeAlias_move_rope*>(p)->ToInterface() : nullptr; }
inline IRopeKeyframeAlias_move_rope* IRopeKeyframeAlias_move_rope::FromOriginal(CRopeKeyframeAlias_move_rope* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CROPEKEYFRAMEALIAS_MOVE_ROPEIMPL_H
