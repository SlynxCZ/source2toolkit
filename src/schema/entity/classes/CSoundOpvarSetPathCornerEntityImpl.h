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

#ifndef _INCLUDE_CSOUNDOPVARSETPATHCORNERENTITYIMPL_H
#define _INCLUDE_CSOUNDOPVARSETPATHCORNERENTITYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISoundOpvarSetPathCornerEntity.h"
#include "schema/entity/classes/CSoundOpvarSetPathCornerEntity.h"
#include "CSoundOpvarSetPointEntityImpl.h"

class CSoundOpvarSetPathCornerEntityImpl : public CSoundOpvarSetPointEntityImpl, public ISoundOpvarSetPathCornerEntity
{

public:
    explicit CSoundOpvarSetPathCornerEntityImpl(CSoundOpvarSetPathCornerEntity* p) : CSoundOpvarSetPointEntityImpl(p) {}

private:
    CSoundOpvarSetPathCornerEntity* Real() { return static_cast<CSoundOpvarSetPathCornerEntity*>(m_pReal); }
    CSoundOpvarSetPathCornerEntity* Real() const { return static_cast<CSoundOpvarSetPathCornerEntity*>(m_pReal); }

public:
    CSoundOpvarSetPathCornerEntity* GetOriginal() const override { return Real(); }
    bool& UseParentedPath() override { return Real()->m_bUseParentedPath(); }
    void UseParentedPathUpdated() override { Real()->m_bUseParentedPath.NetworkStateChanged(); }
    float& DistMinSqr() override { return Real()->m_flDistMinSqr(); }
    void DistMinSqrUpdated() override { Real()->m_flDistMinSqr.NetworkStateChanged(); }
    float& DistMaxSqr() override { return Real()->m_flDistMaxSqr(); }
    void DistMaxSqrUpdated() override { Real()->m_flDistMaxSqr.NetworkStateChanged(); }
    CUtlSymbolLarge& PathCornerEntityName() override { return Real()->m_iszPathCornerEntityName(); }
    void PathCornerEntityNameUpdated() override { Real()->m_iszPathCornerEntityName.NetworkStateChanged(); }
};

inline ISoundOpvarSetPathCornerEntity* CSoundOpvarSetPathCornerEntity::ToInterface() { return new CSoundOpvarSetPathCornerEntityImpl(this); }
inline ISoundOpvarSetPathCornerEntity* ISoundOpvarSetPathCornerEntity::FromOriginal(CSoundOpvarSetPathCornerEntity* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CSOUNDOPVARSETPATHCORNERENTITYIMPL_H
