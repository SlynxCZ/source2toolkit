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

#ifndef _INCLUDE_CSOUNDOPVARSETAUTOROOMENTITYIMPL_H
#define _INCLUDE_CSOUNDOPVARSETAUTOROOMENTITYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISoundOpvarSetAutoRoomEntity.h"
#include "schema/entity/classes/CSoundOpvarSetAutoRoomEntity.h"
#include "CSoundOpvarSetPointEntityImpl.h"

class CSoundOpvarSetAutoRoomEntityImpl : public CSoundOpvarSetPointEntityImpl, public ISoundOpvarSetAutoRoomEntity
{

public:
    explicit CSoundOpvarSetAutoRoomEntityImpl(CSoundOpvarSetAutoRoomEntity* p) : CSoundOpvarSetPointEntityImpl(p) {}

private:
    CSoundOpvarSetAutoRoomEntity* Real() { return static_cast<CSoundOpvarSetAutoRoomEntity*>(m_pReal); }
    CSoundOpvarSetAutoRoomEntity* Real() const { return static_cast<CSoundOpvarSetAutoRoomEntity*>(m_pReal); }

public:
    CSoundOpvarSetAutoRoomEntity* GetOriginal() const override { return Real(); }
    CUtlVector<SoundOpvarTraceResult_t>& TraceResults() override { return Real()->m_traceResults(); }
    void TraceResultsUpdated() override { Real()->m_traceResults.NetworkStateChanged(); }
    CUtlVector<AutoRoomDoorwayPairs_t>& DoorwayPairs() override { return Real()->m_doorwayPairs(); }
    void DoorwayPairsUpdated() override { Real()->m_doorwayPairs.NetworkStateChanged(); }
    float& Size() override { return Real()->m_flSize(); }
    void SizeUpdated() override { Real()->m_flSize.NetworkStateChanged(); }
    float& HeightTolerance() override { return Real()->m_flHeightTolerance(); }
    void HeightToleranceUpdated() override { Real()->m_flHeightTolerance.NetworkStateChanged(); }
    float& SizeSqr() override { return Real()->m_flSizeSqr(); }
    void SizeSqrUpdated() override { Real()->m_flSizeSqr.NetworkStateChanged(); }
};

inline ISoundOpvarSetAutoRoomEntity* CSoundOpvarSetAutoRoomEntity::ToInterface() { return new CSoundOpvarSetAutoRoomEntityImpl(this); }
inline ISoundOpvarSetAutoRoomEntity* ISoundOpvarSetAutoRoomEntity::FromOriginal(CSoundOpvarSetAutoRoomEntity* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CSOUNDOPVARSETAUTOROOMENTITYIMPL_H
