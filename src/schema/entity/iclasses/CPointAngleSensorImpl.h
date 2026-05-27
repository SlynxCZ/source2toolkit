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

#ifndef _INCLUDE_CPOINTANGLESENSORIMPL_H
#define _INCLUDE_CPOINTANGLESENSORIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IPointAngleSensor.h"
#include "schema/entity/classes/CPointAngleSensor.h"
#include "CPointEntityImpl.h"

class CPointAngleSensorImpl : public CPointEntityImpl, public IPointAngleSensor
{

public:
    explicit CPointAngleSensorImpl(CPointAngleSensor* p) : CPointEntityImpl(p) {}

private:
    CPointAngleSensor* Real() { return static_cast<CPointAngleSensor*>(m_pReal); }

public:
    bool& Disabled() override { return Real()->m_bDisabled(); }
    void DisabledUpdated() override { Real()->m_bDisabled.NetworkStateChanged(); }
    CUtlSymbolLarge& LookAtName() override { return Real()->m_nLookAtName(); }
    void LookAtNameUpdated() override { Real()->m_nLookAtName.NetworkStateChanged(); }
    CHandle<CBaseEntity>& TargetEntity() override { return Real()->m_hTargetEntity(); }
    void TargetEntityUpdated() override { Real()->m_hTargetEntity.NetworkStateChanged(); }
    CHandle<CBaseEntity>& LookAtEntity() override { return Real()->m_hLookAtEntity(); }
    void LookAtEntityUpdated() override { Real()->m_hLookAtEntity.NetworkStateChanged(); }
    float& Duration() override { return Real()->m_flDuration(); }
    void DurationUpdated() override { Real()->m_flDuration.NetworkStateChanged(); }
    float& DotTolerance() override { return Real()->m_flDotTolerance(); }
    void DotToleranceUpdated() override { Real()->m_flDotTolerance.NetworkStateChanged(); }
    float& FacingTime() override { return Real()->m_flFacingTime(); }
    void FacingTimeUpdated() override { Real()->m_flFacingTime.NetworkStateChanged(); }
    bool& Fired() override { return Real()->m_bFired(); }
    void FiredUpdated() override { Real()->m_bFired.NetworkStateChanged(); }
    CEntityIOOutput& OnFacingLookat() override { return Real()->m_OnFacingLookat(); }
    void OnFacingLookatUpdated() override { Real()->m_OnFacingLookat.NetworkStateChanged(); }
    CEntityIOOutput& OnNotFacingLookat() override { return Real()->m_OnNotFacingLookat(); }
    void OnNotFacingLookatUpdated() override { Real()->m_OnNotFacingLookat.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPOINTANGLESENSORIMPL_H
