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

#ifndef _INCLUDE_CSCENEENTITYIMPL_H
#define _INCLUDE_CSCENEENTITYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISceneEntity.h"
#include "schema/entity/classes/CSceneEntity.h"
#include "CPointEntityImpl.h"

class CSceneEntityImpl : public CPointEntityImpl, public ISceneEntity
{

public:
    explicit CSceneEntityImpl(CSceneEntity* p) : CPointEntityImpl(p) {}

private:
    CSceneEntity* Real() { return static_cast<CSceneEntity*>(m_pReal); }

public:
    CUtlSymbolLarge& SceneFile() override { return Real()->m_iszSceneFile(); }
    void SceneFileUpdated() override { Real()->m_iszSceneFile.NetworkStateChanged(); }
    CUtlSymbolLarge& Target1() override { return Real()->m_iszTarget1(); }
    void Target1Updated() override { Real()->m_iszTarget1.NetworkStateChanged(); }
    CUtlSymbolLarge& Target2() override { return Real()->m_iszTarget2(); }
    void Target2Updated() override { Real()->m_iszTarget2.NetworkStateChanged(); }
    CUtlSymbolLarge& Target3() override { return Real()->m_iszTarget3(); }
    void Target3Updated() override { Real()->m_iszTarget3.NetworkStateChanged(); }
    CUtlSymbolLarge& Target4() override { return Real()->m_iszTarget4(); }
    void Target4Updated() override { Real()->m_iszTarget4.NetworkStateChanged(); }
    CUtlSymbolLarge& Target5() override { return Real()->m_iszTarget5(); }
    void Target5Updated() override { Real()->m_iszTarget5.NetworkStateChanged(); }
    CUtlSymbolLarge& Target6() override { return Real()->m_iszTarget6(); }
    void Target6Updated() override { Real()->m_iszTarget6.NetworkStateChanged(); }
    CUtlSymbolLarge& Target7() override { return Real()->m_iszTarget7(); }
    void Target7Updated() override { Real()->m_iszTarget7.NetworkStateChanged(); }
    CUtlSymbolLarge& Target8() override { return Real()->m_iszTarget8(); }
    void Target8Updated() override { Real()->m_iszTarget8.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Target1() override { return Real()->m_hTarget1(); }
    void Target1Updated() override { Real()->m_hTarget1.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Target2() override { return Real()->m_hTarget2(); }
    void Target2Updated() override { Real()->m_hTarget2.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Target3() override { return Real()->m_hTarget3(); }
    void Target3Updated() override { Real()->m_hTarget3.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Target4() override { return Real()->m_hTarget4(); }
    void Target4Updated() override { Real()->m_hTarget4.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Target5() override { return Real()->m_hTarget5(); }
    void Target5Updated() override { Real()->m_hTarget5.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Target6() override { return Real()->m_hTarget6(); }
    void Target6Updated() override { Real()->m_hTarget6.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Target7() override { return Real()->m_hTarget7(); }
    void Target7Updated() override { Real()->m_hTarget7.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Target8() override { return Real()->m_hTarget8(); }
    void Target8Updated() override { Real()->m_hTarget8.NetworkStateChanged(); }
    CHandle<CBaseEntity>& LocatorOrigin() override { return Real()->m_hLocatorOrigin(); }
    void LocatorOriginUpdated() override { Real()->m_hLocatorOrigin.NetworkStateChanged(); }
    CUtlSymbolLarge& TargetAttachment() override { return Real()->m_sTargetAttachment(); }
    void TargetAttachmentUpdated() override { Real()->m_sTargetAttachment.NetworkStateChanged(); }
    bool& IsPlayingBack() override { return Real()->m_bIsPlayingBack(); }
    void IsPlayingBackUpdated() override { Real()->m_bIsPlayingBack.NetworkStateChanged(); }
    bool& Paused() override { return Real()->m_bPaused(); }
    void PausedUpdated() override { Real()->m_bPaused.NetworkStateChanged(); }
    bool& Multiplayer() override { return Real()->m_bMultiplayer(); }
    void MultiplayerUpdated() override { Real()->m_bMultiplayer.NetworkStateChanged(); }
    bool& Autogenerated() override { return Real()->m_bAutogenerated(); }
    void AutogeneratedUpdated() override { Real()->m_bAutogenerated.NetworkStateChanged(); }
    bool& AllRequirementsComplete() override { return Real()->m_bAllRequirementsComplete(); }
    void AllRequirementsCompleteUpdated() override { Real()->m_bAllRequirementsComplete.NetworkStateChanged(); }
    float& ForceClientTime() override { return Real()->m_flForceClientTime(); }
    void ForceClientTimeUpdated() override { Real()->m_flForceClientTime.NetworkStateChanged(); }
    float& CurrentTime() override { return Real()->m_flCurrentTime(); }
    void CurrentTimeUpdated() override { Real()->m_flCurrentTime.NetworkStateChanged(); }
    float& FrameTime() override { return Real()->m_flFrameTime(); }
    void FrameTimeUpdated() override { Real()->m_flFrameTime.NetworkStateChanged(); }
    bool& CancelAtNextInterrupt() override { return Real()->m_bCancelAtNextInterrupt(); }
    void CancelAtNextInterruptUpdated() override { Real()->m_bCancelAtNextInterrupt.NetworkStateChanged(); }
    float& Pitch() override { return Real()->m_fPitch(); }
    void PitchUpdated() override { Real()->m_fPitch.NetworkStateChanged(); }
    bool& Automated() override { return Real()->m_bAutomated(); }
    void AutomatedUpdated() override { Real()->m_bAutomated.NetworkStateChanged(); }
    int32_t& AutomatedAction() override { return Real()->m_nAutomatedAction(); }
    void AutomatedActionUpdated() override { Real()->m_nAutomatedAction.NetworkStateChanged(); }
    float& AutomationDelay() override { return Real()->m_flAutomationDelay(); }
    void AutomationDelayUpdated() override { Real()->m_flAutomationDelay.NetworkStateChanged(); }
    float& AutomationTime() override { return Real()->m_flAutomationTime(); }
    void AutomationTimeUpdated() override { Real()->m_flAutomationTime.NetworkStateChanged(); }
    int32_t& SpeechPriority() override { return Real()->m_nSpeechPriority(); }
    void SpeechPriorityUpdated() override { Real()->m_nSpeechPriority.NetworkStateChanged(); }
    bool& PausedViaInput() override { return Real()->m_bPausedViaInput(); }
    void PausedViaInputUpdated() override { Real()->m_bPausedViaInput.NetworkStateChanged(); }
    bool& PauseAtNextInterrupt() override { return Real()->m_bPauseAtNextInterrupt(); }
    void PauseAtNextInterruptUpdated() override { Real()->m_bPauseAtNextInterrupt.NetworkStateChanged(); }
    bool& WaitingForActor() override { return Real()->m_bWaitingForActor(); }
    void WaitingForActorUpdated() override { Real()->m_bWaitingForActor.NetworkStateChanged(); }
    bool& WaitingForInterrupt() override { return Real()->m_bWaitingForInterrupt(); }
    void WaitingForInterruptUpdated() override { Real()->m_bWaitingForInterrupt.NetworkStateChanged(); }
    bool& InterruptedActorsScenes() override { return Real()->m_bInterruptedActorsScenes(); }
    void InterruptedActorsScenesUpdated() override { Real()->m_bInterruptedActorsScenes.NetworkStateChanged(); }
    bool& TakeOverNPCBehavior() override { return Real()->m_bTakeOverNPCBehavior(); }
    void TakeOverNPCBehaviorUpdated() override { Real()->m_bTakeOverNPCBehavior.NetworkStateChanged(); }
    bool& BreakOnNonIdle() override { return Real()->m_bBreakOnNonIdle(); }
    void BreakOnNonIdleUpdated() override { Real()->m_bBreakOnNonIdle.NetworkStateChanged(); }
    bool& SceneFinished() override { return Real()->m_bSceneFinished(); }
    void SceneFinishedUpdated() override { Real()->m_bSceneFinished.NetworkStateChanged(); }
    CUtlVector<CHandle<CBaseModelEntity>>& ActorList() override { return Real()->m_hActorList(); }
    void ActorListUpdated() override { Real()->m_hActorList.NetworkStateChanged(); }
    CUtlVector<CHandle<CBaseEntity>>& RemoveActorList() override { return Real()->m_hRemoveActorList(); }
    void RemoveActorListUpdated() override { Real()->m_hRemoveActorList.NetworkStateChanged(); }
    uint16_t& SceneStringIndex() override { return Real()->m_nSceneStringIndex(); }
    void SceneStringIndexUpdated() override { Real()->m_nSceneStringIndex.NetworkStateChanged(); }
    CEntityIOOutput& OnStart() override { return Real()->m_OnStart(); }
    void OnStartUpdated() override { Real()->m_OnStart.NetworkStateChanged(); }
    CEntityIOOutput& OnCompletion() override { return Real()->m_OnCompletion(); }
    void OnCompletionUpdated() override { Real()->m_OnCompletion.NetworkStateChanged(); }
    CEntityIOOutput& OnCanceled() override { return Real()->m_OnCanceled(); }
    void OnCanceledUpdated() override { Real()->m_OnCanceled.NetworkStateChanged(); }
    CEntityIOOutput& OnPaused() override { return Real()->m_OnPaused(); }
    void OnPausedUpdated() override { Real()->m_OnPaused.NetworkStateChanged(); }
    CEntityIOOutput& OnResumed() override { return Real()->m_OnResumed(); }
    void OnResumedUpdated() override { Real()->m_OnResumed.NetworkStateChanged(); }
    CEntityIOOutput& OnPulseRequirement() override { return Real()->m_OnPulseRequirement(); }
    void OnPulseRequirementUpdated() override { Real()->m_OnPulseRequirement.NetworkStateChanged(); }
    CHandle<CSceneEntity>& InterruptScene() override { return Real()->m_hInterruptScene(); }
    void InterruptSceneUpdated() override { Real()->m_hInterruptScene.NetworkStateChanged(); }
    int32_t& InterruptCount() override { return Real()->m_nInterruptCount(); }
    void InterruptCountUpdated() override { Real()->m_nInterruptCount.NetworkStateChanged(); }
    bool& SceneMissing() override { return Real()->m_bSceneMissing(); }
    void SceneMissingUpdated() override { Real()->m_bSceneMissing.NetworkStateChanged(); }
    bool& Interrupted() override { return Real()->m_bInterrupted(); }
    void InterruptedUpdated() override { Real()->m_bInterrupted.NetworkStateChanged(); }
    bool& CompletedEarly() override { return Real()->m_bCompletedEarly(); }
    void CompletedEarlyUpdated() override { Real()->m_bCompletedEarly.NetworkStateChanged(); }
    bool& InterruptSceneFinished() override { return Real()->m_bInterruptSceneFinished(); }
    void InterruptSceneFinishedUpdated() override { Real()->m_bInterruptSceneFinished.NetworkStateChanged(); }
    bool& Restoring() override { return Real()->m_bRestoring(); }
    void RestoringUpdated() override { Real()->m_bRestoring.NetworkStateChanged(); }
    CUtlVector<CHandle<CSceneEntity>>& NotifySceneCompletion() override { return Real()->m_hNotifySceneCompletion(); }
    void NotifySceneCompletionUpdated() override { Real()->m_hNotifySceneCompletion.NetworkStateChanged(); }
    CUtlVector<CHandle<CSceneListManager>>& ListManagers() override { return Real()->m_hListManagers(); }
    void ListManagersUpdated() override { Real()->m_hListManagers.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundName() override { return Real()->m_iszSoundName(); }
    void SoundNameUpdated() override { Real()->m_iszSoundName.NetworkStateChanged(); }
    CUtlSymbolLarge& SequenceName() override { return Real()->m_iszSequenceName(); }
    void SequenceNameUpdated() override { Real()->m_iszSequenceName.NetworkStateChanged(); }
    CHandle<CBaseModelEntity>& Actor() override { return Real()->m_hActor(); }
    void ActorUpdated() override { Real()->m_hActor.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Activator() override { return Real()->m_hActivator(); }
    void ActivatorUpdated() override { Real()->m_hActivator.NetworkStateChanged(); }
    int32_t& BusyActor() override { return Real()->m_BusyActor(); }
    void BusyActorUpdated() override { Real()->m_BusyActor.NetworkStateChanged(); }
    SceneOnPlayerDeath_t& PlayerDeathBehavior() override { return Real()->m_iPlayerDeathBehavior(); }
    void PlayerDeathBehaviorUpdated() override { Real()->m_iPlayerDeathBehavior.NetworkStateChanged(); }
};

#endif // _INCLUDE_CSCENEENTITYIMPL_H
