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

#ifndef _INCLUDE_CCSBOTIMPL_H
#define _INCLUDE_CCSBOTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSBot.h"
#include "schema/entity/classes/CCSBot.h"
#include "CBotImpl.h"

class CCSBotImpl : public CBotImpl, public ICSBot
{

public:
    explicit CCSBotImpl(CCSBot* p) : CBotImpl(p) {}

private:
    CCSBot* Real() { return static_cast<CCSBot*>(m_pReal); }
    CCSBot* Real() const { return static_cast<CCSBot*>(m_pReal); }

public:
    CCSBot* GetOriginal() const override { return Real(); }
    Vector& EyePosition() override { return Real()->m_eyePosition(); }
    void EyePositionUpdated() override { Real()->m_eyePosition.NetworkStateChanged(); }
    char* Name() override { return Real()->m_name(); }
    float& CombatRange() override { return Real()->m_combatRange(); }
    void CombatRangeUpdated() override { Real()->m_combatRange.NetworkStateChanged(); }
    bool& IsRogue() override { return Real()->m_isRogue(); }
    void IsRogueUpdated() override { Real()->m_isRogue.NetworkStateChanged(); }
    ::CountdownTimer& RogueTimer() override { return Real()->m_rogueTimer(); }
    void RogueTimerUpdated() override { Real()->m_rogueTimer.NetworkStateChanged(); }
    bool& DiedLastRound() override { return Real()->m_diedLastRound(); }
    void DiedLastRoundUpdated() override { Real()->m_diedLastRound.NetworkStateChanged(); }
    float& SafeTime() override { return Real()->m_safeTime(); }
    void SafeTimeUpdated() override { Real()->m_safeTime.NetworkStateChanged(); }
    bool& WasSafe() override { return Real()->m_wasSafe(); }
    void WasSafeUpdated() override { Real()->m_wasSafe.NetworkStateChanged(); }
    bool& BlindFire() override { return Real()->m_blindFire(); }
    void BlindFireUpdated() override { Real()->m_blindFire.NetworkStateChanged(); }
    ::CountdownTimer& SurpriseTimer() override { return Real()->m_surpriseTimer(); }
    void SurpriseTimerUpdated() override { Real()->m_surpriseTimer.NetworkStateChanged(); }
    bool& AllowActive() override { return Real()->m_bAllowActive(); }
    void AllowActiveUpdated() override { Real()->m_bAllowActive.NetworkStateChanged(); }
    bool& IsFollowing() override { return Real()->m_isFollowing(); }
    void IsFollowingUpdated() override { Real()->m_isFollowing.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& Leader() override { return Real()->m_leader(); }
    void LeaderUpdated() override { Real()->m_leader.NetworkStateChanged(); }
    float& FollowTimestamp() override { return Real()->m_followTimestamp(); }
    void FollowTimestampUpdated() override { Real()->m_followTimestamp.NetworkStateChanged(); }
    float& AllowAutoFollowTime() override { return Real()->m_allowAutoFollowTime(); }
    void AllowAutoFollowTimeUpdated() override { Real()->m_allowAutoFollowTime.NetworkStateChanged(); }
    ::CountdownTimer& HurryTimer() override { return Real()->m_hurryTimer(); }
    void HurryTimerUpdated() override { Real()->m_hurryTimer.NetworkStateChanged(); }
    ::CountdownTimer& AlertTimer() override { return Real()->m_alertTimer(); }
    void AlertTimerUpdated() override { Real()->m_alertTimer.NetworkStateChanged(); }
    ::CountdownTimer& SneakTimer() override { return Real()->m_sneakTimer(); }
    void SneakTimerUpdated() override { Real()->m_sneakTimer.NetworkStateChanged(); }
    ::CountdownTimer& PanicTimer() override { return Real()->m_panicTimer(); }
    void PanicTimerUpdated() override { Real()->m_panicTimer.NetworkStateChanged(); }
    float& StateTimestamp() override { return Real()->m_stateTimestamp(); }
    void StateTimestampUpdated() override { Real()->m_stateTimestamp.NetworkStateChanged(); }
    bool& IsAttacking() override { return Real()->m_isAttacking(); }
    void IsAttackingUpdated() override { Real()->m_isAttacking.NetworkStateChanged(); }
    bool& IsOpeningDoor() override { return Real()->m_isOpeningDoor(); }
    void IsOpeningDoorUpdated() override { Real()->m_isOpeningDoor.NetworkStateChanged(); }
    CHandle<CBaseEntity>& TaskEntity() override { return Real()->m_taskEntity(); }
    void TaskEntityUpdated() override { Real()->m_taskEntity.NetworkStateChanged(); }
    Vector& GoalPosition() override { return Real()->m_goalPosition(); }
    void GoalPositionUpdated() override { Real()->m_goalPosition.NetworkStateChanged(); }
    CHandle<CBaseEntity>& GoalEntity() override { return Real()->m_goalEntity(); }
    void GoalEntityUpdated() override { Real()->m_goalEntity.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Avoid() override { return Real()->m_avoid(); }
    void AvoidUpdated() override { Real()->m_avoid.NetworkStateChanged(); }
    float& AvoidTimestamp() override { return Real()->m_avoidTimestamp(); }
    void AvoidTimestampUpdated() override { Real()->m_avoidTimestamp.NetworkStateChanged(); }
    bool& IsStopping() override { return Real()->m_isStopping(); }
    void IsStoppingUpdated() override { Real()->m_isStopping.NetworkStateChanged(); }
    bool& HasVisitedEnemySpawn() override { return Real()->m_hasVisitedEnemySpawn(); }
    void HasVisitedEnemySpawnUpdated() override { Real()->m_hasVisitedEnemySpawn.NetworkStateChanged(); }
    ::IntervalTimer& StillTimer() override { return Real()->m_stillTimer(); }
    void StillTimerUpdated() override { Real()->m_stillTimer.NetworkStateChanged(); }
    bool& EyeAnglesUnderPathFinderControl() override { return Real()->m_bEyeAnglesUnderPathFinderControl(); }
    void EyeAnglesUnderPathFinderControlUpdated() override { Real()->m_bEyeAnglesUnderPathFinderControl.NetworkStateChanged(); }
    int32_t& PathIndex() override { return Real()->m_pathIndex(); }
    void PathIndexUpdated() override { Real()->m_pathIndex.NetworkStateChanged(); }
    float& AreaEnteredTimestamp() override { return Real()->m_areaEnteredTimestamp(); }
    void AreaEnteredTimestampUpdated() override { Real()->m_areaEnteredTimestamp.NetworkStateChanged(); }
    ::CountdownTimer& RepathTimer() override { return Real()->m_repathTimer(); }
    void RepathTimerUpdated() override { Real()->m_repathTimer.NetworkStateChanged(); }
    ::CountdownTimer& AvoidFriendTimer() override { return Real()->m_avoidFriendTimer(); }
    void AvoidFriendTimerUpdated() override { Real()->m_avoidFriendTimer.NetworkStateChanged(); }
    bool& IsFriendInTheWay() override { return Real()->m_isFriendInTheWay(); }
    void IsFriendInTheWayUpdated() override { Real()->m_isFriendInTheWay.NetworkStateChanged(); }
    ::CountdownTimer& PoliteTimer() override { return Real()->m_politeTimer(); }
    void PoliteTimerUpdated() override { Real()->m_politeTimer.NetworkStateChanged(); }
    bool& IsWaitingBehindFriend() override { return Real()->m_isWaitingBehindFriend(); }
    void IsWaitingBehindFriendUpdated() override { Real()->m_isWaitingBehindFriend.NetworkStateChanged(); }
    float& PathLadderEnd() override { return Real()->m_pathLadderEnd(); }
    void PathLadderEndUpdated() override { Real()->m_pathLadderEnd.NetworkStateChanged(); }
    ::CountdownTimer& MustRunTimer() override { return Real()->m_mustRunTimer(); }
    void MustRunTimerUpdated() override { Real()->m_mustRunTimer.NetworkStateChanged(); }
    ::CountdownTimer& WaitTimer() override { return Real()->m_waitTimer(); }
    void WaitTimerUpdated() override { Real()->m_waitTimer.NetworkStateChanged(); }
    ::CountdownTimer& UpdateTravelDistanceTimer() override { return Real()->m_updateTravelDistanceTimer(); }
    void UpdateTravelDistanceTimerUpdated() override { Real()->m_updateTravelDistanceTimer.NetworkStateChanged(); }
    float* PlayerTravelDistance() override { return Real()->m_playerTravelDistance(); }
    uint8_t& TravelDistancePhase() override { return Real()->m_travelDistancePhase(); }
    void TravelDistancePhaseUpdated() override { Real()->m_travelDistancePhase.NetworkStateChanged(); }
    uint8_t& HostageEscortCount() override { return Real()->m_hostageEscortCount(); }
    void HostageEscortCountUpdated() override { Real()->m_hostageEscortCount.NetworkStateChanged(); }
    float& HostageEscortCountTimestamp() override { return Real()->m_hostageEscortCountTimestamp(); }
    void HostageEscortCountTimestampUpdated() override { Real()->m_hostageEscortCountTimestamp.NetworkStateChanged(); }
    int32_t& DesiredTeam() override { return Real()->m_desiredTeam(); }
    void DesiredTeamUpdated() override { Real()->m_desiredTeam.NetworkStateChanged(); }
    bool& HasJoined() override { return Real()->m_hasJoined(); }
    void HasJoinedUpdated() override { Real()->m_hasJoined.NetworkStateChanged(); }
    bool& IsWaitingForHostage() override { return Real()->m_isWaitingForHostage(); }
    void IsWaitingForHostageUpdated() override { Real()->m_isWaitingForHostage.NetworkStateChanged(); }
    ::CountdownTimer& InhibitWaitingForHostageTimer() override { return Real()->m_inhibitWaitingForHostageTimer(); }
    void InhibitWaitingForHostageTimerUpdated() override { Real()->m_inhibitWaitingForHostageTimer.NetworkStateChanged(); }
    ::CountdownTimer& WaitForHostageTimer() override { return Real()->m_waitForHostageTimer(); }
    void WaitForHostageTimerUpdated() override { Real()->m_waitForHostageTimer.NetworkStateChanged(); }
    Vector& NoisePosition() override { return Real()->m_noisePosition(); }
    void NoisePositionUpdated() override { Real()->m_noisePosition.NetworkStateChanged(); }
    float& NoiseTravelDistance() override { return Real()->m_noiseTravelDistance(); }
    void NoiseTravelDistanceUpdated() override { Real()->m_noiseTravelDistance.NetworkStateChanged(); }
    float& NoiseTimestamp() override { return Real()->m_noiseTimestamp(); }
    void NoiseTimestampUpdated() override { Real()->m_noiseTimestamp.NetworkStateChanged(); }
    CCSPlayerPawn*& NoiseSource() override { return Real()->m_noiseSource(); }
    void NoiseSourceUpdated() override { Real()->m_noiseSource.NetworkStateChanged(); }
    ::CountdownTimer& NoiseBendTimer() override { return Real()->m_noiseBendTimer(); }
    void NoiseBendTimerUpdated() override { Real()->m_noiseBendTimer.NetworkStateChanged(); }
    Vector& BentNoisePosition() override { return Real()->m_bentNoisePosition(); }
    void BentNoisePositionUpdated() override { Real()->m_bentNoisePosition.NetworkStateChanged(); }
    bool& BendNoisePositionValid() override { return Real()->m_bendNoisePositionValid(); }
    void BendNoisePositionValidUpdated() override { Real()->m_bendNoisePositionValid.NetworkStateChanged(); }
    float& LookAroundStateTimestamp() override { return Real()->m_lookAroundStateTimestamp(); }
    void LookAroundStateTimestampUpdated() override { Real()->m_lookAroundStateTimestamp.NetworkStateChanged(); }
    float& LookAheadAngle() override { return Real()->m_lookAheadAngle(); }
    void LookAheadAngleUpdated() override { Real()->m_lookAheadAngle.NetworkStateChanged(); }
    float& LookUpAngle() override { return Real()->m_lookUpAngle(); }
    void LookUpAngleUpdated() override { Real()->m_lookUpAngle.NetworkStateChanged(); }
    float& ForwardAngle() override { return Real()->m_forwardAngle(); }
    void ForwardAngleUpdated() override { Real()->m_forwardAngle.NetworkStateChanged(); }
    float& InhibitLookAroundTimestamp() override { return Real()->m_inhibitLookAroundTimestamp(); }
    void InhibitLookAroundTimestampUpdated() override { Real()->m_inhibitLookAroundTimestamp.NetworkStateChanged(); }
    Vector& LookAtSpot() override { return Real()->m_lookAtSpot(); }
    void LookAtSpotUpdated() override { Real()->m_lookAtSpot.NetworkStateChanged(); }
    float& LookAtSpotDuration() override { return Real()->m_lookAtSpotDuration(); }
    void LookAtSpotDurationUpdated() override { Real()->m_lookAtSpotDuration.NetworkStateChanged(); }
    float& LookAtSpotTimestamp() override { return Real()->m_lookAtSpotTimestamp(); }
    void LookAtSpotTimestampUpdated() override { Real()->m_lookAtSpotTimestamp.NetworkStateChanged(); }
    float& LookAtSpotAngleTolerance() override { return Real()->m_lookAtSpotAngleTolerance(); }
    void LookAtSpotAngleToleranceUpdated() override { Real()->m_lookAtSpotAngleTolerance.NetworkStateChanged(); }
    bool& LookAtSpotClearIfClose() override { return Real()->m_lookAtSpotClearIfClose(); }
    void LookAtSpotClearIfCloseUpdated() override { Real()->m_lookAtSpotClearIfClose.NetworkStateChanged(); }
    bool& LookAtSpotAttack() override { return Real()->m_lookAtSpotAttack(); }
    void LookAtSpotAttackUpdated() override { Real()->m_lookAtSpotAttack.NetworkStateChanged(); }
    char*& LookAtDesc() override { return Real()->m_lookAtDesc(); }
    void LookAtDescUpdated() override { Real()->m_lookAtDesc.NetworkStateChanged(); }
    float& PeripheralTimestamp() override { return Real()->m_peripheralTimestamp(); }
    void PeripheralTimestampUpdated() override { Real()->m_peripheralTimestamp.NetworkStateChanged(); }
    uint8_t& ApproachPointCount() override { return Real()->m_approachPointCount(); }
    void ApproachPointCountUpdated() override { Real()->m_approachPointCount.NetworkStateChanged(); }
    Vector& ApproachPointViewPosition() override { return Real()->m_approachPointViewPosition(); }
    void ApproachPointViewPositionUpdated() override { Real()->m_approachPointViewPosition.NetworkStateChanged(); }
    ::IntervalTimer& ViewSteadyTimer() override { return Real()->m_viewSteadyTimer(); }
    void ViewSteadyTimerUpdated() override { Real()->m_viewSteadyTimer.NetworkStateChanged(); }
    ::CountdownTimer& TossGrenadeTimer() override { return Real()->m_tossGrenadeTimer(); }
    void TossGrenadeTimerUpdated() override { Real()->m_tossGrenadeTimer.NetworkStateChanged(); }
    ::CountdownTimer& IsAvoidingGrenade() override { return Real()->m_isAvoidingGrenade(); }
    void IsAvoidingGrenadeUpdated() override { Real()->m_isAvoidingGrenade.NetworkStateChanged(); }
    float& SpotCheckTimestamp() override { return Real()->m_spotCheckTimestamp(); }
    void SpotCheckTimestampUpdated() override { Real()->m_spotCheckTimestamp.NetworkStateChanged(); }
    int32_t& CheckedHidingSpotCount() override { return Real()->m_checkedHidingSpotCount(); }
    void CheckedHidingSpotCountUpdated() override { Real()->m_checkedHidingSpotCount.NetworkStateChanged(); }
    float& LookPitch() override { return Real()->m_lookPitch(); }
    void LookPitchUpdated() override { Real()->m_lookPitch.NetworkStateChanged(); }
    float& LookPitchVel() override { return Real()->m_lookPitchVel(); }
    void LookPitchVelUpdated() override { Real()->m_lookPitchVel.NetworkStateChanged(); }
    float& LookYaw() override { return Real()->m_lookYaw(); }
    void LookYawUpdated() override { Real()->m_lookYaw.NetworkStateChanged(); }
    float& LookYawVel() override { return Real()->m_lookYawVel(); }
    void LookYawVelUpdated() override { Real()->m_lookYawVel.NetworkStateChanged(); }
    Vector& TargetSpot() override { return Real()->m_targetSpot(); }
    void TargetSpotUpdated() override { Real()->m_targetSpot.NetworkStateChanged(); }
    Vector& TargetSpotVelocity() override { return Real()->m_targetSpotVelocity(); }
    void TargetSpotVelocityUpdated() override { Real()->m_targetSpotVelocity.NetworkStateChanged(); }
    Vector& TargetSpotPredicted() override { return Real()->m_targetSpotPredicted(); }
    void TargetSpotPredictedUpdated() override { Real()->m_targetSpotPredicted.NetworkStateChanged(); }
    QAngle& AimError() override { return Real()->m_aimError(); }
    void AimErrorUpdated() override { Real()->m_aimError.NetworkStateChanged(); }
    QAngle& AimGoal() override { return Real()->m_aimGoal(); }
    void AimGoalUpdated() override { Real()->m_aimGoal.NetworkStateChanged(); }
    float& TargetSpotTime() override { return Real()->m_targetSpotTime(); }
    void TargetSpotTimeUpdated() override { Real()->m_targetSpotTime.NetworkStateChanged(); }
    float& AimFocus() override { return Real()->m_aimFocus(); }
    void AimFocusUpdated() override { Real()->m_aimFocus.NetworkStateChanged(); }
    float& AimFocusInterval() override { return Real()->m_aimFocusInterval(); }
    void AimFocusIntervalUpdated() override { Real()->m_aimFocusInterval.NetworkStateChanged(); }
    float& AimFocusNextUpdate() override { return Real()->m_aimFocusNextUpdate(); }
    void AimFocusNextUpdateUpdated() override { Real()->m_aimFocusNextUpdate.NetworkStateChanged(); }
    ::CountdownTimer& IgnoreEnemiesTimer() override { return Real()->m_ignoreEnemiesTimer(); }
    void IgnoreEnemiesTimerUpdated() override { Real()->m_ignoreEnemiesTimer.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& Enemy() override { return Real()->m_enemy(); }
    void EnemyUpdated() override { Real()->m_enemy.NetworkStateChanged(); }
    bool& IsEnemyVisible() override { return Real()->m_isEnemyVisible(); }
    void IsEnemyVisibleUpdated() override { Real()->m_isEnemyVisible.NetworkStateChanged(); }
    uint8_t& VisibleEnemyParts() override { return Real()->m_visibleEnemyParts(); }
    void VisibleEnemyPartsUpdated() override { Real()->m_visibleEnemyParts.NetworkStateChanged(); }
    Vector& LastEnemyPosition() override { return Real()->m_lastEnemyPosition(); }
    void LastEnemyPositionUpdated() override { Real()->m_lastEnemyPosition.NetworkStateChanged(); }
    float& LastSawEnemyTimestamp() override { return Real()->m_lastSawEnemyTimestamp(); }
    void LastSawEnemyTimestampUpdated() override { Real()->m_lastSawEnemyTimestamp.NetworkStateChanged(); }
    float& FirstSawEnemyTimestamp() override { return Real()->m_firstSawEnemyTimestamp(); }
    void FirstSawEnemyTimestampUpdated() override { Real()->m_firstSawEnemyTimestamp.NetworkStateChanged(); }
    float& CurrentEnemyAcquireTimestamp() override { return Real()->m_currentEnemyAcquireTimestamp(); }
    void CurrentEnemyAcquireTimestampUpdated() override { Real()->m_currentEnemyAcquireTimestamp.NetworkStateChanged(); }
    float& EnemyDeathTimestamp() override { return Real()->m_enemyDeathTimestamp(); }
    void EnemyDeathTimestampUpdated() override { Real()->m_enemyDeathTimestamp.NetworkStateChanged(); }
    float& FriendDeathTimestamp() override { return Real()->m_friendDeathTimestamp(); }
    void FriendDeathTimestampUpdated() override { Real()->m_friendDeathTimestamp.NetworkStateChanged(); }
    bool& IsLastEnemyDead() override { return Real()->m_isLastEnemyDead(); }
    void IsLastEnemyDeadUpdated() override { Real()->m_isLastEnemyDead.NetworkStateChanged(); }
    int32_t& NearbyEnemyCount() override { return Real()->m_nearbyEnemyCount(); }
    void NearbyEnemyCountUpdated() override { Real()->m_nearbyEnemyCount.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& Bomber() override { return Real()->m_bomber(); }
    void BomberUpdated() override { Real()->m_bomber.NetworkStateChanged(); }
    int32_t& NearbyFriendCount() override { return Real()->m_nearbyFriendCount(); }
    void NearbyFriendCountUpdated() override { Real()->m_nearbyFriendCount.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& ClosestVisibleFriend() override { return Real()->m_closestVisibleFriend(); }
    void ClosestVisibleFriendUpdated() override { Real()->m_closestVisibleFriend.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& ClosestVisibleHumanFriend() override { return Real()->m_closestVisibleHumanFriend(); }
    void ClosestVisibleHumanFriendUpdated() override { Real()->m_closestVisibleHumanFriend.NetworkStateChanged(); }
    ::IntervalTimer& AttentionInterval() override { return Real()->m_attentionInterval(); }
    void AttentionIntervalUpdated() override { Real()->m_attentionInterval.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& Attacker() override { return Real()->m_attacker(); }
    void AttackerUpdated() override { Real()->m_attacker.NetworkStateChanged(); }
    float& AttackedTimestamp() override { return Real()->m_attackedTimestamp(); }
    void AttackedTimestampUpdated() override { Real()->m_attackedTimestamp.NetworkStateChanged(); }
    ::IntervalTimer& BurnedByFlamesTimer() override { return Real()->m_burnedByFlamesTimer(); }
    void BurnedByFlamesTimerUpdated() override { Real()->m_burnedByFlamesTimer.NetworkStateChanged(); }
    int32_t& LastVictimID() override { return Real()->m_lastVictimID(); }
    void LastVictimIDUpdated() override { Real()->m_lastVictimID.NetworkStateChanged(); }
    bool& IsAimingAtEnemy() override { return Real()->m_isAimingAtEnemy(); }
    void IsAimingAtEnemyUpdated() override { Real()->m_isAimingAtEnemy.NetworkStateChanged(); }
    bool& IsRapidFiring() override { return Real()->m_isRapidFiring(); }
    void IsRapidFiringUpdated() override { Real()->m_isRapidFiring.NetworkStateChanged(); }
    ::IntervalTimer& EquipTimer() override { return Real()->m_equipTimer(); }
    void EquipTimerUpdated() override { Real()->m_equipTimer.NetworkStateChanged(); }
    ::CountdownTimer& ZoomTimer() override { return Real()->m_zoomTimer(); }
    void ZoomTimerUpdated() override { Real()->m_zoomTimer.NetworkStateChanged(); }
    float& FireWeaponTimestamp() override { return Real()->m_fireWeaponTimestamp(); }
    void FireWeaponTimestampUpdated() override { Real()->m_fireWeaponTimestamp.NetworkStateChanged(); }
    ::CountdownTimer& LookForWeaponsOnGroundTimer() override { return Real()->m_lookForWeaponsOnGroundTimer(); }
    void LookForWeaponsOnGroundTimerUpdated() override { Real()->m_lookForWeaponsOnGroundTimer.NetworkStateChanged(); }
    bool& IsSleeping() override { return Real()->m_bIsSleeping(); }
    void IsSleepingUpdated() override { Real()->m_bIsSleeping.NetworkStateChanged(); }
    bool& IsEnemySniperVisible() override { return Real()->m_isEnemySniperVisible(); }
    void IsEnemySniperVisibleUpdated() override { Real()->m_isEnemySniperVisible.NetworkStateChanged(); }
    ::CountdownTimer& SawEnemySniperTimer() override { return Real()->m_sawEnemySniperTimer(); }
    void SawEnemySniperTimerUpdated() override { Real()->m_sawEnemySniperTimer.NetworkStateChanged(); }
    uint8_t& EnemyQueueIndex() override { return Real()->m_enemyQueueIndex(); }
    void EnemyQueueIndexUpdated() override { Real()->m_enemyQueueIndex.NetworkStateChanged(); }
    uint8_t& EnemyQueueCount() override { return Real()->m_enemyQueueCount(); }
    void EnemyQueueCountUpdated() override { Real()->m_enemyQueueCount.NetworkStateChanged(); }
    uint8_t& EnemyQueueAttendIndex() override { return Real()->m_enemyQueueAttendIndex(); }
    void EnemyQueueAttendIndexUpdated() override { Real()->m_enemyQueueAttendIndex.NetworkStateChanged(); }
    bool& IsStuck() override { return Real()->m_isStuck(); }
    void IsStuckUpdated() override { Real()->m_isStuck.NetworkStateChanged(); }
    float& StuckTimestamp() override { return Real()->m_stuckTimestamp(); }
    void StuckTimestampUpdated() override { Real()->m_stuckTimestamp.NetworkStateChanged(); }
    Vector& StuckSpot() override { return Real()->m_stuckSpot(); }
    void StuckSpotUpdated() override { Real()->m_stuckSpot.NetworkStateChanged(); }
    ::CountdownTimer& WiggleTimer() override { return Real()->m_wiggleTimer(); }
    void WiggleTimerUpdated() override { Real()->m_wiggleTimer.NetworkStateChanged(); }
    ::CountdownTimer& StuckJumpTimer() override { return Real()->m_stuckJumpTimer(); }
    void StuckJumpTimerUpdated() override { Real()->m_stuckJumpTimer.NetworkStateChanged(); }
    float& NextCleanupCheckTimestamp() override { return Real()->m_nextCleanupCheckTimestamp(); }
    void NextCleanupCheckTimestampUpdated() override { Real()->m_nextCleanupCheckTimestamp.NetworkStateChanged(); }
    float* AvgVel() override { return Real()->m_avgVel(); }
    int32_t& AvgVelIndex() override { return Real()->m_avgVelIndex(); }
    void AvgVelIndexUpdated() override { Real()->m_avgVelIndex.NetworkStateChanged(); }
    int32_t& AvgVelCount() override { return Real()->m_avgVelCount(); }
    void AvgVelCountUpdated() override { Real()->m_avgVelCount.NetworkStateChanged(); }
    Vector& LastOrigin() override { return Real()->m_lastOrigin(); }
    void LastOriginUpdated() override { Real()->m_lastOrigin.NetworkStateChanged(); }
    float& LastRadioRecievedTimestamp() override { return Real()->m_lastRadioRecievedTimestamp(); }
    void LastRadioRecievedTimestampUpdated() override { Real()->m_lastRadioRecievedTimestamp.NetworkStateChanged(); }
    float& LastRadioSentTimestamp() override { return Real()->m_lastRadioSentTimestamp(); }
    void LastRadioSentTimestampUpdated() override { Real()->m_lastRadioSentTimestamp.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& RadioSubject() override { return Real()->m_radioSubject(); }
    void RadioSubjectUpdated() override { Real()->m_radioSubject.NetworkStateChanged(); }
    Vector& RadioPosition() override { return Real()->m_radioPosition(); }
    void RadioPositionUpdated() override { Real()->m_radioPosition.NetworkStateChanged(); }
    float& VoiceEndTimestamp() override { return Real()->m_voiceEndTimestamp(); }
    void VoiceEndTimestampUpdated() override { Real()->m_voiceEndTimestamp.NetworkStateChanged(); }
    int32_t& LastValidReactionQueueFrame() override { return Real()->m_lastValidReactionQueueFrame(); }
    void LastValidReactionQueueFrameUpdated() override { Real()->m_lastValidReactionQueueFrame.NetworkStateChanged(); }
};

inline ICSBot* CCSBot::ToInterface() { return new CCSBotImpl(this); }
inline ICSBot* ICSBot::FromOriginal(CCSBot* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSBOTIMPL_H
