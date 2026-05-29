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

#ifndef _INCLUDE_CPLAYER_MOVEMENTSERVICES_HUMANOIDIMPL_H
#define _INCLUDE_CPLAYER_MOVEMENTSERVICES_HUMANOIDIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPlayer_MovementServices_Humanoid.h"
#include "schema/entity/classes/CPlayer_MovementServices_Humanoid.h"
#include "CPlayer_MovementServicesImpl.h"

class CPlayer_MovementServices_HumanoidImpl : public CPlayer_MovementServicesImpl, public virtual IPlayer_MovementServices_Humanoid
{

public:
    explicit CPlayer_MovementServices_HumanoidImpl(CPlayer_MovementServices_Humanoid* p) : CPlayer_MovementServicesImpl(p) {}

private:
    CPlayer_MovementServices_Humanoid* Real() { return static_cast<CPlayer_MovementServices_Humanoid*>(m_pReal); }
    CPlayer_MovementServices_Humanoid* Real() const { return static_cast<CPlayer_MovementServices_Humanoid*>(m_pReal); }

public:
    CPlayer_MovementServices_Humanoid* GetOriginal() const override { return Real(); }
    float& StepSoundTime() override { return Real()->m_flStepSoundTime(); }
    void StepSoundTimeUpdated() override { Real()->m_flStepSoundTime.NetworkStateChanged(); }
    float& FallVelocity() override { return Real()->m_flFallVelocity(); }
    void FallVelocityUpdated() override { Real()->m_flFallVelocity.NetworkStateChanged(); }
    Vector& GroundNormal() override { return Real()->m_groundNormal(); }
    void GroundNormalUpdated() override { Real()->m_groundNormal.NetworkStateChanged(); }
    float& SurfaceFriction() override { return Real()->m_flSurfaceFriction(); }
    void SurfaceFrictionUpdated() override { Real()->m_flSurfaceFriction.NetworkStateChanged(); }
    CUtlStringToken* SurfaceProps() override { return Real()->m_surfaceProps(); }
    int32_t& Stepside() override { return Real()->m_nStepside(); }
    void StepsideUpdated() override { Real()->m_nStepside.NetworkStateChanged(); }
    Vector& SmoothedVelocity() override { return Real()->m_vecSmoothedVelocity(); }
    void SmoothedVelocityUpdated() override { Real()->m_vecSmoothedVelocity.NetworkStateChanged(); }
};

inline IPlayer_MovementServices_Humanoid* CPlayer_MovementServices_Humanoid::ToInterface() { return new CPlayer_MovementServices_HumanoidImpl(this); }
inline IPlayer_MovementServices_Humanoid* IPlayer_MovementServices_Humanoid::FromRaw(CEntityInstance*) { return nullptr; }
inline IPlayer_MovementServices_Humanoid* IPlayer_MovementServices_Humanoid::FromOriginal(CPlayer_MovementServices_Humanoid* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPLAYER_MOVEMENTSERVICES_HUMANOIDIMPL_H
