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

#ifndef _INCLUDE_CCSPLAYER_WATERSERVICESIMPL_H
#define _INCLUDE_CCSPLAYER_WATERSERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/ICSPlayer_WaterServices.h"
#include "schema/entity/classes/CCSPlayer_WaterServices.h"
#include "CPlayer_WaterServicesImpl.h"

class CCSPlayer_WaterServicesImpl : public CPlayer_WaterServicesImpl, public ICSPlayer_WaterServices
{

public:
    explicit CCSPlayer_WaterServicesImpl(CCSPlayer_WaterServices* p) : CPlayer_WaterServicesImpl(p) {}

private:
    CCSPlayer_WaterServices* Real() { return static_cast<CCSPlayer_WaterServices*>(m_pReal); }

public:
    float& NextDrownDamageTime() override { return Real()->m_NextDrownDamageTime(); }
    void NextDrownDamageTimeUpdated() override { Real()->m_NextDrownDamageTime.NetworkStateChanged(); }
    int32_t& DrownDmgRate() override { return Real()->m_nDrownDmgRate(); }
    void DrownDmgRateUpdated() override { Real()->m_nDrownDmgRate.NetworkStateChanged(); }
    float& AirFinishedTime() override { return Real()->m_AirFinishedTime(); }
    void AirFinishedTimeUpdated() override { Real()->m_AirFinishedTime.NetworkStateChanged(); }
    float& WaterJumpTime() override { return Real()->m_flWaterJumpTime(); }
    void WaterJumpTimeUpdated() override { Real()->m_flWaterJumpTime.NetworkStateChanged(); }
    Vector& WaterJumpVel() override { return Real()->m_vecWaterJumpVel(); }
    void WaterJumpVelUpdated() override { Real()->m_vecWaterJumpVel.NetworkStateChanged(); }
    float& SwimSoundTime() override { return Real()->m_flSwimSoundTime(); }
    void SwimSoundTimeUpdated() override { Real()->m_flSwimSoundTime.NetworkStateChanged(); }
};

#endif // _INCLUDE_CCSPLAYER_WATERSERVICESIMPL_H
