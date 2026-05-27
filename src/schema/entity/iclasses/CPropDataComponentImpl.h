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

#ifndef _INCLUDE_CPROPDATACOMPONENTIMPL_H
#define _INCLUDE_CPROPDATACOMPONENTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IPropDataComponent.h"
#include "schema/entity/classes/CPropDataComponent.h"

class CPropDataComponentImpl : public virtual IPropDataComponent
{

protected:
    void* m_pReal;

public:
    explicit CPropDataComponentImpl(void* p) : m_pReal(p) {}

private:
    CPropDataComponent* Real() { return static_cast<CPropDataComponent*>(m_pReal); }

public:
    float& DmgModBullet() override { return Real()->m_flDmgModBullet(); }
    void DmgModBulletUpdated() override { Real()->m_flDmgModBullet.NetworkStateChanged(); }
    float& DmgModClub() override { return Real()->m_flDmgModClub(); }
    void DmgModClubUpdated() override { Real()->m_flDmgModClub.NetworkStateChanged(); }
    float& DmgModExplosive() override { return Real()->m_flDmgModExplosive(); }
    void DmgModExplosiveUpdated() override { Real()->m_flDmgModExplosive.NetworkStateChanged(); }
    float& DmgModFire() override { return Real()->m_flDmgModFire(); }
    void DmgModFireUpdated() override { Real()->m_flDmgModFire.NetworkStateChanged(); }
    CUtlSymbolLarge& PhysicsDamageTableName() override { return Real()->m_iszPhysicsDamageTableName(); }
    void PhysicsDamageTableNameUpdated() override { Real()->m_iszPhysicsDamageTableName.NetworkStateChanged(); }
    CUtlSymbolLarge& BasePropData() override { return Real()->m_iszBasePropData(); }
    void BasePropDataUpdated() override { Real()->m_iszBasePropData.NetworkStateChanged(); }
    int32_t& Interactions() override { return Real()->m_nInteractions(); }
    void InteractionsUpdated() override { Real()->m_nInteractions.NetworkStateChanged(); }
    bool& SpawnMotionDisabled() override { return Real()->m_bSpawnMotionDisabled(); }
    void SpawnMotionDisabledUpdated() override { Real()->m_bSpawnMotionDisabled.NetworkStateChanged(); }
    int32_t& DisableTakePhysicsDamageSpawnFlag() override { return Real()->m_nDisableTakePhysicsDamageSpawnFlag(); }
    void DisableTakePhysicsDamageSpawnFlagUpdated() override { Real()->m_nDisableTakePhysicsDamageSpawnFlag.NetworkStateChanged(); }
    int32_t& MotionDisabledSpawnFlag() override { return Real()->m_nMotionDisabledSpawnFlag(); }
    void MotionDisabledSpawnFlagUpdated() override { Real()->m_nMotionDisabledSpawnFlag.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPROPDATACOMPONENTIMPL_H
