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

#ifndef _INCLUDE_CDYNAMICNAVCONNECTIONSVOLUMEIMPL_H
#define _INCLUDE_CDYNAMICNAVCONNECTIONSVOLUMEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IDynamicNavConnectionsVolume.h"
#include "schema/entity/classes/CDynamicNavConnectionsVolume.h"
#include "CTriggerMultipleImpl.h"

class CDynamicNavConnectionsVolumeImpl : public CTriggerMultipleImpl, public IDynamicNavConnectionsVolume
{

public:
    explicit CDynamicNavConnectionsVolumeImpl(CDynamicNavConnectionsVolume* p) : CTriggerMultipleImpl(p) {}

private:
    CDynamicNavConnectionsVolume* Real() { return static_cast<CDynamicNavConnectionsVolume*>(m_pReal); }

public:
    CUtlSymbolLarge& ConnectionTarget() override { return Real()->m_iszConnectionTarget(); }
    void ConnectionTargetUpdated() override { Real()->m_iszConnectionTarget.NetworkStateChanged(); }
    CUtlVector<DynamicVolumeDef_t>& Connections() override { return Real()->m_vecConnections(); }
    void ConnectionsUpdated() override { Real()->m_vecConnections.NetworkStateChanged(); }
    CGlobalSymbol& TransitionType() override { return Real()->m_sTransitionType(); }
    void TransitionTypeUpdated() override { Real()->m_sTransitionType.NetworkStateChanged(); }
    bool& ConnectionsEnabled() override { return Real()->m_bConnectionsEnabled(); }
    void ConnectionsEnabledUpdated() override { Real()->m_bConnectionsEnabled.NetworkStateChanged(); }
    float& TargetAreaSearchRadius() override { return Real()->m_flTargetAreaSearchRadius(); }
    void TargetAreaSearchRadiusUpdated() override { Real()->m_flTargetAreaSearchRadius.NetworkStateChanged(); }
    float& UpdateDistance() override { return Real()->m_flUpdateDistance(); }
    void UpdateDistanceUpdated() override { Real()->m_flUpdateDistance.NetworkStateChanged(); }
    float& MaxConnectionDistance() override { return Real()->m_flMaxConnectionDistance(); }
    void MaxConnectionDistanceUpdated() override { Real()->m_flMaxConnectionDistance.NetworkStateChanged(); }
};

#endif // _INCLUDE_CDYNAMICNAVCONNECTIONSVOLUMEIMPL_H
