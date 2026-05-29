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

#ifndef _INCLUDE_CPLANTEDC4IMPL_H
#define _INCLUDE_CPLANTEDC4IMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPlantedC4.h"
#include "schema/entity/classes/CPlantedC4.h"
#include "CBaseAnimGraphImpl.h"

class CPlantedC4Impl : public CBaseAnimGraphImpl, public IPlantedC4
{

public:
    explicit CPlantedC4Impl(CPlantedC4* p) : CBaseAnimGraphImpl(p) {}

private:
    CPlantedC4* Real() { return static_cast<CPlantedC4*>(m_pReal); }
    CPlantedC4* Real() const { return static_cast<CPlantedC4*>(m_pReal); }

public:
    CPlantedC4* GetOriginal() const override { return Real(); }
    bool& BombTicking() override { return Real()->m_bBombTicking(); }
    void BombTickingUpdated() override { Real()->m_bBombTicking.NetworkStateChanged(); }
    float& C4Blow() override { return Real()->m_flC4Blow(); }
    void C4BlowUpdated() override { Real()->m_flC4Blow.NetworkStateChanged(); }
    int32_t& BombSite() override { return Real()->m_nBombSite(); }
    void BombSiteUpdated() override { Real()->m_nBombSite.NetworkStateChanged(); }
    int32_t& SourceSoundscapeHash() override { return Real()->m_nSourceSoundscapeHash(); }
    void SourceSoundscapeHashUpdated() override { Real()->m_nSourceSoundscapeHash.NetworkStateChanged(); }
    bool& AbortDetonationBecauseWorldIsFrozen() override { return Real()->m_bAbortDetonationBecauseWorldIsFrozen(); }
    void AbortDetonationBecauseWorldIsFrozenUpdated() override { Real()->m_bAbortDetonationBecauseWorldIsFrozen.NetworkStateChanged(); }
    ::CAttributeContainer& AttributeManager() override { return Real()->m_AttributeManager(); }
    void AttributeManagerUpdated() override { Real()->m_AttributeManager.NetworkStateChanged(); }
    ::CEntityIOOutput& OnBombDefused() override { return Real()->m_OnBombDefused(); }
    void OnBombDefusedUpdated() override { Real()->m_OnBombDefused.NetworkStateChanged(); }
    ::CEntityIOOutput& OnBombBeginDefuse() override { return Real()->m_OnBombBeginDefuse(); }
    void OnBombBeginDefuseUpdated() override { Real()->m_OnBombBeginDefuse.NetworkStateChanged(); }
    ::CEntityIOOutput& OnBombDefuseAborted() override { return Real()->m_OnBombDefuseAborted(); }
    void OnBombDefuseAbortedUpdated() override { Real()->m_OnBombDefuseAborted.NetworkStateChanged(); }
    bool& CannotBeDefused() override { return Real()->m_bCannotBeDefused(); }
    void CannotBeDefusedUpdated() override { Real()->m_bCannotBeDefused.NetworkStateChanged(); }
    ::EntitySpottedState_t& EntitySpottedState() override { return Real()->m_entitySpottedState(); }
    void EntitySpottedStateUpdated() override { Real()->m_entitySpottedState.NetworkStateChanged(); }
    int32_t& SpotRules() override { return Real()->m_nSpotRules(); }
    void SpotRulesUpdated() override { Real()->m_nSpotRules.NetworkStateChanged(); }
    bool& HasExploded() override { return Real()->m_bHasExploded(); }
    void HasExplodedUpdated() override { Real()->m_bHasExploded.NetworkStateChanged(); }
    bool& BombDefused() override { return Real()->m_bBombDefused(); }
    void BombDefusedUpdated() override { Real()->m_bBombDefused.NetworkStateChanged(); }
    bool& TrainingPlacedByPlayer() override { return Real()->m_bTrainingPlacedByPlayer(); }
    void TrainingPlacedByPlayerUpdated() override { Real()->m_bTrainingPlacedByPlayer.NetworkStateChanged(); }
    float& TimerLength() override { return Real()->m_flTimerLength(); }
    void TimerLengthUpdated() override { Real()->m_flTimerLength.NetworkStateChanged(); }
    bool& BeingDefused() override { return Real()->m_bBeingDefused(); }
    void BeingDefusedUpdated() override { Real()->m_bBeingDefused.NetworkStateChanged(); }
    float& LastDefuseTime() override { return Real()->m_fLastDefuseTime(); }
    void LastDefuseTimeUpdated() override { Real()->m_fLastDefuseTime.NetworkStateChanged(); }
    float& DefuseLength() override { return Real()->m_flDefuseLength(); }
    void DefuseLengthUpdated() override { Real()->m_flDefuseLength.NetworkStateChanged(); }
    float& DefuseCountDown() override { return Real()->m_flDefuseCountDown(); }
    void DefuseCountDownUpdated() override { Real()->m_flDefuseCountDown.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& BombDefuser() override { return Real()->m_hBombDefuser(); }
    void BombDefuserUpdated() override { Real()->m_hBombDefuser.NetworkStateChanged(); }
    int32_t& ProgressBarTime() override { return Real()->m_iProgressBarTime(); }
    void ProgressBarTimeUpdated() override { Real()->m_iProgressBarTime.NetworkStateChanged(); }
    bool& VoiceAlertFired() override { return Real()->m_bVoiceAlertFired(); }
    void VoiceAlertFiredUpdated() override { Real()->m_bVoiceAlertFired.NetworkStateChanged(); }
    bool* VoiceAlertPlayed() override { return Real()->m_bVoiceAlertPlayed(); }
    float& NextBotBeepTime() override { return Real()->m_flNextBotBeepTime(); }
    void NextBotBeepTimeUpdated() override { Real()->m_flNextBotBeepTime.NetworkStateChanged(); }
    QAngle& CatchUpToPlayerEye() override { return Real()->m_angCatchUpToPlayerEye(); }
    void CatchUpToPlayerEyeUpdated() override { Real()->m_angCatchUpToPlayerEye.NetworkStateChanged(); }
    float& LastSpinDetectionTime() override { return Real()->m_flLastSpinDetectionTime(); }
    void LastSpinDetectionTimeUpdated() override { Real()->m_flLastSpinDetectionTime.NetworkStateChanged(); }
};

inline IPlantedC4* CPlantedC4::ToInterface() { return new CPlantedC4Impl(this); }
inline IPlantedC4* IPlantedC4::FromOriginal(CPlantedC4* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPLANTEDC4IMPL_H
