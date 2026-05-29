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

#ifndef _INCLUDE_CENVSHAKEIMPL_H
#define _INCLUDE_CENVSHAKEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvShake.h"
#include "schema/entity/classes/CEnvShake.h"
#include "CPointEntityImpl.h"

class CEnvShakeImpl : public CPointEntityImpl, public IEnvShake
{

public:
    explicit CEnvShakeImpl(CEnvShake* p) : CPointEntityImpl(p) {}

private:
    CEnvShake* Real() { return static_cast<CEnvShake*>(m_pReal); }
    CEnvShake* Real() const { return static_cast<CEnvShake*>(m_pReal); }

public:
    CEnvShake* GetOriginal() const override { return Real(); }
    CUtlSymbolLarge& LimitToEntity() override { return Real()->m_limitToEntity(); }
    void LimitToEntityUpdated() override { Real()->m_limitToEntity.NetworkStateChanged(); }
    float& Amplitude() override { return Real()->m_Amplitude(); }
    void AmplitudeUpdated() override { Real()->m_Amplitude.NetworkStateChanged(); }
    float& Frequency() override { return Real()->m_Frequency(); }
    void FrequencyUpdated() override { Real()->m_Frequency.NetworkStateChanged(); }
    float& Duration() override { return Real()->m_Duration(); }
    void DurationUpdated() override { Real()->m_Duration.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_Radius(); }
    void RadiusUpdated() override { Real()->m_Radius.NetworkStateChanged(); }
    float& StopTime() override { return Real()->m_stopTime(); }
    void StopTimeUpdated() override { Real()->m_stopTime.NetworkStateChanged(); }
    float& NextShake() override { return Real()->m_nextShake(); }
    void NextShakeUpdated() override { Real()->m_nextShake.NetworkStateChanged(); }
    float& CurrentAmp() override { return Real()->m_currentAmp(); }
    void CurrentAmpUpdated() override { Real()->m_currentAmp.NetworkStateChanged(); }
    Vector& MaxForce() override { return Real()->m_maxForce(); }
    void MaxForceUpdated() override { Real()->m_maxForce.NetworkStateChanged(); }
    IPhysicsMotionController*& ShakeController() override { return Real()->m_pShakeController(); }
    void ShakeControllerUpdated() override { Real()->m_pShakeController.NetworkStateChanged(); }
    CPhysicsShake& ShakeCallback() override { return Real()->m_shakeCallback(); }
    void ShakeCallbackUpdated() override { Real()->m_shakeCallback.NetworkStateChanged(); }
};

inline IEnvShake* CEnvShake::ToInterface() { return new CEnvShakeImpl(this); }
inline IEnvShake* IEnvShake::FromOriginal(CEnvShake* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CENVSHAKEIMPL_H
