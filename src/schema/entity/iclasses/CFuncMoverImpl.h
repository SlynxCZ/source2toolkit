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

#ifndef _INCLUDE_CFUNCMOVERIMPL_H
#define _INCLUDE_CFUNCMOVERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IFuncMover.h"
#include "schema/entity/classes/CFuncMover.h"
#include "CBaseModelEntityImpl.h"

class CFuncMoverImpl : public CBaseModelEntityImpl, public IFuncMover
{

public:
    explicit CFuncMoverImpl(CFuncMover* p) : CBaseModelEntityImpl(p) {}

private:
    CFuncMover* Real() { return static_cast<CFuncMover*>(m_pReal); }

public:
    CUtlSymbolLarge& PathName() override { return Real()->m_iszPathName(); }
    void PathNameUpdated() override { Real()->m_iszPathName.NetworkStateChanged(); }
    CHandle<CPathMover>& PathMover() override { return Real()->m_hPathMover(); }
    void PathMoverUpdated() override { Real()->m_hPathMover.NetworkStateChanged(); }
    CHandle<CPathMover>& PrevPathMover() override { return Real()->m_hPrevPathMover(); }
    void PrevPathMoverUpdated() override { Real()->m_hPrevPathMover.NetworkStateChanged(); }
    CUtlSymbolLarge& PathNodeStart() override { return Real()->m_iszPathNodeStart(); }
    void PathNodeStartUpdated() override { Real()->m_iszPathNodeStart.NetworkStateChanged(); }
    CUtlSymbolLarge& PathNodeEnd() override { return Real()->m_iszPathNodeEnd(); }
    void PathNodeEndUpdated() override { Real()->m_iszPathNodeEnd.NetworkStateChanged(); }
    bool& IgnoreEndNode() override { return Real()->m_bIgnoreEndNode(); }
    void IgnoreEndNodeUpdated() override { Real()->m_bIgnoreEndNode.NetworkStateChanged(); }
    CFuncMover__Move_t& MoveType() override { return Real()->m_eMoveType(); }
    void MoveTypeUpdated() override { Real()->m_eMoveType.NetworkStateChanged(); }
    bool& IsReversing() override { return Real()->m_bIsReversing(); }
    void IsReversingUpdated() override { Real()->m_bIsReversing.NetworkStateChanged(); }
    float& StartSpeed() override { return Real()->m_flStartSpeed(); }
    void StartSpeedUpdated() override { Real()->m_flStartSpeed.NetworkStateChanged(); }
    float& PathLocation() override { return Real()->m_flPathLocation(); }
    void PathLocationUpdated() override { Real()->m_flPathLocation.NetworkStateChanged(); }
    float& T() override { return Real()->m_flT(); }
    void TUpdated() override { Real()->m_flT.NetworkStateChanged(); }
    int32_t& CurrentNodeIndex() override { return Real()->m_nCurrentNodeIndex(); }
    void CurrentNodeIndexUpdated() override { Real()->m_nCurrentNodeIndex.NetworkStateChanged(); }
    int32_t& PreviousNodeIndex() override { return Real()->m_nPreviousNodeIndex(); }
    void PreviousNodeIndexUpdated() override { Real()->m_nPreviousNodeIndex.NetworkStateChanged(); }
    SolidType_t& SolidType() override { return Real()->m_eSolidType(); }
    void SolidTypeUpdated() override { Real()->m_eSolidType.NetworkStateChanged(); }
    bool& IsMoving() override { return Real()->m_bIsMoving(); }
    void IsMovingUpdated() override { Real()->m_bIsMoving.NetworkStateChanged(); }
    float& TimeToReachMaxSpeed() override { return Real()->m_flTimeToReachMaxSpeed(); }
    void TimeToReachMaxSpeedUpdated() override { Real()->m_flTimeToReachMaxSpeed.NetworkStateChanged(); }
    float& DistanceToReachMaxSpeed() override { return Real()->m_flDistanceToReachMaxSpeed(); }
    void DistanceToReachMaxSpeedUpdated() override { Real()->m_flDistanceToReachMaxSpeed.NetworkStateChanged(); }
    float& TimeToReachZeroSpeed() override { return Real()->m_flTimeToReachZeroSpeed(); }
    void TimeToReachZeroSpeedUpdated() override { Real()->m_flTimeToReachZeroSpeed.NetworkStateChanged(); }
    float& ComputedDistanceToReachMaxSpeed() override { return Real()->m_flComputedDistanceToReachMaxSpeed(); }
    void ComputedDistanceToReachMaxSpeedUpdated() override { Real()->m_flComputedDistanceToReachMaxSpeed.NetworkStateChanged(); }
    float& ComputedDistanceToReachZeroSpeed() override { return Real()->m_flComputedDistanceToReachZeroSpeed(); }
    void ComputedDistanceToReachZeroSpeedUpdated() override { Real()->m_flComputedDistanceToReachZeroSpeed.NetworkStateChanged(); }
    float& StartCurveScale() override { return Real()->m_flStartCurveScale(); }
    void StartCurveScaleUpdated() override { Real()->m_flStartCurveScale.NetworkStateChanged(); }
    float& StopCurveScale() override { return Real()->m_flStopCurveScale(); }
    void StopCurveScaleUpdated() override { Real()->m_flStopCurveScale.NetworkStateChanged(); }
    float& DistanceToReachZeroSpeed() override { return Real()->m_flDistanceToReachZeroSpeed(); }
    void DistanceToReachZeroSpeedUpdated() override { Real()->m_flDistanceToReachZeroSpeed.NetworkStateChanged(); }
    float& TimeMovementStart() override { return Real()->m_flTimeMovementStart(); }
    void TimeMovementStartUpdated() override { Real()->m_flTimeMovementStart.NetworkStateChanged(); }
    float& TimeMovementStop() override { return Real()->m_flTimeMovementStop(); }
    void TimeMovementStopUpdated() override { Real()->m_flTimeMovementStop.NetworkStateChanged(); }
    CHandle<CMoverPathNode>& StopAtNode() override { return Real()->m_hStopAtNode(); }
    void StopAtNodeUpdated() override { Real()->m_hStopAtNode.NetworkStateChanged(); }
    float& PathLocationToBeginStop() override { return Real()->m_flPathLocationToBeginStop(); }
    void PathLocationToBeginStopUpdated() override { Real()->m_flPathLocationToBeginStop.NetworkStateChanged(); }
    float& PathLocationStart() override { return Real()->m_flPathLocationStart(); }
    void PathLocationStartUpdated() override { Real()->m_flPathLocationStart.NetworkStateChanged(); }
    float& BeginStopT() override { return Real()->m_flBeginStopT(); }
    void BeginStopTUpdated() override { Real()->m_flBeginStopT.NetworkStateChanged(); }
    CUtlSymbolLarge& StartForwardSound() override { return Real()->m_iszStartForwardSound(); }
    void StartForwardSoundUpdated() override { Real()->m_iszStartForwardSound.NetworkStateChanged(); }
    CUtlSymbolLarge& LoopForwardSound() override { return Real()->m_iszLoopForwardSound(); }
    void LoopForwardSoundUpdated() override { Real()->m_iszLoopForwardSound.NetworkStateChanged(); }
    CUtlSymbolLarge& StopForwardSound() override { return Real()->m_iszStopForwardSound(); }
    void StopForwardSoundUpdated() override { Real()->m_iszStopForwardSound.NetworkStateChanged(); }
    CUtlSymbolLarge& StartReverseSound() override { return Real()->m_iszStartReverseSound(); }
    void StartReverseSoundUpdated() override { Real()->m_iszStartReverseSound.NetworkStateChanged(); }
    CUtlSymbolLarge& LoopReverseSound() override { return Real()->m_iszLoopReverseSound(); }
    void LoopReverseSoundUpdated() override { Real()->m_iszLoopReverseSound.NetworkStateChanged(); }
    CUtlSymbolLarge& StopReverseSound() override { return Real()->m_iszStopReverseSound(); }
    void StopReverseSoundUpdated() override { Real()->m_iszStopReverseSound.NetworkStateChanged(); }
    CUtlSymbolLarge& ArriveAtDestinationSound() override { return Real()->m_iszArriveAtDestinationSound(); }
    void ArriveAtDestinationSoundUpdated() override { Real()->m_iszArriveAtDestinationSound.NetworkStateChanged(); }
    CEntityIOOutput& OnMovementEnd() override { return Real()->m_OnMovementEnd(); }
    void OnMovementEndUpdated() override { Real()->m_OnMovementEnd.NetworkStateChanged(); }
    bool& StartAtClosestPoint() override { return Real()->m_bStartAtClosestPoint(); }
    void StartAtClosestPointUpdated() override { Real()->m_bStartAtClosestPoint.NetworkStateChanged(); }
    bool& StartAtEnd() override { return Real()->m_bStartAtEnd(); }
    void StartAtEndUpdated() override { Real()->m_bStartAtEnd.NetworkStateChanged(); }
    bool& StartFollowingClosestMover() override { return Real()->m_bStartFollowingClosestMover(); }
    void StartFollowingClosestMoverUpdated() override { Real()->m_bStartFollowingClosestMover.NetworkStateChanged(); }
    CFuncMover__OrientationUpdate_t& OrientationUpdate() override { return Real()->m_eOrientationUpdate(); }
    void OrientationUpdateUpdated() override { Real()->m_eOrientationUpdate.NetworkStateChanged(); }
    float& TimeStartOrientationChange() override { return Real()->m_flTimeStartOrientationChange(); }
    void TimeStartOrientationChangeUpdated() override { Real()->m_flTimeStartOrientationChange.NetworkStateChanged(); }
    float& TimeToBlendToNewOrientation() override { return Real()->m_flTimeToBlendToNewOrientation(); }
    void TimeToBlendToNewOrientationUpdated() override { Real()->m_flTimeToBlendToNewOrientation.NetworkStateChanged(); }
    float& DurationBlendToNewOrientationRan() override { return Real()->m_flDurationBlendToNewOrientationRan(); }
    void DurationBlendToNewOrientationRanUpdated() override { Real()->m_flDurationBlendToNewOrientationRan.NetworkStateChanged(); }
    bool& CreateMovableNavMesh() override { return Real()->m_bCreateMovableNavMesh(); }
    void CreateMovableNavMeshUpdated() override { Real()->m_bCreateMovableNavMesh.NetworkStateChanged(); }
    bool& AllowMovableNavMeshDockingOnEntireEntity() override { return Real()->m_bAllowMovableNavMeshDockingOnEntireEntity(); }
    void AllowMovableNavMeshDockingOnEntireEntityUpdated() override { Real()->m_bAllowMovableNavMeshDockingOnEntireEntity.NetworkStateChanged(); }
    CUtlSymbolLarge& OrientationMatchEntityName() override { return Real()->m_iszOrientationMatchEntityName(); }
    void OrientationMatchEntityNameUpdated() override { Real()->m_iszOrientationMatchEntityName.NetworkStateChanged(); }
    CHandle<CBaseEntity>& OrientationMatchEntity() override { return Real()->m_hOrientationMatchEntity(); }
    void OrientationMatchEntityUpdated() override { Real()->m_hOrientationMatchEntity.NetworkStateChanged(); }
    float& TimeToTraverseToNextNode() override { return Real()->m_flTimeToTraverseToNextNode(); }
    void TimeToTraverseToNextNodeUpdated() override { Real()->m_flTimeToTraverseToNextNode.NetworkStateChanged(); }
    Vector& LerpToNewPosStartInPathEntitySpace() override { return Real()->m_vLerpToNewPosStartInPathEntitySpace(); }
    void LerpToNewPosStartInPathEntitySpaceUpdated() override { Real()->m_vLerpToNewPosStartInPathEntitySpace.NetworkStateChanged(); }
    Vector& LerpToNewPosEndInPathEntitySpace() override { return Real()->m_vLerpToNewPosEndInPathEntitySpace(); }
    void LerpToNewPosEndInPathEntitySpaceUpdated() override { Real()->m_vLerpToNewPosEndInPathEntitySpace.NetworkStateChanged(); }
    float& LerpToPositionT() override { return Real()->m_flLerpToPositionT(); }
    void LerpToPositionTUpdated() override { Real()->m_flLerpToPositionT.NetworkStateChanged(); }
    float& LerpToPositionDeltaT() override { return Real()->m_flLerpToPositionDeltaT(); }
    void LerpToPositionDeltaTUpdated() override { Real()->m_flLerpToPositionDeltaT.NetworkStateChanged(); }
    CEntityIOOutput& OnLerpToPositionComplete() override { return Real()->m_OnLerpToPositionComplete(); }
    void OnLerpToPositionCompleteUpdated() override { Real()->m_OnLerpToPositionComplete.NetworkStateChanged(); }
    bool& IsPaused() override { return Real()->m_bIsPaused(); }
    void IsPausedUpdated() override { Real()->m_bIsPaused.NetworkStateChanged(); }
    CFuncMover__TransitionToPathNodeAction_t& TransitionedToPathNodeAction() override { return Real()->m_eTransitionedToPathNodeAction(); }
    void TransitionedToPathNodeActionUpdated() override { Real()->m_eTransitionedToPathNodeAction.NetworkStateChanged(); }
    Quaternion& TransitionSourceOrientation() override { return Real()->m_qTransitionSourceOrientation(); }
    void TransitionSourceOrientationUpdated() override { Real()->m_qTransitionSourceOrientation.NetworkStateChanged(); }
    int32_t& DelayedTeleportToNode() override { return Real()->m_nDelayedTeleportToNode(); }
    void DelayedTeleportToNodeUpdated() override { Real()->m_nDelayedTeleportToNode.NetworkStateChanged(); }
    bool& IsImGuiLogging() override { return Real()->m_bIsImGuiLogging(); }
    void IsImGuiLoggingUpdated() override { Real()->m_bIsImGuiLogging.NetworkStateChanged(); }
    CHandle<CBaseEntity>& FollowEntity() override { return Real()->m_hFollowEntity(); }
    void FollowEntityUpdated() override { Real()->m_hFollowEntity.NetworkStateChanged(); }
    float& FollowDistance() override { return Real()->m_flFollowDistance(); }
    void FollowDistanceUpdated() override { Real()->m_flFollowDistance.NetworkStateChanged(); }
    float& FollowMinimumSpeed() override { return Real()->m_flFollowMinimumSpeed(); }
    void FollowMinimumSpeedUpdated() override { Real()->m_flFollowMinimumSpeed.NetworkStateChanged(); }
    float& CurFollowEntityT() override { return Real()->m_flCurFollowEntityT(); }
    void CurFollowEntityTUpdated() override { Real()->m_flCurFollowEntityT.NetworkStateChanged(); }
    float& CurFollowSpeed() override { return Real()->m_flCurFollowSpeed(); }
    void CurFollowSpeedUpdated() override { Real()->m_flCurFollowSpeed.NetworkStateChanged(); }
    CUtlSymbolLarge& StrOrientationFaceEntityName() override { return Real()->m_strOrientationFaceEntityName(); }
    void StrOrientationFaceEntityNameUpdated() override { Real()->m_strOrientationFaceEntityName.NetworkStateChanged(); }
    CHandle<CBaseEntity>& OrientationFaceEntity() override { return Real()->m_hOrientationFaceEntity(); }
    void OrientationFaceEntityUpdated() override { Real()->m_hOrientationFaceEntity.NetworkStateChanged(); }
    CEntityIOOutput& OnStart() override { return Real()->m_OnStart(); }
    void OnStartUpdated() override { Real()->m_OnStart.NetworkStateChanged(); }
    CEntityIOOutput& OnStartForward() override { return Real()->m_OnStartForward(); }
    void OnStartForwardUpdated() override { Real()->m_OnStartForward.NetworkStateChanged(); }
    CEntityIOOutput& OnStartReverse() override { return Real()->m_OnStartReverse(); }
    void OnStartReverseUpdated() override { Real()->m_OnStartReverse.NetworkStateChanged(); }
    CEntityIOOutput& OnStop() override { return Real()->m_OnStop(); }
    void OnStopUpdated() override { Real()->m_OnStop.NetworkStateChanged(); }
    CEntityIOOutput& OnStopped() override { return Real()->m_OnStopped(); }
    void OnStoppedUpdated() override { Real()->m_OnStopped.NetworkStateChanged(); }
    bool& NextNodeReturnsCurrent() override { return Real()->m_bNextNodeReturnsCurrent(); }
    void NextNodeReturnsCurrentUpdated() override { Real()->m_bNextNodeReturnsCurrent.NetworkStateChanged(); }
    bool& StartedMoving() override { return Real()->m_bStartedMoving(); }
    void StartedMovingUpdated() override { Real()->m_bStartedMoving.NetworkStateChanged(); }
    CFuncMover__FollowEntityDirection_t& FollowEntityDirection() override { return Real()->m_eFollowEntityDirection(); }
    void FollowEntityDirectionUpdated() override { Real()->m_eFollowEntityDirection.NetworkStateChanged(); }
    CHandle<CFuncMover>& FollowMover() override { return Real()->m_hFollowMover(); }
    void FollowMoverUpdated() override { Real()->m_hFollowMover.NetworkStateChanged(); }
    CUtlSymbolLarge& FollowMoverEntityName() override { return Real()->m_iszFollowMoverEntityName(); }
    void FollowMoverEntityNameUpdated() override { Real()->m_iszFollowMoverEntityName.NetworkStateChanged(); }
    float& FollowMoverDistance() override { return Real()->m_flFollowMoverDistance(); }
    void FollowMoverDistanceUpdated() override { Real()->m_flFollowMoverDistance.NetworkStateChanged(); }
    float& FollowMoverRatio() override { return Real()->m_flFollowMoverRatio(); }
    void FollowMoverRatioUpdated() override { Real()->m_flFollowMoverRatio.NetworkStateChanged(); }
    float& FollowMoverCalculatedDistance() override { return Real()->m_flFollowMoverCalculatedDistance(); }
    void FollowMoverCalculatedDistanceUpdated() override { Real()->m_flFollowMoverCalculatedDistance.NetworkStateChanged(); }
    float& FollowMoverSpringStrength() override { return Real()->m_flFollowMoverSpringStrength(); }
    void FollowMoverSpringStrengthUpdated() override { Real()->m_flFollowMoverSpringStrength.NetworkStateChanged(); }
    int32_t& FollowMoverConstraintPriority() override { return Real()->m_nFollowMoverConstraintPriority(); }
    void FollowMoverConstraintPriorityUpdated() override { Real()->m_nFollowMoverConstraintPriority.NetworkStateChanged(); }
    bool& FollowConstraintsInitialized() override { return Real()->m_bFollowConstraintsInitialized(); }
    void FollowConstraintsInitializedUpdated() override { Real()->m_bFollowConstraintsInitialized.NetworkStateChanged(); }
    CFuncMover__FollowConstraint_t& FollowConstraint() override { return Real()->m_eFollowConstraint(); }
    void FollowConstraintUpdated() override { Real()->m_eFollowConstraint.NetworkStateChanged(); }
    float& FollowMoverSpeed() override { return Real()->m_flFollowMoverSpeed(); }
    void FollowMoverSpeedUpdated() override { Real()->m_flFollowMoverSpeed.NetworkStateChanged(); }
    float& FollowMoverVelocity() override { return Real()->m_flFollowMoverVelocity(); }
    void FollowMoverVelocityUpdated() override { Real()->m_flFollowMoverVelocity.NetworkStateChanged(); }
    int32_t& TickMovementRan() override { return Real()->m_nTickMovementRan(); }
    void TickMovementRanUpdated() override { Real()->m_nTickMovementRan.NetworkStateChanged(); }
    FuncMoverMovementSummary_t& MovementSummary() override { return Real()->m_movementSummary(); }
    void MovementSummaryUpdated() override { Real()->m_movementSummary.NetworkStateChanged(); }
    bool& StopFromBeginStopTarget() override { return Real()->m_bStopFromBeginStopTarget(); }
    void StopFromBeginStopTargetUpdated() override { Real()->m_bStopFromBeginStopTarget.NetworkStateChanged(); }
    bool& QueueStop() override { return Real()->m_bQueueStop(); }
    void QueueStopUpdated() override { Real()->m_bQueueStop.NetworkStateChanged(); }
    bool& QueueStopMoving() override { return Real()->m_bQueueStopMoving(); }
    void QueueStopMovingUpdated() override { Real()->m_bQueueStopMoving.NetworkStateChanged(); }
};

#endif // _INCLUDE_CFUNCMOVERIMPL_H
