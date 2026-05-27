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

#ifndef _INCLUDE_CPHYSICSPROPRESPAWNABLEIMPL_H
#define _INCLUDE_CPHYSICSPROPRESPAWNABLEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPhysicsPropRespawnable.h"
#include "schema/entity/classes/CPhysicsPropRespawnable.h"
#include "CPhysicsPropImpl.h"

class CPhysicsPropRespawnableImpl : public CPhysicsPropImpl, public IPhysicsPropRespawnable
{

public:
    explicit CPhysicsPropRespawnableImpl(CPhysicsPropRespawnable* p) : CPhysicsPropImpl(p) {}

private:
    CPhysicsPropRespawnable* Real() { return static_cast<CPhysicsPropRespawnable*>(m_pReal); }

public:
    Vector& OriginalSpawnOrigin() override { return Real()->m_vOriginalSpawnOrigin(); }
    void OriginalSpawnOriginUpdated() override { Real()->m_vOriginalSpawnOrigin.NetworkStateChanged(); }
    QAngle& OriginalSpawnAngles() override { return Real()->m_vOriginalSpawnAngles(); }
    void OriginalSpawnAnglesUpdated() override { Real()->m_vOriginalSpawnAngles.NetworkStateChanged(); }
    Vector& OriginalMins() override { return Real()->m_vOriginalMins(); }
    void OriginalMinsUpdated() override { Real()->m_vOriginalMins.NetworkStateChanged(); }
    Vector& OriginalMaxs() override { return Real()->m_vOriginalMaxs(); }
    void OriginalMaxsUpdated() override { Real()->m_vOriginalMaxs.NetworkStateChanged(); }
    float& RespawnDuration() override { return Real()->m_flRespawnDuration(); }
    void RespawnDurationUpdated() override { Real()->m_flRespawnDuration.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPHYSICSPROPRESPAWNABLEIMPL_H
