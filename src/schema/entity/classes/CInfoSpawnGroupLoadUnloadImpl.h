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

#ifndef _INCLUDE_CINFOSPAWNGROUPLOADUNLOADIMPL_H
#define _INCLUDE_CINFOSPAWNGROUPLOADUNLOADIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IInfoSpawnGroupLoadUnload.h"
#include "schema/entity/classes/CInfoSpawnGroupLoadUnload.h"
#include "CLogicalEntityImpl.h"

class CInfoSpawnGroupLoadUnloadImpl : public CLogicalEntityImpl, public IInfoSpawnGroupLoadUnload
{

public:
    explicit CInfoSpawnGroupLoadUnloadImpl(CInfoSpawnGroupLoadUnload* p) : CLogicalEntityImpl(p) {}

private:
    CInfoSpawnGroupLoadUnload* Real() { return static_cast<CInfoSpawnGroupLoadUnload*>(m_pReal); }

public:
    CEntityIOOutput& OnSpawnGroupLoadStarted() override { return Real()->m_OnSpawnGroupLoadStarted(); }
    void OnSpawnGroupLoadStartedUpdated() override { Real()->m_OnSpawnGroupLoadStarted.NetworkStateChanged(); }
    CEntityIOOutput& OnSpawnGroupLoadFinished() override { return Real()->m_OnSpawnGroupLoadFinished(); }
    void OnSpawnGroupLoadFinishedUpdated() override { Real()->m_OnSpawnGroupLoadFinished.NetworkStateChanged(); }
    CEntityIOOutput& OnSpawnGroupUnloadStarted() override { return Real()->m_OnSpawnGroupUnloadStarted(); }
    void OnSpawnGroupUnloadStartedUpdated() override { Real()->m_OnSpawnGroupUnloadStarted.NetworkStateChanged(); }
    CEntityIOOutput& OnSpawnGroupUnloadFinished() override { return Real()->m_OnSpawnGroupUnloadFinished(); }
    void OnSpawnGroupUnloadFinishedUpdated() override { Real()->m_OnSpawnGroupUnloadFinished.NetworkStateChanged(); }
    CUtlSymbolLarge& SpawnGroupName() override { return Real()->m_iszSpawnGroupName(); }
    void SpawnGroupNameUpdated() override { Real()->m_iszSpawnGroupName.NetworkStateChanged(); }
    CUtlSymbolLarge& SpawnGroupFilterName() override { return Real()->m_iszSpawnGroupFilterName(); }
    void SpawnGroupFilterNameUpdated() override { Real()->m_iszSpawnGroupFilterName.NetworkStateChanged(); }
    CUtlSymbolLarge& LandmarkName() override { return Real()->m_iszLandmarkName(); }
    void LandmarkNameUpdated() override { Real()->m_iszLandmarkName.NetworkStateChanged(); }
    CUtlString& FixedSpawnGroupName() override { return Real()->m_sFixedSpawnGroupName(); }
    void FixedSpawnGroupNameUpdated() override { Real()->m_sFixedSpawnGroupName.NetworkStateChanged(); }
    float& TimeoutInterval() override { return Real()->m_flTimeoutInterval(); }
    void TimeoutIntervalUpdated() override { Real()->m_flTimeoutInterval.NetworkStateChanged(); }
    bool& AutoActivate() override { return Real()->m_bAutoActivate(); }
    void AutoActivateUpdated() override { Real()->m_bAutoActivate.NetworkStateChanged(); }
    bool& UnloadingStarted() override { return Real()->m_bUnloadingStarted(); }
    void UnloadingStartedUpdated() override { Real()->m_bUnloadingStarted.NetworkStateChanged(); }
    bool& QueueActiveSpawnGroupChange() override { return Real()->m_bQueueActiveSpawnGroupChange(); }
    void QueueActiveSpawnGroupChangeUpdated() override { Real()->m_bQueueActiveSpawnGroupChange.NetworkStateChanged(); }
    bool& QueueFinishLoading() override { return Real()->m_bQueueFinishLoading(); }
    void QueueFinishLoadingUpdated() override { Real()->m_bQueueFinishLoading.NetworkStateChanged(); }
};

#endif // _INCLUDE_CINFOSPAWNGROUPLOADUNLOADIMPL_H
