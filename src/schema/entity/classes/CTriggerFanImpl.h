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

#ifndef _INCLUDE_CTRIGGERFANIMPL_H
#define _INCLUDE_CTRIGGERFANIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ITriggerFan.h"
#include "schema/entity/classes/CTriggerFan.h"
#include "CBaseTriggerImpl.h"

class CTriggerFanImpl : public CBaseTriggerImpl, public virtual ITriggerFan
{

public:
    explicit CTriggerFanImpl(CTriggerFan* p) : CBaseTriggerImpl(p) {}

private:
    CTriggerFan* Real() { return static_cast<CTriggerFan*>(m_pReal); }
    CTriggerFan* Real() const { return static_cast<CTriggerFan*>(m_pReal); }

public:
    CTriggerFan* GetOriginal() const override { return Real(); }
    Vector& FanOriginOffset() override { return Real()->m_vFanOriginOffset(); }
    void FanOriginOffsetUpdated() override { Real()->m_vFanOriginOffset.NetworkStateChanged(); }
    Vector& Direction() override { return Real()->m_vDirection(); }
    void DirectionUpdated() override { Real()->m_vDirection.NetworkStateChanged(); }
    bool& PushTowardsInfoTarget() override { return Real()->m_bPushTowardsInfoTarget(); }
    void PushTowardsInfoTargetUpdated() override { Real()->m_bPushTowardsInfoTarget.NetworkStateChanged(); }
    bool& PushAwayFromInfoTarget() override { return Real()->m_bPushAwayFromInfoTarget(); }
    void PushAwayFromInfoTargetUpdated() override { Real()->m_bPushAwayFromInfoTarget.NetworkStateChanged(); }
    Quaternion& NoiseDelta() override { return Real()->m_qNoiseDelta(); }
    void NoiseDeltaUpdated() override { Real()->m_qNoiseDelta.NetworkStateChanged(); }
    CHandle<CInfoFan>& InfoFan() override { return Real()->m_hInfoFan(); }
    void InfoFanUpdated() override { Real()->m_hInfoFan.NetworkStateChanged(); }
    float& Force() override { return Real()->m_flForce(); }
    void ForceUpdated() override { Real()->m_flForce.NetworkStateChanged(); }
    bool& Falloff() override { return Real()->m_bFalloff(); }
    void FalloffUpdated() override { Real()->m_bFalloff.NetworkStateChanged(); }
    ::CountdownTimer& RampTimer() override { return Real()->m_RampTimer(); }
    void RampTimerUpdated() override { Real()->m_RampTimer.NetworkStateChanged(); }
    Vector& FanOriginWS() override { return Real()->m_vFanOriginWS(); }
    void FanOriginWSUpdated() override { Real()->m_vFanOriginWS.NetworkStateChanged(); }
    Vector& FanOriginLS() override { return Real()->m_vFanOriginLS(); }
    void FanOriginLSUpdated() override { Real()->m_vFanOriginLS.NetworkStateChanged(); }
    Vector& FanEndLS() override { return Real()->m_vFanEndLS(); }
    void FanEndLSUpdated() override { Real()->m_vFanEndLS.NetworkStateChanged(); }
    Vector& NoiseDirectionTarget() override { return Real()->m_vNoiseDirectionTarget(); }
    void NoiseDirectionTargetUpdated() override { Real()->m_vNoiseDirectionTarget.NetworkStateChanged(); }
    float& RopeForceScale() override { return Real()->m_flRopeForceScale(); }
    void RopeForceScaleUpdated() override { Real()->m_flRopeForceScale.NetworkStateChanged(); }
    float& ParticleForceScale() override { return Real()->m_flParticleForceScale(); }
    void ParticleForceScaleUpdated() override { Real()->m_flParticleForceScale.NetworkStateChanged(); }
    float& PlayerForce() override { return Real()->m_flPlayerForce(); }
    void PlayerForceUpdated() override { Real()->m_flPlayerForce.NetworkStateChanged(); }
    bool& PlayerWindblock() override { return Real()->m_bPlayerWindblock(); }
    void PlayerWindblockUpdated() override { Real()->m_bPlayerWindblock.NetworkStateChanged(); }
    float& NPCForce() override { return Real()->m_flNPCForce(); }
    void NPCForceUpdated() override { Real()->m_flNPCForce.NetworkStateChanged(); }
    float& RampTime() override { return Real()->m_flRampTime(); }
    void RampTimeUpdated() override { Real()->m_flRampTime.NetworkStateChanged(); }
    float& NoiseDegrees() override { return Real()->m_fNoiseDegrees(); }
    void NoiseDegreesUpdated() override { Real()->m_fNoiseDegrees.NetworkStateChanged(); }
    float& NoiseSpeed() override { return Real()->m_fNoiseSpeed(); }
    void NoiseSpeedUpdated() override { Real()->m_fNoiseSpeed.NetworkStateChanged(); }
    bool& PushPlayer() override { return Real()->m_bPushPlayer(); }
    void PushPlayerUpdated() override { Real()->m_bPushPlayer.NetworkStateChanged(); }
    bool& RampDown() override { return Real()->m_bRampDown(); }
    void RampDownUpdated() override { Real()->m_bRampDown.NetworkStateChanged(); }
    int32_t& ManagerFanIdx() override { return Real()->m_nManagerFanIdx(); }
    void ManagerFanIdxUpdated() override { Real()->m_nManagerFanIdx.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline ITriggerFan* CTriggerFan::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ITriggerFan*>(tagIt->second.ptr_for_return);
    auto* impl = new CTriggerFanImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ITriggerFan*>(impl));
    return impl;
}
inline ITriggerFan* ITriggerFan::FromRaw(CEntityInstance* p) { return p ? static_cast<CTriggerFan*>(p)->ToInterface() : nullptr; }
inline ITriggerFan* ITriggerFan::FromOriginal(CTriggerFan* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CTRIGGERFANIMPL_H
