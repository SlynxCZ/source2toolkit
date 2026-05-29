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

#ifndef _INCLUDE_CBASEPLAYERCONTROLLERIMPL_H
#define _INCLUDE_CBASEPLAYERCONTROLLERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBasePlayerController.h"
#include "schema/entity/classes/CBasePlayerController.h"
#include "CBaseEntityImpl.h"

class CBasePlayerControllerImpl : public CBaseEntityImpl, public IBasePlayerController
{

public:
    explicit CBasePlayerControllerImpl(CBasePlayerController* p) : CBaseEntityImpl(p) {}

private:
    CBasePlayerController* Real() { return static_cast<CBasePlayerController*>(m_pReal); }
    CBasePlayerController* Real() const { return static_cast<CBasePlayerController*>(m_pReal); }

public:
    CBasePlayerController* GetOriginal() const override { return Real(); }
    uint64_t& InButtonsWhichAreToggles() override { return Real()->m_nInButtonsWhichAreToggles(); }
    void InButtonsWhichAreTogglesUpdated() override { Real()->m_nInButtonsWhichAreToggles.NetworkStateChanged(); }
    uint32_t& TickBase() override { return Real()->m_nTickBase(); }
    void TickBaseUpdated() override { Real()->m_nTickBase.NetworkStateChanged(); }
    CHandle<CBasePlayerPawn>& Pawn() override { return Real()->m_hPawn(); }
    void PawnUpdated() override { Real()->m_hPawn.NetworkStateChanged(); }
    bool& KnownTeamMismatch() override { return Real()->m_bKnownTeamMismatch(); }
    void KnownTeamMismatchUpdated() override { Real()->m_bKnownTeamMismatch.NetworkStateChanged(); }
    int32_t& SplitScreenSlot() override { return Real()->m_nSplitScreenSlot(); }
    void SplitScreenSlotUpdated() override { Real()->m_nSplitScreenSlot.NetworkStateChanged(); }
    CHandle<CBasePlayerController>& SplitOwner() override { return Real()->m_hSplitOwner(); }
    void SplitOwnerUpdated() override { Real()->m_hSplitOwner.NetworkStateChanged(); }
    CUtlVector<CHandle<CBasePlayerController>>& SplitScreenPlayers() override { return Real()->m_hSplitScreenPlayers(); }
    void SplitScreenPlayersUpdated() override { Real()->m_hSplitScreenPlayers.NetworkStateChanged(); }
    bool& IsHLTV() override { return Real()->m_bIsHLTV(); }
    void IsHLTVUpdated() override { Real()->m_bIsHLTV.NetworkStateChanged(); }
    ::PlayerConnectedState& Connected() override { return Real()->m_iConnected(); }
    void ConnectedUpdated() override { Real()->m_iConnected.NetworkStateChanged(); }
    ::PlayerConnectedState& MostConnected() override { return Real()->m_iMostConnected(); }
    void MostConnectedUpdated() override { Real()->m_iMostConnected.NetworkStateChanged(); }
    char* PlayerName() override { return Real()->m_iszPlayerName(); }
    CUtlString& NetworkIDString() override { return Real()->m_szNetworkIDString(); }
    void NetworkIDStringUpdated() override { Real()->m_szNetworkIDString.NetworkStateChanged(); }
    float& LerpTime() override { return Real()->m_fLerpTime(); }
    void LerpTimeUpdated() override { Real()->m_fLerpTime.NetworkStateChanged(); }
    bool& LagCompensation() override { return Real()->m_bLagCompensation(); }
    void LagCompensationUpdated() override { Real()->m_bLagCompensation.NetworkStateChanged(); }
    bool& Predict() override { return Real()->m_bPredict(); }
    void PredictUpdated() override { Real()->m_bPredict.NetworkStateChanged(); }
    bool& IsLowViolence() override { return Real()->m_bIsLowViolence(); }
    void IsLowViolenceUpdated() override { Real()->m_bIsLowViolence.NetworkStateChanged(); }
    bool& GamePaused() override { return Real()->m_bGamePaused(); }
    void GamePausedUpdated() override { Real()->m_bGamePaused.NetworkStateChanged(); }
    ::ChatIgnoreType_t& IgnoreGlobalChat() override { return Real()->m_iIgnoreGlobalChat(); }
    void IgnoreGlobalChatUpdated() override { Real()->m_iIgnoreGlobalChat.NetworkStateChanged(); }
    float& LastPlayerTalkTime() override { return Real()->m_flLastPlayerTalkTime(); }
    void LastPlayerTalkTimeUpdated() override { Real()->m_flLastPlayerTalkTime.NetworkStateChanged(); }
    float& LastEntitySteadyState() override { return Real()->m_flLastEntitySteadyState(); }
    void LastEntitySteadyStateUpdated() override { Real()->m_flLastEntitySteadyState.NetworkStateChanged(); }
    int32_t& AvailableEntitySteadyState() override { return Real()->m_nAvailableEntitySteadyState(); }
    void AvailableEntitySteadyStateUpdated() override { Real()->m_nAvailableEntitySteadyState.NetworkStateChanged(); }
    bool& HasAnySteadyStateEnts() override { return Real()->m_bHasAnySteadyStateEnts(); }
    void HasAnySteadyStateEntsUpdated() override { Real()->m_bHasAnySteadyStateEnts.NetworkStateChanged(); }
    uint64_t& SteamID() override { return Real()->m_steamID(); }
    void SteamIDUpdated() override { Real()->m_steamID.NetworkStateChanged(); }
    bool& NoClipEnabled() override { return Real()->m_bNoClipEnabled(); }
    void NoClipEnabledUpdated() override { Real()->m_bNoClipEnabled.NetworkStateChanged(); }
    uint32_t& DesiredFOV() override { return Real()->m_iDesiredFOV(); }
    void DesiredFOVUpdated() override { Real()->m_iDesiredFOV.NetworkStateChanged(); }

    void SetPawn(IBasePlayerPawn* pPawn) override { Real()->SetPawn(pPawn); }
};

#endif // _INCLUDE_CBASEPLAYERCONTROLLERIMPL_H
