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

#ifndef _INCLUDE_CBASEANIMGRAPHCONTROLLERIMPL_H
#define _INCLUDE_CBASEANIMGRAPHCONTROLLERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBaseAnimGraphController.h"
#include "schema/entity/classes/CBaseAnimGraphController.h"
#include "CSkeletonAnimationControllerImpl.h"

class CBaseAnimGraphControllerImpl : public CSkeletonAnimationControllerImpl, public IBaseAnimGraphController
{

public:
    explicit CBaseAnimGraphControllerImpl(CBaseAnimGraphController* p) : CSkeletonAnimationControllerImpl(p) {}

private:
    CBaseAnimGraphController* Real() { return static_cast<CBaseAnimGraphController*>(m_pReal); }
    CBaseAnimGraphController* Real() const { return static_cast<CBaseAnimGraphController*>(m_pReal); }

public:
    CBaseAnimGraphController* GetOriginal() const override { return Real(); }
    ::AnimationAlgorithm_t& AnimationAlgorithm() override { return Real()->m_nAnimationAlgorithm(); }
    void AnimationAlgorithmUpdated() override { Real()->m_nAnimationAlgorithm.NetworkStateChanged(); }
    ::ExternalAnimGraphHandle_t& NextExternalGraphHandle() override { return Real()->m_nNextExternalGraphHandle(); }
    void NextExternalGraphHandleUpdated() override { Real()->m_nNextExternalGraphHandle.NetworkStateChanged(); }
    CUtlVector<CGlobalSymbol>& SecondarySkeletonSlotIDs() override { return Real()->m_vecSecondarySkeletonSlotIDs(); }
    void SecondarySkeletonSlotIDsUpdated() override { Real()->m_vecSecondarySkeletonSlotIDs.NetworkStateChanged(); }
    CUtlVector<CHandle<CBaseAnimGraph>>& SecondarySkeletons() override { return Real()->m_vecSecondarySkeletons(); }
    void SecondarySkeletonsUpdated() override { Real()->m_vecSecondarySkeletons.NetworkStateChanged(); }
    int32_t& SecondarySkeletonMasterCount() override { return Real()->m_nSecondarySkeletonMasterCount(); }
    void SecondarySkeletonMasterCountUpdated() override { Real()->m_nSecondarySkeletonMasterCount.NetworkStateChanged(); }
    float& SoundSyncTime() override { return Real()->m_flSoundSyncTime(); }
    void SoundSyncTimeUpdated() override { Real()->m_flSoundSyncTime.NetworkStateChanged(); }
    uint32_t& ActiveIKChainMask() override { return Real()->m_nActiveIKChainMask(); }
    void ActiveIKChainMaskUpdated() override { Real()->m_nActiveIKChainMask.NetworkStateChanged(); }
    int32_t& Sequence() override { return Real()->m_hSequence(); }
    void SequenceUpdated() override { Real()->m_hSequence.NetworkStateChanged(); }
    float& SeqStartTime() override { return Real()->m_flSeqStartTime(); }
    void SeqStartTimeUpdated() override { Real()->m_flSeqStartTime.NetworkStateChanged(); }
    float& SeqFixedCycle() override { return Real()->m_flSeqFixedCycle(); }
    void SeqFixedCycleUpdated() override { Real()->m_flSeqFixedCycle.NetworkStateChanged(); }
    ::AnimLoopMode_t& AnimLoopMode() override { return Real()->m_nAnimLoopMode(); }
    void AnimLoopModeUpdated() override { Real()->m_nAnimLoopMode.NetworkStateChanged(); }
    float& PlaybackRate() override { return Real()->m_flPlaybackRate(); }
    void PlaybackRateUpdated() override { Real()->m_flPlaybackRate.NetworkStateChanged(); }
    ::SequenceFinishNotifyState_t& NotifyState() override { return Real()->m_nNotifyState(); }
    void NotifyStateUpdated() override { Real()->m_nNotifyState.NetworkStateChanged(); }
    bool& NetworkedAnimationInputsChanged() override { return Real()->m_bNetworkedAnimationInputsChanged(); }
    void NetworkedAnimationInputsChangedUpdated() override { Real()->m_bNetworkedAnimationInputsChanged.NetworkStateChanged(); }
    bool& NetworkedSequenceChanged() override { return Real()->m_bNetworkedSequenceChanged(); }
    void NetworkedSequenceChangedUpdated() override { Real()->m_bNetworkedSequenceChanged.NetworkStateChanged(); }
    bool& LastUpdateSkipped() override { return Real()->m_bLastUpdateSkipped(); }
    void LastUpdateSkippedUpdated() override { Real()->m_bLastUpdateSkipped.NetworkStateChanged(); }
    bool& SequenceFinished() override { return Real()->m_bSequenceFinished(); }
    void SequenceFinishedUpdated() override { Real()->m_bSequenceFinished.NetworkStateChanged(); }
    int32_t& PrevAnimUpdateTick() override { return Real()->m_nPrevAnimUpdateTick(); }
    void PrevAnimUpdateTickUpdated() override { Real()->m_nPrevAnimUpdateTick.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCNmGraphDefinition>& GraphDefinitionAG2() override { return Real()->m_hGraphDefinitionAG2(); }
    void GraphDefinitionAG2Updated() override { Real()->m_hGraphDefinitionAG2.NetworkStateChanged(); }
    CUtlVector<AnimGraph2SerializedPoseRecipeSlot_t>& SerializePoseRecipeAG2Slots() override { return Real()->m_SerializePoseRecipeAG2Slots(); }
    void SerializePoseRecipeAG2SlotsUpdated() override { Real()->m_SerializePoseRecipeAG2Slots.NetworkStateChanged(); }
    CUtlVector<uint8_t>& SerializePoseRecipeAG2Dynamic() override { return Real()->m_SerializePoseRecipeAG2Dynamic(); }
    void SerializePoseRecipeAG2DynamicUpdated() override { Real()->m_SerializePoseRecipeAG2Dynamic.NetworkStateChanged(); }
    uint32_t& SerializePoseRecipeAG2ActiveSlot() override { return Real()->m_nSerializePoseRecipeAG2ActiveSlot(); }
    void SerializePoseRecipeAG2ActiveSlotUpdated() override { Real()->m_nSerializePoseRecipeAG2ActiveSlot.NetworkStateChanged(); }
    int32_t& SerializePoseRecipeVersionAG2() override { return Real()->m_nSerializePoseRecipeVersionAG2(); }
    void SerializePoseRecipeVersionAG2Updated() override { Real()->m_nSerializePoseRecipeVersionAG2.NetworkStateChanged(); }
    int32_t& ServerGraphInstanceIteration() override { return Real()->m_nServerGraphInstanceIteration(); }
    void ServerGraphInstanceIterationUpdated() override { Real()->m_nServerGraphInstanceIteration.NetworkStateChanged(); }
    int32_t& ServerSerializationContextIteration() override { return Real()->m_nServerSerializationContextIteration(); }
    void ServerSerializationContextIterationUpdated() override { Real()->m_nServerSerializationContextIteration.NetworkStateChanged(); }
    ::ResourceId_t& PrimaryGraphId() override { return Real()->m_primaryGraphId(); }
    void PrimaryGraphIdUpdated() override { Real()->m_primaryGraphId.NetworkStateChanged(); }
    CUtlVector<ResourceId_t>& ExternalGraphIds() override { return Real()->m_vecExternalGraphIds(); }
    void ExternalGraphIdsUpdated() override { Real()->m_vecExternalGraphIds.NetworkStateChanged(); }
    CUtlVector<ResourceId_t>& ExternalClipIds() override { return Real()->m_vecExternalClipIds(); }
    void ExternalClipIdsUpdated() override { Real()->m_vecExternalClipIds.NetworkStateChanged(); }
    CGlobalSymbol& AnimGraph2Identifier() override { return Real()->m_sAnimGraph2Identifier(); }
    void AnimGraph2IdentifierUpdated() override { Real()->m_sAnimGraph2Identifier.NetworkStateChanged(); }
    CNmGraphInstance*& GraphInstanceAG2() override { return Real()->m_pGraphInstanceAG2(); }
    void GraphInstanceAG2Updated() override { Real()->m_pGraphInstanceAG2.NetworkStateChanged(); }
    CUtlVector<ExternalAnimGraph_t>& ExternalGraphs() override { return Real()->m_vecExternalGraphs(); }
    void ExternalGraphsUpdated() override { Real()->m_vecExternalGraphs.NetworkStateChanged(); }
};

inline IBaseAnimGraphController* CBaseAnimGraphController::ToInterface() { return new CBaseAnimGraphControllerImpl(this); }
inline IBaseAnimGraphController* IBaseAnimGraphController::FromOriginal(CBaseAnimGraphController* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBASEANIMGRAPHCONTROLLERIMPL_H
