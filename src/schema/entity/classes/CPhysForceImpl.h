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

#ifndef _INCLUDE_CPHYSFORCEIMPL_H
#define _INCLUDE_CPHYSFORCEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPhysForce.h"
#include "schema/entity/classes/CPhysForce.h"
#include "CPointEntityImpl.h"

class CPhysForceImpl : public CPointEntityImpl, public IPhysForce
{

public:
    explicit CPhysForceImpl(CPhysForce* p) : CPointEntityImpl(p) {}

private:
    CPhysForce* Real() { return static_cast<CPhysForce*>(m_pReal); }
    CPhysForce* Real() const { return static_cast<CPhysForce*>(m_pReal); }

public:
    CPhysForce* GetOriginal() const override { return Real(); }
    IPhysicsMotionController*& Controller() override { return Real()->m_pController(); }
    void ControllerUpdated() override { Real()->m_pController.NetworkStateChanged(); }
    CUtlSymbolLarge& NameAttach() override { return Real()->m_nameAttach(); }
    void NameAttachUpdated() override { Real()->m_nameAttach.NetworkStateChanged(); }
    float& Force() override { return Real()->m_force(); }
    void ForceUpdated() override { Real()->m_force.NetworkStateChanged(); }
    float& ForceTime() override { return Real()->m_forceTime(); }
    void ForceTimeUpdated() override { Real()->m_forceTime.NetworkStateChanged(); }
    CHandle<CBaseEntity>& AttachedObject() override { return Real()->m_attachedObject(); }
    void AttachedObjectUpdated() override { Real()->m_attachedObject.NetworkStateChanged(); }
    bool& WasRestored() override { return Real()->m_wasRestored(); }
    void WasRestoredUpdated() override { Real()->m_wasRestored.NetworkStateChanged(); }
    ::CConstantForceController& Integrator() override { return Real()->m_integrator(); }
    void IntegratorUpdated() override { Real()->m_integrator.NetworkStateChanged(); }
};

inline IPhysForce* CPhysForce::ToInterface() { return new CPhysForceImpl(this); }
inline IPhysForce* IPhysForce::FromOriginal(CPhysForce* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPHYSFORCEIMPL_H
