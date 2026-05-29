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

#ifndef _INCLUDE_SPAWNPOINTIMPL_H
#define _INCLUDE_SPAWNPOINTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISpawnPoint.h"
#include "schema/entity/classes/SpawnPoint.h"
#include "CServerOnlyPointEntityImpl.h"

class SpawnPointImpl : public CServerOnlyPointEntityImpl, public ISpawnPoint
{

public:
    explicit SpawnPointImpl(SpawnPoint* p) : CServerOnlyPointEntityImpl(p) {}

private:
    SpawnPoint* Real() { return static_cast<SpawnPoint*>(m_pReal); }
    SpawnPoint* Real() const { return static_cast<SpawnPoint*>(m_pReal); }

public:
    SpawnPoint* GetOriginal() const override { return Real(); }
    int32_t& Priority() override { return Real()->m_iPriority(); }
    void PriorityUpdated() override { Real()->m_iPriority.NetworkStateChanged(); }
    bool& Enabled() override { return Real()->m_bEnabled(); }
    void EnabledUpdated() override { Real()->m_bEnabled.NetworkStateChanged(); }
    int32_t& Type() override { return Real()->m_nType(); }
    void TypeUpdated() override { Real()->m_nType.NetworkStateChanged(); }
};

inline ISpawnPoint* SpawnPoint::ToInterface() { return new SpawnPointImpl(this); }
inline ISpawnPoint* ISpawnPoint::FromOriginal(SpawnPoint* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_SPAWNPOINTIMPL_H
