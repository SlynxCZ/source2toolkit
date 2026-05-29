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

#ifndef _INCLUDE_CBASEDOORIMPL_H
#define _INCLUDE_CBASEDOORIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBaseDoor.h"
#include "schema/entity/classes/CBaseDoor.h"
#include "CBaseToggleImpl.h"

class CBaseDoorImpl : public CBaseToggleImpl, public IBaseDoor
{

public:
    explicit CBaseDoorImpl(CBaseDoor* p) : CBaseToggleImpl(p) {}

private:
    CBaseDoor* Real() { return static_cast<CBaseDoor*>(m_pReal); }
    CBaseDoor* Real() const { return static_cast<CBaseDoor*>(m_pReal); }

public:
    CBaseDoor* GetOriginal() const override { return Real(); }
    QAngle& MoveEntitySpace() override { return Real()->m_angMoveEntitySpace(); }
    void MoveEntitySpaceUpdated() override { Real()->m_angMoveEntitySpace.NetworkStateChanged(); }
    Vector& MoveDirParentSpace() override { return Real()->m_vecMoveDirParentSpace(); }
    void MoveDirParentSpaceUpdated() override { Real()->m_vecMoveDirParentSpace.NetworkStateChanged(); }
    ::locksound_t& Ls() override { return Real()->m_ls(); }
    void LsUpdated() override { Real()->m_ls.NetworkStateChanged(); }
    bool& ForceClosed() override { return Real()->m_bForceClosed(); }
    void ForceClosedUpdated() override { Real()->m_bForceClosed.NetworkStateChanged(); }
    bool& DoorGroup() override { return Real()->m_bDoorGroup(); }
    void DoorGroupUpdated() override { Real()->m_bDoorGroup.NetworkStateChanged(); }
    bool& Locked() override { return Real()->m_bLocked(); }
    void LockedUpdated() override { Real()->m_bLocked.NetworkStateChanged(); }
    bool& IgnoreDebris() override { return Real()->m_bIgnoreDebris(); }
    void IgnoreDebrisUpdated() override { Real()->m_bIgnoreDebris.NetworkStateChanged(); }
    bool& NoNPCs() override { return Real()->m_bNoNPCs(); }
    void NoNPCsUpdated() override { Real()->m_bNoNPCs.NetworkStateChanged(); }
    ::FuncDoorSpawnPos_t& SpawnPosition() override { return Real()->m_eSpawnPosition(); }
    void SpawnPositionUpdated() override { Real()->m_eSpawnPosition.NetworkStateChanged(); }
    float& BlockDamage() override { return Real()->m_flBlockDamage(); }
    void BlockDamageUpdated() override { Real()->m_flBlockDamage.NetworkStateChanged(); }
    CUtlSymbolLarge& NoiseMoving() override { return Real()->m_NoiseMoving(); }
    void NoiseMovingUpdated() override { Real()->m_NoiseMoving.NetworkStateChanged(); }
    CUtlSymbolLarge& NoiseArrived() override { return Real()->m_NoiseArrived(); }
    void NoiseArrivedUpdated() override { Real()->m_NoiseArrived.NetworkStateChanged(); }
    CUtlSymbolLarge& NoiseMovingClosed() override { return Real()->m_NoiseMovingClosed(); }
    void NoiseMovingClosedUpdated() override { Real()->m_NoiseMovingClosed.NetworkStateChanged(); }
    CUtlSymbolLarge& NoiseArrivedClosed() override { return Real()->m_NoiseArrivedClosed(); }
    void NoiseArrivedClosedUpdated() override { Real()->m_NoiseArrivedClosed.NetworkStateChanged(); }
    CUtlSymbolLarge& ChainTarget() override { return Real()->m_ChainTarget(); }
    void ChainTargetUpdated() override { Real()->m_ChainTarget.NetworkStateChanged(); }
    ::CEntityIOOutput& OnBlockedClosing() override { return Real()->m_OnBlockedClosing(); }
    void OnBlockedClosingUpdated() override { Real()->m_OnBlockedClosing.NetworkStateChanged(); }
    ::CEntityIOOutput& OnBlockedOpening() override { return Real()->m_OnBlockedOpening(); }
    void OnBlockedOpeningUpdated() override { Real()->m_OnBlockedOpening.NetworkStateChanged(); }
    ::CEntityIOOutput& OnUnblockedClosing() override { return Real()->m_OnUnblockedClosing(); }
    void OnUnblockedClosingUpdated() override { Real()->m_OnUnblockedClosing.NetworkStateChanged(); }
    ::CEntityIOOutput& OnUnblockedOpening() override { return Real()->m_OnUnblockedOpening(); }
    void OnUnblockedOpeningUpdated() override { Real()->m_OnUnblockedOpening.NetworkStateChanged(); }
    ::CEntityIOOutput& OnFullyClosed() override { return Real()->m_OnFullyClosed(); }
    void OnFullyClosedUpdated() override { Real()->m_OnFullyClosed.NetworkStateChanged(); }
    ::CEntityIOOutput& OnFullyOpen() override { return Real()->m_OnFullyOpen(); }
    void OnFullyOpenUpdated() override { Real()->m_OnFullyOpen.NetworkStateChanged(); }
    ::CEntityIOOutput& OnClose() override { return Real()->m_OnClose(); }
    void OnCloseUpdated() override { Real()->m_OnClose.NetworkStateChanged(); }
    ::CEntityIOOutput& OnOpen() override { return Real()->m_OnOpen(); }
    void OnOpenUpdated() override { Real()->m_OnOpen.NetworkStateChanged(); }
    ::CEntityIOOutput& OnLockedUse() override { return Real()->m_OnLockedUse(); }
    void OnLockedUseUpdated() override { Real()->m_OnLockedUse.NetworkStateChanged(); }
    bool& LoopMoveSound() override { return Real()->m_bLoopMoveSound(); }
    void LoopMoveSoundUpdated() override { Real()->m_bLoopMoveSound.NetworkStateChanged(); }
    bool& CreateNavObstacle() override { return Real()->m_bCreateNavObstacle(); }
    void CreateNavObstacleUpdated() override { Real()->m_bCreateNavObstacle.NetworkStateChanged(); }
    bool& IsChaining() override { return Real()->m_isChaining(); }
    void IsChainingUpdated() override { Real()->m_isChaining.NetworkStateChanged(); }
    bool& IsUsable() override { return Real()->m_bIsUsable(); }
    void IsUsableUpdated() override { Real()->m_bIsUsable.NetworkStateChanged(); }
};

inline IBaseDoor* CBaseDoor::ToInterface() { return new CBaseDoorImpl(this); }
inline IBaseDoor* IBaseDoor::FromOriginal(CBaseDoor* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBASEDOORIMPL_H
