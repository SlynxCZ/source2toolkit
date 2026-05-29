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

#ifndef _INCLUDE_CCSPLAYERCONTROLLERIMPL_H
#define _INCLUDE_CCSPLAYERCONTROLLERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayerController.h"
#include "schema/entity/classes/CCSPlayerController.h"
#include "CBasePlayerControllerImpl.h"

class CCSPlayerControllerImpl : public CBasePlayerControllerImpl, public ICSPlayerController
{

public:
    explicit CCSPlayerControllerImpl(CCSPlayerController* p) : CBasePlayerControllerImpl(p) {}

private:
    CCSPlayerController* Real() { return static_cast<CCSPlayerController*>(m_pReal); }
    CCSPlayerController* Real() const { return static_cast<CCSPlayerController*>(m_pReal); }

public:
    CCSPlayerController* GetOriginal() const override { return Real(); }
    CCSPlayerController_InGameMoneyServices*& InGameMoneyServices() override { return Real()->m_pInGameMoneyServices(); }
    void InGameMoneyServicesUpdated() override { Real()->m_pInGameMoneyServices.NetworkStateChanged(); }
    CCSPlayerController_InventoryServices*& InventoryServices() override { return Real()->m_pInventoryServices(); }
    void InventoryServicesUpdated() override { Real()->m_pInventoryServices.NetworkStateChanged(); }
    CCSPlayerController_ActionTrackingServices*& ActionTrackingServices() override { return Real()->m_pActionTrackingServices(); }
    void ActionTrackingServicesUpdated() override { Real()->m_pActionTrackingServices.NetworkStateChanged(); }
    CCSPlayerController_DamageServices*& DamageServices() override { return Real()->m_pDamageServices(); }
    void DamageServicesUpdated() override { Real()->m_pDamageServices.NetworkStateChanged(); }
    uint32_t& Ping() override { return Real()->m_iPing(); }
    void PingUpdated() override { Real()->m_iPing.NetworkStateChanged(); }
    bool& HasCommunicationAbuseMute() override { return Real()->m_bHasCommunicationAbuseMute(); }
    void HasCommunicationAbuseMuteUpdated() override { Real()->m_bHasCommunicationAbuseMute.NetworkStateChanged(); }
    uint32_t& UiCommunicationMuteFlags() override { return Real()->m_uiCommunicationMuteFlags(); }
    void UiCommunicationMuteFlagsUpdated() override { Real()->m_uiCommunicationMuteFlags.NetworkStateChanged(); }
    CUtlSymbolLarge& CrosshairCodes() override { return Real()->m_szCrosshairCodes(); }
    void CrosshairCodesUpdated() override { Real()->m_szCrosshairCodes.NetworkStateChanged(); }
    uint8_t& PendingTeamNum() override { return Real()->m_iPendingTeamNum(); }
    void PendingTeamNumUpdated() override { Real()->m_iPendingTeamNum.NetworkStateChanged(); }
    float& ForceTeamTime() override { return Real()->m_flForceTeamTime(); }
    void ForceTeamTimeUpdated() override { Real()->m_flForceTeamTime.NetworkStateChanged(); }
    int32_t& CompTeammateColor() override { return Real()->m_iCompTeammateColor(); }
    void CompTeammateColorUpdated() override { Real()->m_iCompTeammateColor.NetworkStateChanged(); }
    bool& EverPlayedOnTeam() override { return Real()->m_bEverPlayedOnTeam(); }
    void EverPlayedOnTeamUpdated() override { Real()->m_bEverPlayedOnTeam.NetworkStateChanged(); }
    bool& AttemptedToGetColor() override { return Real()->m_bAttemptedToGetColor(); }
    void AttemptedToGetColorUpdated() override { Real()->m_bAttemptedToGetColor.NetworkStateChanged(); }
    int32_t& TeammatePreferredColor() override { return Real()->m_iTeammatePreferredColor(); }
    void TeammatePreferredColorUpdated() override { Real()->m_iTeammatePreferredColor.NetworkStateChanged(); }
    bool& TeamChanged() override { return Real()->m_bTeamChanged(); }
    void TeamChangedUpdated() override { Real()->m_bTeamChanged.NetworkStateChanged(); }
    bool& InSwitchTeam() override { return Real()->m_bInSwitchTeam(); }
    void InSwitchTeamUpdated() override { Real()->m_bInSwitchTeam.NetworkStateChanged(); }
    bool& HasSeenJoinGame() override { return Real()->m_bHasSeenJoinGame(); }
    void HasSeenJoinGameUpdated() override { Real()->m_bHasSeenJoinGame.NetworkStateChanged(); }
    bool& JustBecameSpectator() override { return Real()->m_bJustBecameSpectator(); }
    void JustBecameSpectatorUpdated() override { Real()->m_bJustBecameSpectator.NetworkStateChanged(); }
    bool& SwitchTeamsOnNextRoundReset() override { return Real()->m_bSwitchTeamsOnNextRoundReset(); }
    void SwitchTeamsOnNextRoundResetUpdated() override { Real()->m_bSwitchTeamsOnNextRoundReset.NetworkStateChanged(); }
    bool& RemoveAllItemsOnNextRoundReset() override { return Real()->m_bRemoveAllItemsOnNextRoundReset(); }
    void RemoveAllItemsOnNextRoundResetUpdated() override { Real()->m_bRemoveAllItemsOnNextRoundReset.NetworkStateChanged(); }
    float& LastJoinTeamTime() override { return Real()->m_flLastJoinTeamTime(); }
    void LastJoinTeamTimeUpdated() override { Real()->m_flLastJoinTeamTime.NetworkStateChanged(); }
    CUtlSymbolLarge& Clan() override { return Real()->m_szClan(); }
    void ClanUpdated() override { Real()->m_szClan.NetworkStateChanged(); }
    int32_t& CoachingTeam() override { return Real()->m_iCoachingTeam(); }
    void CoachingTeamUpdated() override { Real()->m_iCoachingTeam.NetworkStateChanged(); }
    uint64_t& PlayerDominated() override { return Real()->m_nPlayerDominated(); }
    void PlayerDominatedUpdated() override { Real()->m_nPlayerDominated.NetworkStateChanged(); }
    uint64_t& PlayerDominatingMe() override { return Real()->m_nPlayerDominatingMe(); }
    void PlayerDominatingMeUpdated() override { Real()->m_nPlayerDominatingMe.NetworkStateChanged(); }
    int32_t& CompetitiveRanking() override { return Real()->m_iCompetitiveRanking(); }
    void CompetitiveRankingUpdated() override { Real()->m_iCompetitiveRanking.NetworkStateChanged(); }
    int32_t& CompetitiveWins() override { return Real()->m_iCompetitiveWins(); }
    void CompetitiveWinsUpdated() override { Real()->m_iCompetitiveWins.NetworkStateChanged(); }
    int8_t& CompetitiveRankType() override { return Real()->m_iCompetitiveRankType(); }
    void CompetitiveRankTypeUpdated() override { Real()->m_iCompetitiveRankType.NetworkStateChanged(); }
    int32_t& CompetitiveRankingPredicted_Win() override { return Real()->m_iCompetitiveRankingPredicted_Win(); }
    void CompetitiveRankingPredicted_WinUpdated() override { Real()->m_iCompetitiveRankingPredicted_Win.NetworkStateChanged(); }
    int32_t& CompetitiveRankingPredicted_Loss() override { return Real()->m_iCompetitiveRankingPredicted_Loss(); }
    void CompetitiveRankingPredicted_LossUpdated() override { Real()->m_iCompetitiveRankingPredicted_Loss.NetworkStateChanged(); }
    int32_t& CompetitiveRankingPredicted_Tie() override { return Real()->m_iCompetitiveRankingPredicted_Tie(); }
    void CompetitiveRankingPredicted_TieUpdated() override { Real()->m_iCompetitiveRankingPredicted_Tie.NetworkStateChanged(); }
    int32_t& EndMatchNextMapVote() override { return Real()->m_nEndMatchNextMapVote(); }
    void EndMatchNextMapVoteUpdated() override { Real()->m_nEndMatchNextMapVote.NetworkStateChanged(); }
    uint16_t& ActiveQuestId() override { return Real()->m_unActiveQuestId(); }
    void ActiveQuestIdUpdated() override { Real()->m_unActiveQuestId.NetworkStateChanged(); }
    uint32_t& RtActiveMissionPeriod() override { return Real()->m_rtActiveMissionPeriod(); }
    void RtActiveMissionPeriodUpdated() override { Real()->m_rtActiveMissionPeriod.NetworkStateChanged(); }
    QuestProgress__Reason& QuestProgressReason() override { return Real()->m_nQuestProgressReason(); }
    void QuestProgressReasonUpdated() override { Real()->m_nQuestProgressReason.NetworkStateChanged(); }
    uint32_t& PlayerTvControlFlags() override { return Real()->m_unPlayerTvControlFlags(); }
    void PlayerTvControlFlagsUpdated() override { Real()->m_unPlayerTvControlFlags.NetworkStateChanged(); }
    int32_t& DraftIndex() override { return Real()->m_iDraftIndex(); }
    void DraftIndexUpdated() override { Real()->m_iDraftIndex.NetworkStateChanged(); }
    uint32_t& MsQueuedModeDisconnectionTimestamp() override { return Real()->m_msQueuedModeDisconnectionTimestamp(); }
    void MsQueuedModeDisconnectionTimestampUpdated() override { Real()->m_msQueuedModeDisconnectionTimestamp.NetworkStateChanged(); }
    uint32_t& UiAbandonRecordedReason() override { return Real()->m_uiAbandonRecordedReason(); }
    void UiAbandonRecordedReasonUpdated() override { Real()->m_uiAbandonRecordedReason.NetworkStateChanged(); }
    uint32_t& NetworkDisconnectionReason() override { return Real()->m_eNetworkDisconnectionReason(); }
    void NetworkDisconnectionReasonUpdated() override { Real()->m_eNetworkDisconnectionReason.NetworkStateChanged(); }
    bool& CannotBeKicked() override { return Real()->m_bCannotBeKicked(); }
    void CannotBeKickedUpdated() override { Real()->m_bCannotBeKicked.NetworkStateChanged(); }
    bool& EverFullyConnected() override { return Real()->m_bEverFullyConnected(); }
    void EverFullyConnectedUpdated() override { Real()->m_bEverFullyConnected.NetworkStateChanged(); }
    bool& AbandonAllowsSurrender() override { return Real()->m_bAbandonAllowsSurrender(); }
    void AbandonAllowsSurrenderUpdated() override { Real()->m_bAbandonAllowsSurrender.NetworkStateChanged(); }
    bool& AbandonOffersInstantSurrender() override { return Real()->m_bAbandonOffersInstantSurrender(); }
    void AbandonOffersInstantSurrenderUpdated() override { Real()->m_bAbandonOffersInstantSurrender.NetworkStateChanged(); }
    bool& Disconnection1MinWarningPrinted() override { return Real()->m_bDisconnection1MinWarningPrinted(); }
    void Disconnection1MinWarningPrintedUpdated() override { Real()->m_bDisconnection1MinWarningPrinted.NetworkStateChanged(); }
    bool& ScoreReported() override { return Real()->m_bScoreReported(); }
    void ScoreReportedUpdated() override { Real()->m_bScoreReported.NetworkStateChanged(); }
    int32_t& DisconnectionTick() override { return Real()->m_nDisconnectionTick(); }
    void DisconnectionTickUpdated() override { Real()->m_nDisconnectionTick.NetworkStateChanged(); }
    bool& ControllingBot() override { return Real()->m_bControllingBot(); }
    void ControllingBotUpdated() override { Real()->m_bControllingBot.NetworkStateChanged(); }
    bool& HasControlledBotThisRound() override { return Real()->m_bHasControlledBotThisRound(); }
    void HasControlledBotThisRoundUpdated() override { Real()->m_bHasControlledBotThisRound.NetworkStateChanged(); }
    bool& HasBeenControlledByPlayerThisRound() override { return Real()->m_bHasBeenControlledByPlayerThisRound(); }
    void HasBeenControlledByPlayerThisRoundUpdated() override { Real()->m_bHasBeenControlledByPlayerThisRound.NetworkStateChanged(); }
    int32_t& BotsControlledThisRound() override { return Real()->m_nBotsControlledThisRound(); }
    void BotsControlledThisRoundUpdated() override { Real()->m_nBotsControlledThisRound.NetworkStateChanged(); }
    bool& CanControlObservedBot() override { return Real()->m_bCanControlObservedBot(); }
    void CanControlObservedBotUpdated() override { Real()->m_bCanControlObservedBot.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& PlayerPawn() override { return Real()->m_hPlayerPawn(); }
    void PlayerPawnUpdated() override { Real()->m_hPlayerPawn.NetworkStateChanged(); }
    CHandle<CCSObserverPawn>& ObserverPawn() override { return Real()->m_hObserverPawn(); }
    void ObserverPawnUpdated() override { Real()->m_hObserverPawn.NetworkStateChanged(); }
    int32_t& DesiredObserverMode() override { return Real()->m_DesiredObserverMode(); }
    void DesiredObserverModeUpdated() override { Real()->m_DesiredObserverMode.NetworkStateChanged(); }
    CEntityHandle& DesiredObserverTarget() override { return Real()->m_hDesiredObserverTarget(); }
    void DesiredObserverTargetUpdated() override { Real()->m_hDesiredObserverTarget.NetworkStateChanged(); }
    bool& PawnIsAlive() override { return Real()->m_bPawnIsAlive(); }
    void PawnIsAliveUpdated() override { Real()->m_bPawnIsAlive.NetworkStateChanged(); }
    uint32_t& PawnHealth() override { return Real()->m_iPawnHealth(); }
    void PawnHealthUpdated() override { Real()->m_iPawnHealth.NetworkStateChanged(); }
    int32_t& PawnArmor() override { return Real()->m_iPawnArmor(); }
    void PawnArmorUpdated() override { Real()->m_iPawnArmor.NetworkStateChanged(); }
    bool& PawnHasDefuser() override { return Real()->m_bPawnHasDefuser(); }
    void PawnHasDefuserUpdated() override { Real()->m_bPawnHasDefuser.NetworkStateChanged(); }
    bool& PawnHasHelmet() override { return Real()->m_bPawnHasHelmet(); }
    void PawnHasHelmetUpdated() override { Real()->m_bPawnHasHelmet.NetworkStateChanged(); }
    uint16_t& PawnCharacterDefIndex() override { return Real()->m_nPawnCharacterDefIndex(); }
    void PawnCharacterDefIndexUpdated() override { Real()->m_nPawnCharacterDefIndex.NetworkStateChanged(); }
    int32_t& PawnLifetimeStart() override { return Real()->m_iPawnLifetimeStart(); }
    void PawnLifetimeStartUpdated() override { Real()->m_iPawnLifetimeStart.NetworkStateChanged(); }
    int32_t& PawnLifetimeEnd() override { return Real()->m_iPawnLifetimeEnd(); }
    void PawnLifetimeEndUpdated() override { Real()->m_iPawnLifetimeEnd.NetworkStateChanged(); }
    int32_t& PawnBotDifficulty() override { return Real()->m_iPawnBotDifficulty(); }
    void PawnBotDifficultyUpdated() override { Real()->m_iPawnBotDifficulty.NetworkStateChanged(); }
    CHandle<CCSPlayerController>& OriginalControllerOfCurrentPawn() override { return Real()->m_hOriginalControllerOfCurrentPawn(); }
    void OriginalControllerOfCurrentPawnUpdated() override { Real()->m_hOriginalControllerOfCurrentPawn.NetworkStateChanged(); }
    int32_t& Score() override { return Real()->m_iScore(); }
    void ScoreUpdated() override { Real()->m_iScore.NetworkStateChanged(); }
    int32_t& RoundScore() override { return Real()->m_iRoundScore(); }
    void RoundScoreUpdated() override { Real()->m_iRoundScore.NetworkStateChanged(); }
    int32_t& RoundsWon() override { return Real()->m_iRoundsWon(); }
    void RoundsWonUpdated() override { Real()->m_iRoundsWon.NetworkStateChanged(); }
    uint8_t* RecentKillQueue() override { return Real()->m_recentKillQueue(); }
    uint8_t& FirstKill() override { return Real()->m_nFirstKill(); }
    void FirstKillUpdated() override { Real()->m_nFirstKill.NetworkStateChanged(); }
    uint8_t& KillCount() override { return Real()->m_nKillCount(); }
    void KillCountUpdated() override { Real()->m_nKillCount.NetworkStateChanged(); }
    bool& MvpNoMusic() override { return Real()->m_bMvpNoMusic(); }
    void MvpNoMusicUpdated() override { Real()->m_bMvpNoMusic.NetworkStateChanged(); }
    int32_t& MvpReason() override { return Real()->m_eMvpReason(); }
    void MvpReasonUpdated() override { Real()->m_eMvpReason.NetworkStateChanged(); }
    int32_t& MusicKitID() override { return Real()->m_iMusicKitID(); }
    void MusicKitIDUpdated() override { Real()->m_iMusicKitID.NetworkStateChanged(); }
    int32_t& MusicKitMVPs() override { return Real()->m_iMusicKitMVPs(); }
    void MusicKitMVPsUpdated() override { Real()->m_iMusicKitMVPs.NetworkStateChanged(); }
    int32_t& MVPs() override { return Real()->m_iMVPs(); }
    void MVPsUpdated() override { Real()->m_iMVPs.NetworkStateChanged(); }
    int32_t& UpdateCounter() override { return Real()->m_nUpdateCounter(); }
    void UpdateCounterUpdated() override { Real()->m_nUpdateCounter.NetworkStateChanged(); }
    float& SmoothedPing() override { return Real()->m_flSmoothedPing(); }
    void SmoothedPingUpdated() override { Real()->m_flSmoothedPing.NetworkStateChanged(); }
    IntervalTimer& LastHeldVoteTimer() override { return Real()->m_lastHeldVoteTimer(); }
    void LastHeldVoteTimerUpdated() override { Real()->m_lastHeldVoteTimer.NetworkStateChanged(); }
    bool& ShowHints() override { return Real()->m_bShowHints(); }
    void ShowHintsUpdated() override { Real()->m_bShowHints.NetworkStateChanged(); }
    int32_t& NextTimeCheck() override { return Real()->m_iNextTimeCheck(); }
    void NextTimeCheckUpdated() override { Real()->m_iNextTimeCheck.NetworkStateChanged(); }
    bool& JustDidTeamKill() override { return Real()->m_bJustDidTeamKill(); }
    void JustDidTeamKillUpdated() override { Real()->m_bJustDidTeamKill.NetworkStateChanged(); }
    bool& PunishForTeamKill() override { return Real()->m_bPunishForTeamKill(); }
    void PunishForTeamKillUpdated() override { Real()->m_bPunishForTeamKill.NetworkStateChanged(); }
    bool& GaveTeamDamageWarning() override { return Real()->m_bGaveTeamDamageWarning(); }
    void GaveTeamDamageWarningUpdated() override { Real()->m_bGaveTeamDamageWarning.NetworkStateChanged(); }
    bool& GaveTeamDamageWarningThisRound() override { return Real()->m_bGaveTeamDamageWarningThisRound(); }
    void GaveTeamDamageWarningThisRoundUpdated() override { Real()->m_bGaveTeamDamageWarningThisRound.NetworkStateChanged(); }
    double& DblLastReceivedPacketPlatFloatTime() override { return Real()->m_dblLastReceivedPacketPlatFloatTime(); }
    void DblLastReceivedPacketPlatFloatTimeUpdated() override { Real()->m_dblLastReceivedPacketPlatFloatTime.NetworkStateChanged(); }
    float& LastTeamDamageWarningTime() override { return Real()->m_LastTeamDamageWarningTime(); }
    void LastTeamDamageWarningTimeUpdated() override { Real()->m_LastTeamDamageWarningTime.NetworkStateChanged(); }
    float& LastTimePlayerWasDisconnectedForPawnsRemove() override { return Real()->m_LastTimePlayerWasDisconnectedForPawnsRemove(); }
    void LastTimePlayerWasDisconnectedForPawnsRemoveUpdated() override { Real()->m_LastTimePlayerWasDisconnectedForPawnsRemove.NetworkStateChanged(); }
    uint32_t& SuspiciousHitCount() override { return Real()->m_nSuspiciousHitCount(); }
    void SuspiciousHitCountUpdated() override { Real()->m_nSuspiciousHitCount.NetworkStateChanged(); }
    uint32_t& NonSuspiciousHitStreak() override { return Real()->m_nNonSuspiciousHitStreak(); }
    void NonSuspiciousHitStreakUpdated() override { Real()->m_nNonSuspiciousHitStreak.NetworkStateChanged(); }
    bool& FireBulletsSeedSynchronized() override { return Real()->m_bFireBulletsSeedSynchronized(); }
    void FireBulletsSeedSynchronizedUpdated() override { Real()->m_bFireBulletsSeedSynchronized.NetworkStateChanged(); }

    void PrintToConsole(const char* pszMessage) override { Real()->PrintToConsole(pszMessage); }
    void PrintToChat(const char* pszMessage) override { Real()->PrintToChat(pszMessage); }
    void PrintToCenter(const char* pszMessage) override { Real()->PrintToCenter(pszMessage); }
    void PrintToCenterAlert(const char* pszMessage) override { Real()->PrintToCenterAlert(pszMessage); }
    void PrintToCenterHtml(const char* pszMessage, int iDuration) override { Real()->PrintToCenterHtml(pszMessage, iDuration); }
    void TakeDamage(ICSPlayerController* pAttacker, int iDamage, DamageTypes_t bitsDamageType) override { Real()->TakeDamage(pAttacker, iDamage, bitsDamageType); }
    void Respawn() override { Real()->Respawn(); }
    void SwitchTeam(int nTeam) override { Real()->SwitchTeam(nTeam); }
    void ChangeTeam(int nTeam) override { Real()->ChangeTeam(nTeam); }
    bool IsBot() override { return Real()->IsBot(); }
    void Disconnect(ENetworkDisconnectionReason eReason) override { Real()->Disconnect(eReason); }
    void ExecuteClientCommand(const char* pszCommand) override { Real()->ExecuteClientCommand(pszCommand); }
    void ExecuteClientCommandFromServer(const char* pszCommand) override { Real()->ExecuteClientCommandFromServer(pszCommand); }
    ICSPlayerPawn* GetPawn() override { return Real()->GetPawn(); }
    ICSPlayerPawn* GetPlayerPawn() override { return Real()->GetPlayerPawn(); }
    ICSObserverPawn* GetObserverPawn() override { return Real()->GetObserverPawn(); }
    CEntityIndex GetPlayerIndex() override { return Real()->GetPlayerIndex(); }
    int GetSlot() override { return Real()->GetSlot(); }
    CPlayerSlot GetPlayerSlot() override { return Real()->GetPlayerSlot(); }
    int GetUserID() override { return Real()->GetUserID(); }
    CPlayerUserId GetPlayerUserID() override { return Real()->GetPlayerUserID(); }
    uint64 GetSteamID() override { return Real()->GetSteamID(); }
    CSteamID GetPlayerSteamID() override { return Real()->GetPlayerSteamID(); }
    const char* GetPlayerName() override { return Real()->GetPlayerName(); }
    CUtlString GetIpAddress() override { return Real()->GetIpAddress(); }
    void ReplicateConVar(const char* pszConVar, const char* pszValue) override { Real()->ReplicateConVar(pszConVar, pszValue); }
    void FireEventToClient(IGameEvent* pEvent) override { Real()->FireEventToClient(pEvent); }
};

#endif // _INCLUDE_CCSPLAYERCONTROLLERIMPL_H
