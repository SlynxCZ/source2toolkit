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

#ifndef _INCLUDE_CPHYSICSSPRINGIMPL_H
#define _INCLUDE_CPHYSICSSPRINGIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IPhysicsSpring.h"
#include "schema/entity/classes/CPhysicsSpring.h"
#include "CBaseEntityImpl.h"

class CPhysicsSpringImpl : public CBaseEntityImpl, public IPhysicsSpring
{

public:
    explicit CPhysicsSpringImpl(CPhysicsSpring* p) : CBaseEntityImpl(p) {}

private:
    CPhysicsSpring* Real() { return static_cast<CPhysicsSpring*>(m_pReal); }

public:
    IPhysicsJoint*& SpringJoint() override { return Real()->m_pSpringJoint(); }
    void SpringJointUpdated() override { Real()->m_pSpringJoint.NetworkStateChanged(); }
    float& Frequency() override { return Real()->m_flFrequency(); }
    void FrequencyUpdated() override { Real()->m_flFrequency.NetworkStateChanged(); }
    float& DampingRatio() override { return Real()->m_flDampingRatio(); }
    void DampingRatioUpdated() override { Real()->m_flDampingRatio.NetworkStateChanged(); }
    float& RestLength() override { return Real()->m_flRestLength(); }
    void RestLengthUpdated() override { Real()->m_flRestLength.NetworkStateChanged(); }
    CUtlSymbolLarge& NameAttachStart() override { return Real()->m_nameAttachStart(); }
    void NameAttachStartUpdated() override { Real()->m_nameAttachStart.NetworkStateChanged(); }
    CUtlSymbolLarge& NameAttachEnd() override { return Real()->m_nameAttachEnd(); }
    void NameAttachEndUpdated() override { Real()->m_nameAttachEnd.NetworkStateChanged(); }
    Vector& Start() override { return Real()->m_start(); }
    void StartUpdated() override { Real()->m_start.NetworkStateChanged(); }
    Vector& End() override { return Real()->m_end(); }
    void EndUpdated() override { Real()->m_end.NetworkStateChanged(); }
    uint32_t& TeleportTick() override { return Real()->m_teleportTick(); }
    void TeleportTickUpdated() override { Real()->m_teleportTick.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPHYSICSSPRINGIMPL_H
