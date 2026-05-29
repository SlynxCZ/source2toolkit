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

#ifndef _INCLUDE_CAI_EXPRESSERIMPL_H
#define _INCLUDE_CAI_EXPRESSERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IAI_Expresser.h"
#include "schema/entity/classes/CAI_Expresser.h"

class CAI_ExpresserImpl : public virtual IAI_Expresser
{

protected:
    void* m_pReal;

public:
    explicit CAI_ExpresserImpl(void* p) : m_pReal(p) {}

private:
    CAI_Expresser* Real() { return static_cast<CAI_Expresser*>(m_pReal); }
    CAI_Expresser* Real() const { return static_cast<CAI_Expresser*>(m_pReal); }

public:
    CAI_Expresser* GetOriginal() const override { return Real(); }
    float& StopTalkTime() override { return Real()->m_flStopTalkTime(); }
    void StopTalkTimeUpdated() override { Real()->m_flStopTalkTime.NetworkStateChanged(); }
    float& StopTalkTimeWithoutDelay() override { return Real()->m_flStopTalkTimeWithoutDelay(); }
    void StopTalkTimeWithoutDelayUpdated() override { Real()->m_flStopTalkTimeWithoutDelay.NetworkStateChanged(); }
    float& QueuedSpeechTime() override { return Real()->m_flQueuedSpeechTime(); }
    void QueuedSpeechTimeUpdated() override { Real()->m_flQueuedSpeechTime.NetworkStateChanged(); }
    float& BlockedTalkTime() override { return Real()->m_flBlockedTalkTime(); }
    void BlockedTalkTimeUpdated() override { Real()->m_flBlockedTalkTime.NetworkStateChanged(); }
    int32_t& VoicePitch() override { return Real()->m_voicePitch(); }
    void VoicePitchUpdated() override { Real()->m_voicePitch.NetworkStateChanged(); }
    float& LastTimeAcceptedSpeak() override { return Real()->m_flLastTimeAcceptedSpeak(); }
    void LastTimeAcceptedSpeakUpdated() override { Real()->m_flLastTimeAcceptedSpeak.NetworkStateChanged(); }
    bool& AllowSpeakingInterrupts() override { return Real()->m_bAllowSpeakingInterrupts(); }
    void AllowSpeakingInterruptsUpdated() override { Real()->m_bAllowSpeakingInterrupts.NetworkStateChanged(); }
    bool& ConsiderSceneInvolvementAsSpeech() override { return Real()->m_bConsiderSceneInvolvementAsSpeech(); }
    void ConsiderSceneInvolvementAsSpeechUpdated() override { Real()->m_bConsiderSceneInvolvementAsSpeech.NetworkStateChanged(); }
    bool& SceneEntityDisabled() override { return Real()->m_bSceneEntityDisabled(); }
    void SceneEntityDisabledUpdated() override { Real()->m_bSceneEntityDisabled.NetworkStateChanged(); }
    int32_t& LastSpokenPriority() override { return Real()->m_nLastSpokenPriority(); }
    void LastSpokenPriorityUpdated() override { Real()->m_nLastSpokenPriority.NetworkStateChanged(); }
    CBaseModelEntity*& Outer() override { return Real()->m_pOuter(); }
    void OuterUpdated() override { Real()->m_pOuter.NetworkStateChanged(); }
};

inline IAI_Expresser* CAI_Expresser::ToInterface() { return new CAI_ExpresserImpl(this); }
inline IAI_Expresser* IAI_Expresser::FromOriginal(CAI_Expresser* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CAI_EXPRESSERIMPL_H
