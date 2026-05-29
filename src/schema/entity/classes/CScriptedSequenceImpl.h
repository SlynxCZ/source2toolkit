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

#ifndef _INCLUDE_CSCRIPTEDSEQUENCEIMPL_H
#define _INCLUDE_CSCRIPTEDSEQUENCEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IScriptedSequence.h"
#include "schema/entity/classes/CScriptedSequence.h"
#include "CBaseEntityImpl.h"

class CScriptedSequenceImpl : public CBaseEntityImpl, public virtual IScriptedSequence
{

public:
    explicit CScriptedSequenceImpl(CScriptedSequence* p) : CBaseEntityImpl(p) {}

private:
    CScriptedSequence* Real() { return static_cast<CScriptedSequence*>(m_pReal); }
    CScriptedSequence* Real() const { return static_cast<CScriptedSequence*>(m_pReal); }

public:
    CScriptedSequence* GetOriginal() const override { return Real(); }
    CUtlSymbolLarge& Entry() override { return Real()->m_iszEntry(); }
    void EntryUpdated() override { Real()->m_iszEntry.NetworkStateChanged(); }
    CUtlSymbolLarge& PreIdle() override { return Real()->m_iszPreIdle(); }
    void PreIdleUpdated() override { Real()->m_iszPreIdle.NetworkStateChanged(); }
    CUtlSymbolLarge& Play() override { return Real()->m_iszPlay(); }
    void PlayUpdated() override { Real()->m_iszPlay.NetworkStateChanged(); }
    CUtlSymbolLarge& PostIdle() override { return Real()->m_iszPostIdle(); }
    void PostIdleUpdated() override { Real()->m_iszPostIdle.NetworkStateChanged(); }
    CUtlSymbolLarge& ModifierToAddOnPlay() override { return Real()->m_iszModifierToAddOnPlay(); }
    void ModifierToAddOnPlayUpdated() override { Real()->m_iszModifierToAddOnPlay.NetworkStateChanged(); }
    CUtlSymbolLarge& NextScript() override { return Real()->m_iszNextScript(); }
    void NextScriptUpdated() override { Real()->m_iszNextScript.NetworkStateChanged(); }
    CUtlSymbolLarge& Entity() override { return Real()->m_iszEntity(); }
    void EntityUpdated() override { Real()->m_iszEntity.NetworkStateChanged(); }
    CUtlSymbolLarge& SyncGroup() override { return Real()->m_iszSyncGroup(); }
    void SyncGroupUpdated() override { Real()->m_iszSyncGroup.NetworkStateChanged(); }
    ::ScriptedMoveTo_t& MoveTo() override { return Real()->m_nMoveTo(); }
    void MoveToUpdated() override { Real()->m_nMoveTo.NetworkStateChanged(); }
    ::SharedMovementGait_t& MoveToGait() override { return Real()->m_nMoveToGait(); }
    void MoveToGaitUpdated() override { Real()->m_nMoveToGait.NetworkStateChanged(); }
    ::ScriptedHeldWeaponBehavior_t& HeldWeaponBehavior() override { return Real()->m_nHeldWeaponBehavior(); }
    void HeldWeaponBehaviorUpdated() override { Real()->m_nHeldWeaponBehavior.NetworkStateChanged(); }
    ::ForcedCrouchState_t& ForcedCrouchState() override { return Real()->m_nForcedCrouchState(); }
    void ForcedCrouchStateUpdated() override { Real()->m_nForcedCrouchState.NetworkStateChanged(); }
    bool& IsPlayingPreIdle() override { return Real()->m_bIsPlayingPreIdle(); }
    void IsPlayingPreIdleUpdated() override { Real()->m_bIsPlayingPreIdle.NetworkStateChanged(); }
    bool& IsPlayingEntry() override { return Real()->m_bIsPlayingEntry(); }
    void IsPlayingEntryUpdated() override { Real()->m_bIsPlayingEntry.NetworkStateChanged(); }
    bool& IsPlayingAction() override { return Real()->m_bIsPlayingAction(); }
    void IsPlayingActionUpdated() override { Real()->m_bIsPlayingAction.NetworkStateChanged(); }
    bool& IsPlayingPostIdle() override { return Real()->m_bIsPlayingPostIdle(); }
    void IsPlayingPostIdleUpdated() override { Real()->m_bIsPlayingPostIdle.NetworkStateChanged(); }
    bool& DontRotateOther() override { return Real()->m_bDontRotateOther(); }
    void DontRotateOtherUpdated() override { Real()->m_bDontRotateOther.NetworkStateChanged(); }
    bool& IsRepeatable() override { return Real()->m_bIsRepeatable(); }
    void IsRepeatableUpdated() override { Real()->m_bIsRepeatable.NetworkStateChanged(); }
    bool& ShouldLeaveCorpse() override { return Real()->m_bShouldLeaveCorpse(); }
    void ShouldLeaveCorpseUpdated() override { Real()->m_bShouldLeaveCorpse.NetworkStateChanged(); }
    bool& StartOnSpawn() override { return Real()->m_bStartOnSpawn(); }
    void StartOnSpawnUpdated() override { Real()->m_bStartOnSpawn.NetworkStateChanged(); }
    bool& DisallowInterrupts() override { return Real()->m_bDisallowInterrupts(); }
    void DisallowInterruptsUpdated() override { Real()->m_bDisallowInterrupts.NetworkStateChanged(); }
    bool& CanOverrideNPCState() override { return Real()->m_bCanOverrideNPCState(); }
    void CanOverrideNPCStateUpdated() override { Real()->m_bCanOverrideNPCState.NetworkStateChanged(); }
    bool& DontTeleportAtEnd() override { return Real()->m_bDontTeleportAtEnd(); }
    void DontTeleportAtEndUpdated() override { Real()->m_bDontTeleportAtEnd.NetworkStateChanged(); }
    bool& HighPriority() override { return Real()->m_bHighPriority(); }
    void HighPriorityUpdated() override { Real()->m_bHighPriority.NetworkStateChanged(); }
    bool& HideDebugComplaints() override { return Real()->m_bHideDebugComplaints(); }
    void HideDebugComplaintsUpdated() override { Real()->m_bHideDebugComplaints.NetworkStateChanged(); }
    bool& ContinueOnDeath() override { return Real()->m_bContinueOnDeath(); }
    void ContinueOnDeathUpdated() override { Real()->m_bContinueOnDeath.NetworkStateChanged(); }
    bool& LoopPreIdleSequence() override { return Real()->m_bLoopPreIdleSequence(); }
    void LoopPreIdleSequenceUpdated() override { Real()->m_bLoopPreIdleSequence.NetworkStateChanged(); }
    bool& LoopActionSequence() override { return Real()->m_bLoopActionSequence(); }
    void LoopActionSequenceUpdated() override { Real()->m_bLoopActionSequence.NetworkStateChanged(); }
    bool& LoopPostIdleSequence() override { return Real()->m_bLoopPostIdleSequence(); }
    void LoopPostIdleSequenceUpdated() override { Real()->m_bLoopPostIdleSequence.NetworkStateChanged(); }
    bool& SynchPostIdles() override { return Real()->m_bSynchPostIdles(); }
    void SynchPostIdlesUpdated() override { Real()->m_bSynchPostIdles.NetworkStateChanged(); }
    bool& IgnoreLookAt() override { return Real()->m_bIgnoreLookAt(); }
    void IgnoreLookAtUpdated() override { Real()->m_bIgnoreLookAt.NetworkStateChanged(); }
    bool& IgnoreGravity() override { return Real()->m_bIgnoreGravity(); }
    void IgnoreGravityUpdated() override { Real()->m_bIgnoreGravity.NetworkStateChanged(); }
    bool& DisableNPCCollisions() override { return Real()->m_bDisableNPCCollisions(); }
    void DisableNPCCollisionsUpdated() override { Real()->m_bDisableNPCCollisions.NetworkStateChanged(); }
    bool& KeepAnimgraphLockedPost() override { return Real()->m_bKeepAnimgraphLockedPost(); }
    void KeepAnimgraphLockedPostUpdated() override { Real()->m_bKeepAnimgraphLockedPost.NetworkStateChanged(); }
    bool& DontAddModifiers() override { return Real()->m_bDontAddModifiers(); }
    void DontAddModifiersUpdated() override { Real()->m_bDontAddModifiers.NetworkStateChanged(); }
    bool& DisableAimingWhileMoving() override { return Real()->m_bDisableAimingWhileMoving(); }
    void DisableAimingWhileMovingUpdated() override { Real()->m_bDisableAimingWhileMoving.NetworkStateChanged(); }
    bool& IgnoreRotation() override { return Real()->m_bIgnoreRotation(); }
    void IgnoreRotationUpdated() override { Real()->m_bIgnoreRotation.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_flRadius(); }
    void RadiusUpdated() override { Real()->m_flRadius.NetworkStateChanged(); }
    float& Repeat() override { return Real()->m_flRepeat(); }
    void RepeatUpdated() override { Real()->m_flRepeat.NetworkStateChanged(); }
    float& PlayAnimFadeInTime() override { return Real()->m_flPlayAnimFadeInTime(); }
    void PlayAnimFadeInTimeUpdated() override { Real()->m_flPlayAnimFadeInTime.NetworkStateChanged(); }
    float& MoveInterpTime() override { return Real()->m_flMoveInterpTime(); }
    void MoveInterpTimeUpdated() override { Real()->m_flMoveInterpTime.NetworkStateChanged(); }
    float& AngRate() override { return Real()->m_flAngRate(); }
    void AngRateUpdated() override { Real()->m_flAngRate.NetworkStateChanged(); }
    float& MoveSpeed() override { return Real()->m_flMoveSpeed(); }
    void MoveSpeedUpdated() override { Real()->m_flMoveSpeed.NetworkStateChanged(); }
    bool& WaitUntilMoveCompletesToStartAnimation() override { return Real()->m_bWaitUntilMoveCompletesToStartAnimation(); }
    void WaitUntilMoveCompletesToStartAnimationUpdated() override { Real()->m_bWaitUntilMoveCompletesToStartAnimation.NetworkStateChanged(); }
    int32_t& NotReadySequenceCount() override { return Real()->m_nNotReadySequenceCount(); }
    void NotReadySequenceCountUpdated() override { Real()->m_nNotReadySequenceCount.NetworkStateChanged(); }
    float& StartTime() override { return Real()->m_startTime(); }
    void StartTimeUpdated() override { Real()->m_startTime.NetworkStateChanged(); }
    bool& WaitForBeginSequence() override { return Real()->m_bWaitForBeginSequence(); }
    void WaitForBeginSequenceUpdated() override { Real()->m_bWaitForBeginSequence.NetworkStateChanged(); }
    int32_t& Saved_effects() override { return Real()->m_saved_effects(); }
    void Saved_effectsUpdated() override { Real()->m_saved_effects.NetworkStateChanged(); }
    int32_t& SavedFlags() override { return Real()->m_savedFlags(); }
    void SavedFlagsUpdated() override { Real()->m_savedFlags.NetworkStateChanged(); }
    int32_t& SavedCollisionGroup() override { return Real()->m_savedCollisionGroup(); }
    void SavedCollisionGroupUpdated() override { Real()->m_savedCollisionGroup.NetworkStateChanged(); }
    bool& Interruptable() override { return Real()->m_bInterruptable(); }
    void InterruptableUpdated() override { Real()->m_bInterruptable.NetworkStateChanged(); }
    bool& SequenceStarted() override { return Real()->m_sequenceStarted(); }
    void SequenceStartedUpdated() override { Real()->m_sequenceStarted.NetworkStateChanged(); }
    bool& PositionRelativeToOtherEntity() override { return Real()->m_bPositionRelativeToOtherEntity(); }
    void PositionRelativeToOtherEntityUpdated() override { Real()->m_bPositionRelativeToOtherEntity.NetworkStateChanged(); }
    CHandle<CBaseEntity>& TargetEnt() override { return Real()->m_hTargetEnt(); }
    void TargetEntUpdated() override { Real()->m_hTargetEnt.NetworkStateChanged(); }
    CHandle<CScriptedSequence>& NextCine() override { return Real()->m_hNextCine(); }
    void NextCineUpdated() override { Real()->m_hNextCine.NetworkStateChanged(); }
    bool& Thinking() override { return Real()->m_bThinking(); }
    void ThinkingUpdated() override { Real()->m_bThinking.NetworkStateChanged(); }
    bool& InitiatedSelfDelete() override { return Real()->m_bInitiatedSelfDelete(); }
    void InitiatedSelfDeleteUpdated() override { Real()->m_bInitiatedSelfDelete.NetworkStateChanged(); }
    bool& IsTeleportingDueToMoveTo() override { return Real()->m_bIsTeleportingDueToMoveTo(); }
    void IsTeleportingDueToMoveToUpdated() override { Real()->m_bIsTeleportingDueToMoveTo.NetworkStateChanged(); }
    bool& AllowCustomInterruptConditions() override { return Real()->m_bAllowCustomInterruptConditions(); }
    void AllowCustomInterruptConditionsUpdated() override { Real()->m_bAllowCustomInterruptConditions.NetworkStateChanged(); }
    CHandle<CBaseAnimGraph>& ForcedTarget() override { return Real()->m_hForcedTarget(); }
    void ForcedTargetUpdated() override { Real()->m_hForcedTarget.NetworkStateChanged(); }
    bool& DontCancelOtherSequences() override { return Real()->m_bDontCancelOtherSequences(); }
    void DontCancelOtherSequencesUpdated() override { Real()->m_bDontCancelOtherSequences.NetworkStateChanged(); }
    bool& ForceSynch() override { return Real()->m_bForceSynch(); }
    void ForceSynchUpdated() override { Real()->m_bForceSynch.NetworkStateChanged(); }
    bool& PreventUpdateYawOnFinish() override { return Real()->m_bPreventUpdateYawOnFinish(); }
    void PreventUpdateYawOnFinishUpdated() override { Real()->m_bPreventUpdateYawOnFinish.NetworkStateChanged(); }
    bool& EnsureOnNavmeshOnFinish() override { return Real()->m_bEnsureOnNavmeshOnFinish(); }
    void EnsureOnNavmeshOnFinishUpdated() override { Real()->m_bEnsureOnNavmeshOnFinish.NetworkStateChanged(); }
    ::ScriptedOnDeath_t& OnDeathBehavior() override { return Real()->m_onDeathBehavior(); }
    void OnDeathBehaviorUpdated() override { Real()->m_onDeathBehavior.NetworkStateChanged(); }
    ::ScriptedConflictResponse_t& ConflictResponse() override { return Real()->m_ConflictResponse(); }
    void ConflictResponseUpdated() override { Real()->m_ConflictResponse.NetworkStateChanged(); }
    ::CEntityIOOutput& OnBeginSequence() override { return Real()->m_OnBeginSequence(); }
    void OnBeginSequenceUpdated() override { Real()->m_OnBeginSequence.NetworkStateChanged(); }
    ::CEntityIOOutput& OnActionStartOrLoop() override { return Real()->m_OnActionStartOrLoop(); }
    void OnActionStartOrLoopUpdated() override { Real()->m_OnActionStartOrLoop.NetworkStateChanged(); }
    ::CEntityIOOutput& OnEndSequence() override { return Real()->m_OnEndSequence(); }
    void OnEndSequenceUpdated() override { Real()->m_OnEndSequence.NetworkStateChanged(); }
    ::CEntityIOOutput& OnPostIdleEndSequence() override { return Real()->m_OnPostIdleEndSequence(); }
    void OnPostIdleEndSequenceUpdated() override { Real()->m_OnPostIdleEndSequence.NetworkStateChanged(); }
    ::CEntityIOOutput& OnCancelSequence() override { return Real()->m_OnCancelSequence(); }
    void OnCancelSequenceUpdated() override { Real()->m_OnCancelSequence.NetworkStateChanged(); }
    ::CEntityIOOutput& OnCancelFailedSequence() override { return Real()->m_OnCancelFailedSequence(); }
    void OnCancelFailedSequenceUpdated() override { Real()->m_OnCancelFailedSequence.NetworkStateChanged(); }
    CEntityIOOutput* OnScriptEvent() override { return Real()->m_OnScriptEvent(); }
    CTransform& MatOtherToMain() override { return Real()->m_matOtherToMain(); }
    void MatOtherToMainUpdated() override { Real()->m_matOtherToMain.NetworkStateChanged(); }
    CHandle<CBaseEntity>& InteractionMainEntity() override { return Real()->m_hInteractionMainEntity(); }
    void InteractionMainEntityUpdated() override { Real()->m_hInteractionMainEntity.NetworkStateChanged(); }
    int32_t& PlayerDeathBehavior() override { return Real()->m_iPlayerDeathBehavior(); }
    void PlayerDeathBehaviorUpdated() override { Real()->m_iPlayerDeathBehavior.NetworkStateChanged(); }
    bool& SkipFadeIn() override { return Real()->m_bSkipFadeIn(); }
    void SkipFadeInUpdated() override { Real()->m_bSkipFadeIn.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IScriptedSequence* CScriptedSequence::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IScriptedSequence*>(tagIt->second.ptr_for_return);
    auto* impl = new CScriptedSequenceImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IScriptedSequence*>(impl));
    return impl;
}
inline IScriptedSequence* IScriptedSequence::FromRaw(CEntityInstance* p) { return p ? static_cast<CScriptedSequence*>(p)->ToInterface() : nullptr; }
inline IScriptedSequence* IScriptedSequence::FromOriginal(CScriptedSequence* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CSCRIPTEDSEQUENCEIMPL_H
