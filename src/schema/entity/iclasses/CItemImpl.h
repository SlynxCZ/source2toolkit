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

#ifndef _INCLUDE_CITEMIMPL_H
#define _INCLUDE_CITEMIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IItem.h"
#include "schema/entity/classes/CItem.h"
#include "CBaseAnimGraphImpl.h"

class CItemImpl : public CBaseAnimGraphImpl, public IItem
{

public:
    explicit CItemImpl(CItem* p) : CBaseAnimGraphImpl(p) {}

private:
    CItem* Real() { return static_cast<CItem*>(m_pReal); }

public:
    CEntityIOOutput& OnPlayerTouch() override { return Real()->m_OnPlayerTouch(); }
    void OnPlayerTouchUpdated() override { Real()->m_OnPlayerTouch.NetworkStateChanged(); }
    CEntityIOOutput& OnPlayerPickup() override { return Real()->m_OnPlayerPickup(); }
    void OnPlayerPickupUpdated() override { Real()->m_OnPlayerPickup.NetworkStateChanged(); }
    bool& ActivateWhenAtRest() override { return Real()->m_bActivateWhenAtRest(); }
    void ActivateWhenAtRestUpdated() override { Real()->m_bActivateWhenAtRest.NetworkStateChanged(); }
    CEntityIOOutput& OnCacheInteraction() override { return Real()->m_OnCacheInteraction(); }
    void OnCacheInteractionUpdated() override { Real()->m_OnCacheInteraction.NetworkStateChanged(); }
    CEntityIOOutput& OnGlovePulled() override { return Real()->m_OnGlovePulled(); }
    void OnGlovePulledUpdated() override { Real()->m_OnGlovePulled.NetworkStateChanged(); }
    Vector& OriginalSpawnOrigin() override { return Real()->m_vOriginalSpawnOrigin(); }
    void OriginalSpawnOriginUpdated() override { Real()->m_vOriginalSpawnOrigin.NetworkStateChanged(); }
    QAngle& OriginalSpawnAngles() override { return Real()->m_vOriginalSpawnAngles(); }
    void OriginalSpawnAnglesUpdated() override { Real()->m_vOriginalSpawnAngles.NetworkStateChanged(); }
    bool& PhysStartAsleep() override { return Real()->m_bPhysStartAsleep(); }
    void PhysStartAsleepUpdated() override { Real()->m_bPhysStartAsleep.NetworkStateChanged(); }
};

#endif // _INCLUDE_CITEMIMPL_H
