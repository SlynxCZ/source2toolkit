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

#ifndef _INCLUDE_CFUNCROTATORIMPL_H
#define _INCLUDE_CFUNCROTATORIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IFuncRotator.h"
#include "schema/entity/classes/CFuncRotator.h"
#include "CBaseModelEntityImpl.h"

class CFuncRotatorImpl : public CBaseModelEntityImpl, public IFuncRotator
{

public:
    explicit CFuncRotatorImpl(CFuncRotator* p) : CBaseModelEntityImpl(p) {}

private:
    CFuncRotator* Real() { return static_cast<CFuncRotator*>(m_pReal); }
    CFuncRotator* Real() const { return static_cast<CFuncRotator*>(m_pReal); }

public:
    CFuncRotator* GetOriginal() const override { return Real(); }
    CHandle<CBaseEntity>& RotatorTarget() override { return Real()->m_hRotatorTarget(); }
    void RotatorTargetUpdated() override { Real()->m_hRotatorTarget.NetworkStateChanged(); }
    bool& IsRotating() override { return Real()->m_bIsRotating(); }
    void IsRotatingUpdated() override { Real()->m_bIsRotating.NetworkStateChanged(); }
    bool& IsReversing() override { return Real()->m_bIsReversing(); }
    void IsReversingUpdated() override { Real()->m_bIsReversing.NetworkStateChanged(); }
    float& TimeToReachMaxSpeed() override { return Real()->m_flTimeToReachMaxSpeed(); }
    void TimeToReachMaxSpeedUpdated() override { Real()->m_flTimeToReachMaxSpeed.NetworkStateChanged(); }
    float& TimeToReachZeroSpeed() override { return Real()->m_flTimeToReachZeroSpeed(); }
    void TimeToReachZeroSpeedUpdated() override { Real()->m_flTimeToReachZeroSpeed.NetworkStateChanged(); }
    float& DistanceAlongArcTraveled() override { return Real()->m_flDistanceAlongArcTraveled(); }
    void DistanceAlongArcTraveledUpdated() override { Real()->m_flDistanceAlongArcTraveled.NetworkStateChanged(); }
    float& TimeToWaitOscillate() override { return Real()->m_flTimeToWaitOscillate(); }
    void TimeToWaitOscillateUpdated() override { Real()->m_flTimeToWaitOscillate.NetworkStateChanged(); }
    float& TimeRotationStart() override { return Real()->m_flTimeRotationStart(); }
    void TimeRotationStartUpdated() override { Real()->m_flTimeRotationStart.NetworkStateChanged(); }
    Quaternion& LSPrevChange() override { return Real()->m_qLSPrevChange(); }
    void LSPrevChangeUpdated() override { Real()->m_qLSPrevChange.NetworkStateChanged(); }
    Quaternion& WSPrev() override { return Real()->m_qWSPrev(); }
    void WSPrevUpdated() override { Real()->m_qWSPrev.NetworkStateChanged(); }
    Quaternion& WSInit() override { return Real()->m_qWSInit(); }
    void WSInitUpdated() override { Real()->m_qWSInit.NetworkStateChanged(); }
    Quaternion& LSInit() override { return Real()->m_qLSInit(); }
    void LSInitUpdated() override { Real()->m_qLSInit.NetworkStateChanged(); }
    Quaternion& LSOrientation() override { return Real()->m_qLSOrientation(); }
    void LSOrientationUpdated() override { Real()->m_qLSOrientation.NetworkStateChanged(); }
    ::CEntityIOOutput& OnRotationStarted() override { return Real()->m_OnRotationStarted(); }
    void OnRotationStartedUpdated() override { Real()->m_OnRotationStarted.NetworkStateChanged(); }
    ::CEntityIOOutput& OnRotationCompleted() override { return Real()->m_OnRotationCompleted(); }
    void OnRotationCompletedUpdated() override { Real()->m_OnRotationCompleted.NetworkStateChanged(); }
    ::CEntityIOOutput& OnOscillate() override { return Real()->m_OnOscillate(); }
    void OnOscillateUpdated() override { Real()->m_OnOscillate.NetworkStateChanged(); }
    ::CEntityIOOutput& OnOscillateStartArrive() override { return Real()->m_OnOscillateStartArrive(); }
    void OnOscillateStartArriveUpdated() override { Real()->m_OnOscillateStartArrive.NetworkStateChanged(); }
    ::CEntityIOOutput& OnOscillateStartDepart() override { return Real()->m_OnOscillateStartDepart(); }
    void OnOscillateStartDepartUpdated() override { Real()->m_OnOscillateStartDepart.NetworkStateChanged(); }
    ::CEntityIOOutput& OnOscillateEndArrive() override { return Real()->m_OnOscillateEndArrive(); }
    void OnOscillateEndArriveUpdated() override { Real()->m_OnOscillateEndArrive.NetworkStateChanged(); }
    ::CEntityIOOutput& OnOscillateEndDepart() override { return Real()->m_OnOscillateEndDepart(); }
    void OnOscillateEndDepartUpdated() override { Real()->m_OnOscillateEndDepart.NetworkStateChanged(); }
    bool& OscillateDepart() override { return Real()->m_bOscillateDepart(); }
    void OscillateDepartUpdated() override { Real()->m_bOscillateDepart.NetworkStateChanged(); }
    int32_t& OscillateCount() override { return Real()->m_nOscillateCount(); }
    void OscillateCountUpdated() override { Real()->m_nOscillateCount.NetworkStateChanged(); }
    ::CFuncRotator__Rotate_t& RotateType() override { return Real()->m_eRotateType(); }
    void RotateTypeUpdated() override { Real()->m_eRotateType.NetworkStateChanged(); }
    ::CFuncRotator__Rotate_t& PrevRotateType() override { return Real()->m_ePrevRotateType(); }
    void PrevRotateTypeUpdated() override { Real()->m_ePrevRotateType.NetworkStateChanged(); }
    bool& HasTargetOverride() override { return Real()->m_bHasTargetOverride(); }
    void HasTargetOverrideUpdated() override { Real()->m_bHasTargetOverride.NetworkStateChanged(); }
    Quaternion& OrientationOverride() override { return Real()->m_qOrientationOverride(); }
    void OrientationOverrideUpdated() override { Real()->m_qOrientationOverride.NetworkStateChanged(); }
    ::RotatorTargetSpace_t& SpaceOverride() override { return Real()->m_eSpaceOverride(); }
    void SpaceOverrideUpdated() override { Real()->m_eSpaceOverride.NetworkStateChanged(); }
    QAngle& AngularVelocity() override { return Real()->m_qAngularVelocity(); }
    void AngularVelocityUpdated() override { Real()->m_qAngularVelocity.NetworkStateChanged(); }
    Vector& LookAtForcedUp() override { return Real()->m_vLookAtForcedUp(); }
    void LookAtForcedUpUpdated() override { Real()->m_vLookAtForcedUp.NetworkStateChanged(); }
    CUtlSymbolLarge& StrRotatorTarget() override { return Real()->m_strRotatorTarget(); }
    void StrRotatorTargetUpdated() override { Real()->m_strRotatorTarget.NetworkStateChanged(); }
    bool& RecordHistory() override { return Real()->m_bRecordHistory(); }
    void RecordHistoryUpdated() override { Real()->m_bRecordHistory.NetworkStateChanged(); }
    CUtlVector<RotatorHistoryEntry_t>& RotatorHistory() override { return Real()->m_vecRotatorHistory(); }
    void RotatorHistoryUpdated() override { Real()->m_vecRotatorHistory.NetworkStateChanged(); }
    bool& ReturningToPreviousOrientation() override { return Real()->m_bReturningToPreviousOrientation(); }
    void ReturningToPreviousOrientationUpdated() override { Real()->m_bReturningToPreviousOrientation.NetworkStateChanged(); }
    CUtlVector<RotatorQueueEntry_t>& RotatorQueue() override { return Real()->m_vecRotatorQueue(); }
    void RotatorQueueUpdated() override { Real()->m_vecRotatorQueue.NetworkStateChanged(); }
    CUtlVector<RotatorHistoryEntry_t>& RotatorQueueHistory() override { return Real()->m_vecRotatorQueueHistory(); }
    void RotatorQueueHistoryUpdated() override { Real()->m_vecRotatorQueueHistory.NetworkStateChanged(); }
    ::SolidType_t& SolidType() override { return Real()->m_eSolidType(); }
    void SolidTypeUpdated() override { Real()->m_eSolidType.NetworkStateChanged(); }
    CHandle<CFuncMover>& SpeedFromMover() override { return Real()->m_hSpeedFromMover(); }
    void SpeedFromMoverUpdated() override { Real()->m_hSpeedFromMover.NetworkStateChanged(); }
    CUtlSymbolLarge& SpeedFromMover() override { return Real()->m_iszSpeedFromMover(); }
    void SpeedFromMoverUpdated() override { Real()->m_iszSpeedFromMover.NetworkStateChanged(); }
    float& SpeedScale() override { return Real()->m_flSpeedScale(); }
    void SpeedScaleUpdated() override { Real()->m_flSpeedScale.NetworkStateChanged(); }
    float& MinYawRotation() override { return Real()->m_flMinYawRotation(); }
    void MinYawRotationUpdated() override { Real()->m_flMinYawRotation.NetworkStateChanged(); }
    float& MaxYawRotation() override { return Real()->m_flMaxYawRotation(); }
    void MaxYawRotationUpdated() override { Real()->m_flMaxYawRotation.NetworkStateChanged(); }
};

inline IFuncRotator* CFuncRotator::ToInterface() { return new CFuncRotatorImpl(this); }
inline IFuncRotator* IFuncRotator::FromOriginal(CFuncRotator* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CFUNCROTATORIMPL_H
