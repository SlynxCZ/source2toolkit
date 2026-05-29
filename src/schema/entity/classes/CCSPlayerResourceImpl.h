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

#ifndef _INCLUDE_CCSPLAYERRESOURCEIMPL_H
#define _INCLUDE_CCSPLAYERRESOURCEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayerResource.h"
#include "schema/entity/classes/CCSPlayerResource.h"
#include "CBaseEntityImpl.h"

class CCSPlayerResourceImpl : public CBaseEntityImpl, public ICSPlayerResource
{

public:
    explicit CCSPlayerResourceImpl(CCSPlayerResource* p) : CBaseEntityImpl(p) {}

private:
    CCSPlayerResource* Real() { return static_cast<CCSPlayerResource*>(m_pReal); }
    CCSPlayerResource* Real() const { return static_cast<CCSPlayerResource*>(m_pReal); }

public:
    CCSPlayerResource* GetOriginal() const override { return Real(); }
    bool* HostageAlive() override { return Real()->m_bHostageAlive(); }
    bool* IsHostageFollowingSomeone() override { return Real()->m_isHostageFollowingSomeone(); }
    CEntityIndex* HostageEntityIDs() override { return Real()->m_iHostageEntityIDs(); }
    Vector& BombsiteCenterA() override { return Real()->m_bombsiteCenterA(); }
    void BombsiteCenterAUpdated() override { Real()->m_bombsiteCenterA.NetworkStateChanged(); }
    Vector& BombsiteCenterB() override { return Real()->m_bombsiteCenterB(); }
    void BombsiteCenterBUpdated() override { Real()->m_bombsiteCenterB.NetworkStateChanged(); }
    int32_t* HostageRescueX() override { return Real()->m_hostageRescueX(); }
    int32_t* HostageRescueY() override { return Real()->m_hostageRescueY(); }
    int32_t* HostageRescueZ() override { return Real()->m_hostageRescueZ(); }
    bool& EndMatchNextMapAllVoted() override { return Real()->m_bEndMatchNextMapAllVoted(); }
    void EndMatchNextMapAllVotedUpdated() override { Real()->m_bEndMatchNextMapAllVoted.NetworkStateChanged(); }
    bool& FoundGoalPositions() override { return Real()->m_foundGoalPositions(); }
    void FoundGoalPositionsUpdated() override { Real()->m_foundGoalPositions.NetworkStateChanged(); }
};

inline ICSPlayerResource* CCSPlayerResource::ToInterface() { return new CCSPlayerResourceImpl(this); }
inline ICSPlayerResource* ICSPlayerResource::FromOriginal(CCSPlayerResource* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSPLAYERRESOURCEIMPL_H
