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

#ifndef _INCLUDE_CBASEPROPDOORIMPL_H
#define _INCLUDE_CBASEPROPDOORIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBasePropDoor.h"
#include "schema/entity/classes/CBasePropDoor.h"
#include "CDynamicPropImpl.h"

class CBasePropDoorImpl : public CDynamicPropImpl, public virtual IBasePropDoor
{

public:
    explicit CBasePropDoorImpl(CBasePropDoor* p) : CDynamicPropImpl(p) {}

private:
    CBasePropDoor* Real() { return static_cast<CBasePropDoor*>(m_pReal); }
    CBasePropDoor* Real() const { return static_cast<CBasePropDoor*>(m_pReal); }

public:
    CBasePropDoor* GetOriginal() const override { return Real(); }
    float& AutoReturnDelay() override { return Real()->m_flAutoReturnDelay(); }
    void AutoReturnDelayUpdated() override { Real()->m_flAutoReturnDelay.NetworkStateChanged(); }
    CUtlVector<CHandle<CBasePropDoor>>& DoorList() override { return Real()->m_hDoorList(); }
    void DoorListUpdated() override { Real()->m_hDoorList.NetworkStateChanged(); }
    int32_t& HardwareType() override { return Real()->m_nHardwareType(); }
    void HardwareTypeUpdated() override { Real()->m_nHardwareType.NetworkStateChanged(); }
    bool& NeedsHardware() override { return Real()->m_bNeedsHardware(); }
    void NeedsHardwareUpdated() override { Real()->m_bNeedsHardware.NetworkStateChanged(); }
    ::DoorState_t& DoorState() override { return Real()->m_eDoorState(); }
    void DoorStateUpdated() override { Real()->m_eDoorState.NetworkStateChanged(); }
    bool& Locked() override { return Real()->m_bLocked(); }
    void LockedUpdated() override { Real()->m_bLocked.NetworkStateChanged(); }
    bool& NoNPCs() override { return Real()->m_bNoNPCs(); }
    void NoNPCsUpdated() override { Real()->m_bNoNPCs.NetworkStateChanged(); }
    Vector& ClosedPosition() override { return Real()->m_closedPosition(); }
    void ClosedPositionUpdated() override { Real()->m_closedPosition.NetworkStateChanged(); }
    QAngle& ClosedAngles() override { return Real()->m_closedAngles(); }
    void ClosedAnglesUpdated() override { Real()->m_closedAngles.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Blocker() override { return Real()->m_hBlocker(); }
    void BlockerUpdated() override { Real()->m_hBlocker.NetworkStateChanged(); }
    bool& FirstBlocked() override { return Real()->m_bFirstBlocked(); }
    void FirstBlockedUpdated() override { Real()->m_bFirstBlocked.NetworkStateChanged(); }
    ::locksound_t& Ls() override { return Real()->m_ls(); }
    void LsUpdated() override { Real()->m_ls.NetworkStateChanged(); }
    bool& ForceClosed() override { return Real()->m_bForceClosed(); }
    void ForceClosedUpdated() override { Real()->m_bForceClosed.NetworkStateChanged(); }
    Vector& LatchWorldPosition() override { return Real()->m_vecLatchWorldPosition(); }
    void LatchWorldPositionUpdated() override { Real()->m_vecLatchWorldPosition.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Activator() override { return Real()->m_hActivator(); }
    void ActivatorUpdated() override { Real()->m_hActivator.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundMoving() override { return Real()->m_SoundMoving(); }
    void SoundMovingUpdated() override { Real()->m_SoundMoving.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundOpen() override { return Real()->m_SoundOpen(); }
    void SoundOpenUpdated() override { Real()->m_SoundOpen.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundClose() override { return Real()->m_SoundClose(); }
    void SoundCloseUpdated() override { Real()->m_SoundClose.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundLock() override { return Real()->m_SoundLock(); }
    void SoundLockUpdated() override { Real()->m_SoundLock.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundUnlock() override { return Real()->m_SoundUnlock(); }
    void SoundUnlockUpdated() override { Real()->m_SoundUnlock.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundLatch() override { return Real()->m_SoundLatch(); }
    void SoundLatchUpdated() override { Real()->m_SoundLatch.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundPound() override { return Real()->m_SoundPound(); }
    void SoundPoundUpdated() override { Real()->m_SoundPound.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundJiggle() override { return Real()->m_SoundJiggle(); }
    void SoundJiggleUpdated() override { Real()->m_SoundJiggle.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundLockedAnim() override { return Real()->m_SoundLockedAnim(); }
    void SoundLockedAnimUpdated() override { Real()->m_SoundLockedAnim.NetworkStateChanged(); }
    int32_t& NumCloseAttempts() override { return Real()->m_numCloseAttempts(); }
    void NumCloseAttemptsUpdated() override { Real()->m_numCloseAttempts.NetworkStateChanged(); }
    CUtlStringToken* PhysicsMaterial() override { return Real()->m_nPhysicsMaterial(); }
    CUtlSymbolLarge& SlaveName() override { return Real()->m_SlaveName(); }
    void SlaveNameUpdated() override { Real()->m_SlaveName.NetworkStateChanged(); }
    CHandle<CBasePropDoor>& Master() override { return Real()->m_hMaster(); }
    void MasterUpdated() override { Real()->m_hMaster.NetworkStateChanged(); }
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
    ::CEntityIOOutput& OnAjarOpen() override { return Real()->m_OnAjarOpen(); }
    void OnAjarOpenUpdated() override { Real()->m_OnAjarOpen.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IBasePropDoor* CBasePropDoor::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IBasePropDoor*>(tagIt->second.ptr_for_return);
    auto* impl = new CBasePropDoorImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IBasePropDoor*>(impl));
    return impl;
}
inline IBasePropDoor* IBasePropDoor::FromRaw(CEntityInstance* p) { return p ? static_cast<CBasePropDoor*>(p)->ToInterface() : nullptr; }
inline IBasePropDoor* IBasePropDoor::FromOriginal(CBasePropDoor* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBASEPROPDOORIMPL_H
