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

#ifndef _INCLUDE_CSOUNDEVENTPATHCORNERENTITYIMPL_H
#define _INCLUDE_CSOUNDEVENTPATHCORNERENTITYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISoundEventPathCornerEntity.h"
#include "schema/entity/classes/CSoundEventPathCornerEntity.h"
#include "CSoundEventEntityImpl.h"

class CSoundEventPathCornerEntityImpl : public CSoundEventEntityImpl, public ISoundEventPathCornerEntity
{

public:
    explicit CSoundEventPathCornerEntityImpl(CSoundEventPathCornerEntity* p) : CSoundEventEntityImpl(p) {}

private:
    CSoundEventPathCornerEntity* Real() { return static_cast<CSoundEventPathCornerEntity*>(m_pReal); }

public:
    CUtlSymbolLarge& PathCorner() override { return Real()->m_iszPathCorner(); }
    void PathCornerUpdated() override { Real()->m_iszPathCorner.NetworkStateChanged(); }
    int32_t& CountMax() override { return Real()->m_iCountMax(); }
    void CountMaxUpdated() override { Real()->m_iCountMax.NetworkStateChanged(); }
    float& DistanceMax() override { return Real()->m_flDistanceMax(); }
    void DistanceMaxUpdated() override { Real()->m_flDistanceMax.NetworkStateChanged(); }
    float& DistMaxSqr() override { return Real()->m_flDistMaxSqr(); }
    void DistMaxSqrUpdated() override { Real()->m_flDistMaxSqr.NetworkStateChanged(); }
    float& DotProductMax() override { return Real()->m_flDotProductMax(); }
    void DotProductMaxUpdated() override { Real()->m_flDotProductMax.NetworkStateChanged(); }
    bool& Playing() override { return Real()->m_bPlaying(); }
    void PlayingUpdated() override { Real()->m_bPlaying.NetworkStateChanged(); }
};

#endif // _INCLUDE_CSOUNDEVENTPATHCORNERENTITYIMPL_H
