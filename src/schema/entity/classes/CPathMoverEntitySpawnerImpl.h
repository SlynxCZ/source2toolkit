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

#ifndef _INCLUDE_CPATHMOVERENTITYSPAWNERIMPL_H
#define _INCLUDE_CPATHMOVERENTITYSPAWNERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPathMoverEntitySpawner.h"
#include "schema/entity/classes/CPathMoverEntitySpawner.h"
#include "CLogicalEntityImpl.h"

class CPathMoverEntitySpawnerImpl : public CLogicalEntityImpl, public IPathMoverEntitySpawner
{

public:
    explicit CPathMoverEntitySpawnerImpl(CPathMoverEntitySpawner* p) : CLogicalEntityImpl(p) {}

private:
    CPathMoverEntitySpawner* Real() { return static_cast<CPathMoverEntitySpawner*>(m_pReal); }
    CPathMoverEntitySpawner* Real() const { return static_cast<CPathMoverEntitySpawner*>(m_pReal); }

public:
    CPathMoverEntitySpawner* GetOriginal() const override { return Real(); }
    CUtlSymbolLarge* SpawnTemplates() override { return Real()->m_szSpawnTemplates(); }
    int32_t& SpawnIndex() override { return Real()->m_nSpawnIndex(); }
    void SpawnIndexUpdated() override { Real()->m_nSpawnIndex.NetworkStateChanged(); }
    CHandle<CPathMover>& PathMover() override { return Real()->m_hPathMover(); }
    void PathMoverUpdated() override { Real()->m_hPathMover.NetworkStateChanged(); }
    float& SpawnFrequencySeconds() override { return Real()->m_flSpawnFrequencySeconds(); }
    void SpawnFrequencySecondsUpdated() override { Real()->m_flSpawnFrequencySeconds.NetworkStateChanged(); }
    float& SpawnFrequencyDistToNearestMover() override { return Real()->m_flSpawnFrequencyDistToNearestMover(); }
    void SpawnFrequencyDistToNearestMoverUpdated() override { Real()->m_flSpawnFrequencyDistToNearestMover.NetworkStateChanged(); }
    int32_t& MaxActive() override { return Real()->m_nMaxActive(); }
    void MaxActiveUpdated() override { Real()->m_nMaxActive.NetworkStateChanged(); }
    int32_t& SpawnNum() override { return Real()->m_nSpawnNum(); }
    void SpawnNumUpdated() override { Real()->m_nSpawnNum.NetworkStateChanged(); }
    float& LastSpawnTime() override { return Real()->m_flLastSpawnTime(); }
    void LastSpawnTimeUpdated() override { Real()->m_flLastSpawnTime.NetworkStateChanged(); }
    bool& Enabled() override { return Real()->m_bEnabled(); }
    void EnabledUpdated() override { Real()->m_bEnabled.NetworkStateChanged(); }
    bool& DestroyMoverOnArrivedAtEnd() override { return Real()->m_bDestroyMoverOnArrivedAtEnd(); }
    void DestroyMoverOnArrivedAtEndUpdated() override { Real()->m_bDestroyMoverOnArrivedAtEnd.NetworkStateChanged(); }
    CUtlVector<CHandle<CFuncMover>>& QueuedRemovals() override { return Real()->m_vecQueuedRemovals(); }
    void QueuedRemovalsUpdated() override { Real()->m_vecQueuedRemovals.NetworkStateChanged(); }
    CEntityIOOutput& OnTemplateSpawned() override { return Real()->m_OnTemplateSpawned(); }
    void OnTemplateSpawnedUpdated() override { Real()->m_OnTemplateSpawned.NetworkStateChanged(); }
    CEntityIOOutput& OnTemplateGroupSpawned() override { return Real()->m_OnTemplateGroupSpawned(); }
    void OnTemplateGroupSpawnedUpdated() override { Real()->m_OnTemplateGroupSpawned.NetworkStateChanged(); }
};

inline IPathMoverEntitySpawner* CPathMoverEntitySpawner::ToInterface() { return new CPathMoverEntitySpawnerImpl(this); }
inline IPathMoverEntitySpawner* IPathMoverEntitySpawner::FromOriginal(CPathMoverEntitySpawner* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPATHMOVERENTITYSPAWNERIMPL_H
