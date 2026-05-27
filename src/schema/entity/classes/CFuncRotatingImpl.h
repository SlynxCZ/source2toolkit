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

#ifndef _INCLUDE_CFUNCROTATINGIMPL_H
#define _INCLUDE_CFUNCROTATINGIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IFuncRotating.h"
#include "schema/entity/classes/CFuncRotating.h"
#include "CBaseModelEntityImpl.h"

class CFuncRotatingImpl : public CBaseModelEntityImpl, public IFuncRotating
{

public:
    explicit CFuncRotatingImpl(CFuncRotating* p) : CBaseModelEntityImpl(p) {}

private:
    CFuncRotating* Real() { return static_cast<CFuncRotating*>(m_pReal); }

public:
    CEntityIOOutput& OnStopped() override { return Real()->m_OnStopped(); }
    void OnStoppedUpdated() override { Real()->m_OnStopped.NetworkStateChanged(); }
    CEntityIOOutput& OnStarted() override { return Real()->m_OnStarted(); }
    void OnStartedUpdated() override { Real()->m_OnStarted.NetworkStateChanged(); }
    CEntityIOOutput& OnReachedStart() override { return Real()->m_OnReachedStart(); }
    void OnReachedStartUpdated() override { Real()->m_OnReachedStart.NetworkStateChanged(); }
    RotationVector& LocalRotationVector() override { return Real()->m_localRotationVector(); }
    void LocalRotationVectorUpdated() override { Real()->m_localRotationVector.NetworkStateChanged(); }
    float& FanFriction() override { return Real()->m_flFanFriction(); }
    void FanFrictionUpdated() override { Real()->m_flFanFriction.NetworkStateChanged(); }
    float& Attenuation() override { return Real()->m_flAttenuation(); }
    void AttenuationUpdated() override { Real()->m_flAttenuation.NetworkStateChanged(); }
    float& Volume() override { return Real()->m_flVolume(); }
    void VolumeUpdated() override { Real()->m_flVolume.NetworkStateChanged(); }
    float& TargetSpeed() override { return Real()->m_flTargetSpeed(); }
    void TargetSpeedUpdated() override { Real()->m_flTargetSpeed.NetworkStateChanged(); }
    float& MaxSpeed() override { return Real()->m_flMaxSpeed(); }
    void MaxSpeedUpdated() override { Real()->m_flMaxSpeed.NetworkStateChanged(); }
    float& BlockDamage() override { return Real()->m_flBlockDamage(); }
    void BlockDamageUpdated() override { Real()->m_flBlockDamage.NetworkStateChanged(); }
    CUtlSymbolLarge& NoiseRunning() override { return Real()->m_NoiseRunning(); }
    void NoiseRunningUpdated() override { Real()->m_NoiseRunning.NetworkStateChanged(); }
    bool& Reversed() override { return Real()->m_bReversed(); }
    void ReversedUpdated() override { Real()->m_bReversed.NetworkStateChanged(); }
    bool& AccelDecel() override { return Real()->m_bAccelDecel(); }
    void AccelDecelUpdated() override { Real()->m_bAccelDecel.NetworkStateChanged(); }
    QAngle& PrevLocalAngles() override { return Real()->m_prevLocalAngles(); }
    void PrevLocalAnglesUpdated() override { Real()->m_prevLocalAngles.NetworkStateChanged(); }
    QAngle& Start() override { return Real()->m_angStart(); }
    void StartUpdated() override { Real()->m_angStart.NetworkStateChanged(); }
    bool& StopAtStartPos() override { return Real()->m_bStopAtStartPos(); }
    void StopAtStartPosUpdated() override { Real()->m_bStopAtStartPos.NetworkStateChanged(); }
    Vector& ClientOrigin() override { return Real()->m_vecClientOrigin(); }
    void ClientOriginUpdated() override { Real()->m_vecClientOrigin.NetworkStateChanged(); }
    QAngle& ClientAngles() override { return Real()->m_vecClientAngles(); }
    void ClientAnglesUpdated() override { Real()->m_vecClientAngles.NetworkStateChanged(); }
};

#endif // _INCLUDE_CFUNCROTATINGIMPL_H
