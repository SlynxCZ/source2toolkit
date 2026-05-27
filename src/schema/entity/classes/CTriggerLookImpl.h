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

#ifndef _INCLUDE_CTRIGGERLOOKIMPL_H
#define _INCLUDE_CTRIGGERLOOKIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ITriggerLook.h"
#include "schema/entity/classes/CTriggerLook.h"
#include "CTriggerOnceImpl.h"

class CTriggerLookImpl : public CTriggerOnceImpl, public ITriggerLook
{

public:
    explicit CTriggerLookImpl(CTriggerLook* p) : CTriggerOnceImpl(p) {}

private:
    CTriggerLook* Real() { return static_cast<CTriggerLook*>(m_pReal); }

public:
    CHandle<CBaseEntity>& LookTarget() override { return Real()->m_hLookTarget(); }
    void LookTargetUpdated() override { Real()->m_hLookTarget.NetworkStateChanged(); }
    float& FieldOfView() override { return Real()->m_flFieldOfView(); }
    void FieldOfViewUpdated() override { Real()->m_flFieldOfView.NetworkStateChanged(); }
    float& LookTime() override { return Real()->m_flLookTime(); }
    void LookTimeUpdated() override { Real()->m_flLookTime.NetworkStateChanged(); }
    float& LookTimeTotal() override { return Real()->m_flLookTimeTotal(); }
    void LookTimeTotalUpdated() override { Real()->m_flLookTimeTotal.NetworkStateChanged(); }
    float& LookTimeLast() override { return Real()->m_flLookTimeLast(); }
    void LookTimeLastUpdated() override { Real()->m_flLookTimeLast.NetworkStateChanged(); }
    float& TimeoutDuration() override { return Real()->m_flTimeoutDuration(); }
    void TimeoutDurationUpdated() override { Real()->m_flTimeoutDuration.NetworkStateChanged(); }
    bool& TimeoutFired() override { return Real()->m_bTimeoutFired(); }
    void TimeoutFiredUpdated() override { Real()->m_bTimeoutFired.NetworkStateChanged(); }
    bool& IsLooking() override { return Real()->m_bIsLooking(); }
    void IsLookingUpdated() override { Real()->m_bIsLooking.NetworkStateChanged(); }
    bool& B2DFOV() override { return Real()->m_b2DFOV(); }
    void B2DFOVUpdated() override { Real()->m_b2DFOV.NetworkStateChanged(); }
    bool& UseVelocity() override { return Real()->m_bUseVelocity(); }
    void UseVelocityUpdated() override { Real()->m_bUseVelocity.NetworkStateChanged(); }
    bool& TestOcclusion() override { return Real()->m_bTestOcclusion(); }
    void TestOcclusionUpdated() override { Real()->m_bTestOcclusion.NetworkStateChanged(); }
    bool& TestAllVisibleOcclusion() override { return Real()->m_bTestAllVisibleOcclusion(); }
    void TestAllVisibleOcclusionUpdated() override { Real()->m_bTestAllVisibleOcclusion.NetworkStateChanged(); }
    CEntityIOOutput& OnTimeout() override { return Real()->m_OnTimeout(); }
    void OnTimeoutUpdated() override { Real()->m_OnTimeout.NetworkStateChanged(); }
    CEntityIOOutput& OnStartLook() override { return Real()->m_OnStartLook(); }
    void OnStartLookUpdated() override { Real()->m_OnStartLook.NetworkStateChanged(); }
    CEntityIOOutput& OnEndLook() override { return Real()->m_OnEndLook(); }
    void OnEndLookUpdated() override { Real()->m_OnEndLook.NetworkStateChanged(); }
};

#endif // _INCLUDE_CTRIGGERLOOKIMPL_H
