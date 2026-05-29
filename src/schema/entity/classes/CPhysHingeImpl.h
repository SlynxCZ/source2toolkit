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

#ifndef _INCLUDE_CPHYSHINGEIMPL_H
#define _INCLUDE_CPHYSHINGEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPhysHinge.h"
#include "schema/entity/classes/CPhysHinge.h"
#include "CPhysConstraintImpl.h"

class CPhysHingeImpl : public CPhysConstraintImpl, public virtual IPhysHinge
{

public:
    explicit CPhysHingeImpl(CPhysHinge* p) : CPhysConstraintImpl(p) {}

private:
    CPhysHinge* Real() { return static_cast<CPhysHinge*>(m_pReal); }
    CPhysHinge* Real() const { return static_cast<CPhysHinge*>(m_pReal); }

public:
    CPhysHinge* GetOriginal() const override { return Real(); }
    ::ConstraintSoundInfo& SoundInfo() override { return Real()->m_soundInfo(); }
    void SoundInfoUpdated() override { Real()->m_soundInfo.NetworkStateChanged(); }
    ::CEntityIOOutput& NotifyMinLimitReached() override { return Real()->m_NotifyMinLimitReached(); }
    void NotifyMinLimitReachedUpdated() override { Real()->m_NotifyMinLimitReached.NetworkStateChanged(); }
    ::CEntityIOOutput& NotifyMaxLimitReached() override { return Real()->m_NotifyMaxLimitReached(); }
    void NotifyMaxLimitReachedUpdated() override { Real()->m_NotifyMaxLimitReached.NetworkStateChanged(); }
    bool& AtMinLimit() override { return Real()->m_bAtMinLimit(); }
    void AtMinLimitUpdated() override { Real()->m_bAtMinLimit.NetworkStateChanged(); }
    bool& AtMaxLimit() override { return Real()->m_bAtMaxLimit(); }
    void AtMaxLimitUpdated() override { Real()->m_bAtMaxLimit.NetworkStateChanged(); }
    ::constraint_hingeparams_t& Hinge() override { return Real()->m_hinge(); }
    void HingeUpdated() override { Real()->m_hinge.NetworkStateChanged(); }
    float& HingeFriction() override { return Real()->m_hingeFriction(); }
    void HingeFrictionUpdated() override { Real()->m_hingeFriction.NetworkStateChanged(); }
    float& SystemLoadScale() override { return Real()->m_systemLoadScale(); }
    void SystemLoadScaleUpdated() override { Real()->m_systemLoadScale.NetworkStateChanged(); }
    bool& IsAxisLocal() override { return Real()->m_bIsAxisLocal(); }
    void IsAxisLocalUpdated() override { Real()->m_bIsAxisLocal.NetworkStateChanged(); }
    float& MinRotation() override { return Real()->m_flMinRotation(); }
    void MinRotationUpdated() override { Real()->m_flMinRotation.NetworkStateChanged(); }
    float& MaxRotation() override { return Real()->m_flMaxRotation(); }
    void MaxRotationUpdated() override { Real()->m_flMaxRotation.NetworkStateChanged(); }
    float& InitialRotation() override { return Real()->m_flInitialRotation(); }
    void InitialRotationUpdated() override { Real()->m_flInitialRotation.NetworkStateChanged(); }
    float& MotorFrequency() override { return Real()->m_flMotorFrequency(); }
    void MotorFrequencyUpdated() override { Real()->m_flMotorFrequency.NetworkStateChanged(); }
    float& MotorDampingRatio() override { return Real()->m_flMotorDampingRatio(); }
    void MotorDampingRatioUpdated() override { Real()->m_flMotorDampingRatio.NetworkStateChanged(); }
    float& AngleSpeed() override { return Real()->m_flAngleSpeed(); }
    void AngleSpeedUpdated() override { Real()->m_flAngleSpeed.NetworkStateChanged(); }
    float& AngleSpeedThreshold() override { return Real()->m_flAngleSpeedThreshold(); }
    void AngleSpeedThresholdUpdated() override { Real()->m_flAngleSpeedThreshold.NetworkStateChanged(); }
    float& LimitsDebugVisRotation() override { return Real()->m_flLimitsDebugVisRotation(); }
    void LimitsDebugVisRotationUpdated() override { Real()->m_flLimitsDebugVisRotation.NetworkStateChanged(); }
    ::CEntityIOOutput& OnStartMoving() override { return Real()->m_OnStartMoving(); }
    void OnStartMovingUpdated() override { Real()->m_OnStartMoving.NetworkStateChanged(); }
    ::CEntityIOOutput& OnStopMoving() override { return Real()->m_OnStopMoving(); }
    void OnStopMovingUpdated() override { Real()->m_OnStopMoving.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IPhysHinge* CPhysHinge::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPhysHinge*>(tagIt->second.ptr_for_return);
    auto* impl = new CPhysHingeImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPhysHinge*>(impl));
    return impl;
}
inline IPhysHinge* IPhysHinge::FromRaw(CEntityInstance* p) { return p ? static_cast<CPhysHinge*>(p)->ToInterface() : nullptr; }
inline IPhysHinge* IPhysHinge::FromOriginal(CPhysHinge* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPHYSHINGEIMPL_H
