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

#ifndef _INCLUDE_CPHYSMAGNETIMPL_H
#define _INCLUDE_CPHYSMAGNETIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPhysMagnet.h"
#include "schema/entity/classes/CPhysMagnet.h"
#include "CBaseAnimGraphImpl.h"

class CPhysMagnetImpl : public CBaseAnimGraphImpl, public IPhysMagnet
{

public:
    explicit CPhysMagnetImpl(CPhysMagnet* p) : CBaseAnimGraphImpl(p) {}

private:
    CPhysMagnet* Real() { return static_cast<CPhysMagnet*>(m_pReal); }
    CPhysMagnet* Real() const { return static_cast<CPhysMagnet*>(m_pReal); }

public:
    CPhysMagnet* GetOriginal() const override { return Real(); }
    CEntityIOOutput& OnMagnetAttach() override { return Real()->m_OnMagnetAttach(); }
    void OnMagnetAttachUpdated() override { Real()->m_OnMagnetAttach.NetworkStateChanged(); }
    CEntityIOOutput& OnMagnetDetach() override { return Real()->m_OnMagnetDetach(); }
    void OnMagnetDetachUpdated() override { Real()->m_OnMagnetDetach.NetworkStateChanged(); }
    float& MassScale() override { return Real()->m_massScale(); }
    void MassScaleUpdated() override { Real()->m_massScale.NetworkStateChanged(); }
    float& ForceLimit() override { return Real()->m_forceLimit(); }
    void ForceLimitUpdated() override { Real()->m_forceLimit.NetworkStateChanged(); }
    float& TorqueLimit() override { return Real()->m_torqueLimit(); }
    void TorqueLimitUpdated() override { Real()->m_torqueLimit.NetworkStateChanged(); }
    CUtlVector<magnetted_objects_t>& MagnettedEntities() override { return Real()->m_MagnettedEntities(); }
    void MagnettedEntitiesUpdated() override { Real()->m_MagnettedEntities.NetworkStateChanged(); }
    bool& Active() override { return Real()->m_bActive(); }
    void ActiveUpdated() override { Real()->m_bActive.NetworkStateChanged(); }
    bool& HasHitSomething() override { return Real()->m_bHasHitSomething(); }
    void HasHitSomethingUpdated() override { Real()->m_bHasHitSomething.NetworkStateChanged(); }
    float& TotalMass() override { return Real()->m_flTotalMass(); }
    void TotalMassUpdated() override { Real()->m_flTotalMass.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_flRadius(); }
    void RadiusUpdated() override { Real()->m_flRadius.NetworkStateChanged(); }
    float& NextSuckTime() override { return Real()->m_flNextSuckTime(); }
    void NextSuckTimeUpdated() override { Real()->m_flNextSuckTime.NetworkStateChanged(); }
    int32_t& MaxObjectsAttached() override { return Real()->m_iMaxObjectsAttached(); }
    void MaxObjectsAttachedUpdated() override { Real()->m_iMaxObjectsAttached.NetworkStateChanged(); }
};

inline IPhysMagnet* CPhysMagnet::ToInterface() { return new CPhysMagnetImpl(this); }
inline IPhysMagnet* IPhysMagnet::FromOriginal(CPhysMagnet* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPHYSMAGNETIMPL_H
