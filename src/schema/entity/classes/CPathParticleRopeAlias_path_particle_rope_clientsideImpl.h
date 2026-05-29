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

#ifndef _INCLUDE_CPATHPARTICLEROPEALIAS_PATH_PARTICLE_ROPE_CLIENTSIDEIMPL_H
#define _INCLUDE_CPATHPARTICLEROPEALIAS_PATH_PARTICLE_ROPE_CLIENTSIDEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPathParticleRopeAlias_path_particle_rope_clientside.h"
#include "schema/entity/classes/CPathParticleRopeAlias_path_particle_rope_clientside.h"
#include "CPathParticleRopeImpl.h"

class CPathParticleRopeAlias_path_particle_rope_clientsideImpl : public CPathParticleRopeImpl, public virtual IPathParticleRopeAlias_path_particle_rope_clientside
{

public:
    explicit CPathParticleRopeAlias_path_particle_rope_clientsideImpl(CPathParticleRopeAlias_path_particle_rope_clientside* p) : CPathParticleRopeImpl(p) {}

private:
    CPathParticleRopeAlias_path_particle_rope_clientside* Real() { return static_cast<CPathParticleRopeAlias_path_particle_rope_clientside*>(m_pReal); }
    CPathParticleRopeAlias_path_particle_rope_clientside* Real() const { return static_cast<CPathParticleRopeAlias_path_particle_rope_clientside*>(m_pReal); }

public:
    CPathParticleRopeAlias_path_particle_rope_clientside* GetOriginal() const override { return Real(); }
};

#include "core/virtualhooks.h"

inline IPathParticleRopeAlias_path_particle_rope_clientside* CPathParticleRopeAlias_path_particle_rope_clientside::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPathParticleRopeAlias_path_particle_rope_clientside*>(tagIt->second.ptr_for_return);
    auto* impl = new CPathParticleRopeAlias_path_particle_rope_clientsideImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPathParticleRopeAlias_path_particle_rope_clientside*>(impl));
    return impl;
}
inline IPathParticleRopeAlias_path_particle_rope_clientside* IPathParticleRopeAlias_path_particle_rope_clientside::FromRaw(CEntityInstance* p) { return p ? static_cast<CPathParticleRopeAlias_path_particle_rope_clientside*>(p)->ToInterface() : nullptr; }
inline IPathParticleRopeAlias_path_particle_rope_clientside* IPathParticleRopeAlias_path_particle_rope_clientside::FromOriginal(CPathParticleRopeAlias_path_particle_rope_clientside* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPATHPARTICLEROPEALIAS_PATH_PARTICLE_ROPE_CLIENTSIDEIMPL_H
