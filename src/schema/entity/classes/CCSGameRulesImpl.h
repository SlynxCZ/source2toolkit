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

#ifndef _INCLUDE_CCSGAMERULESIMPL_H
#define _INCLUDE_CCSGAMERULESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSGameRules.h"
#include "schema/entity/classes/CCSGameRules.h"

class CCSGameRulesImpl : public virtual ICSGameRules
{

protected:
    void* m_pReal;

public:
    explicit CCSGameRulesImpl(void* p) : m_pReal(p) {}

private:
    CCSGameRules* Real() { return static_cast<CCSGameRules*>(m_pReal); }
    CCSGameRules* Real() const { return static_cast<CCSGameRules*>(m_pReal); }

public:
    CCSGameRules* GetOriginal() const override { return Real(); }
    bool& FreezePeriod() override { return Real()->m_bFreezePeriod(); }
    void FreezePeriodUpdated() override { Real()->m_bFreezePeriod.NetworkStateChanged(); }
    bool& WarmupPeriod() override { return Real()->m_bWarmupPeriod(); }
    void WarmupPeriodUpdated() override { Real()->m_bWarmupPeriod.NetworkStateChanged(); }
    float& WarmupPeriodEnd() override { return Real()->m_fWarmupPeriodEnd(); }
    void WarmupPeriodEndUpdated() override { Real()->m_fWarmupPeriodEnd.NetworkStateChanged(); }
    float& WarmupPeriodStart() override { return Real()->m_fWarmupPeriodStart(); }
    void WarmupPeriodStartUpdated() override { Real()->m_fWarmupPeriodStart.NetworkStateChanged(); }
    bool& TerroristTimeOutActive() override { return Real()->m_bTerroristTimeOutActive(); }
    void TerroristTimeOutActiveUpdated() override { Real()->m_bTerroristTimeOutActive.NetworkStateChanged(); }
    bool& TTimeOutActive() override { return Real()->m_bCTTimeOutActive(); }
    void TTimeOutActiveUpdated() override { Real()->m_bCTTimeOutActive.NetworkStateChanged(); }
    float& TerroristTimeOutRemaining() override { return Real()->m_flTerroristTimeOutRemaining(); }
    void TerroristTimeOutRemainingUpdated() override { Real()->m_flTerroristTimeOutRemaining.NetworkStateChanged(); }
    float& TTimeOutRemaining() override { return Real()->m_flCTTimeOutRemaining(); }
    void TTimeOutRemainingUpdated() override { Real()->m_flCTTimeOutRemaining.NetworkStateChanged(); }
    int32_t& TerroristTimeOuts() override { return Real()->m_nTerroristTimeOuts(); }
    void TerroristTimeOutsUpdated() override { Real()->m_nTerroristTimeOuts.NetworkStateChanged(); }
    int32_t& TTimeOuts() override { return Real()->m_nCTTimeOuts(); }
    void TTimeOutsUpdated() override { Real()->m_nCTTimeOuts.NetworkStateChanged(); }
    bool& TechnicalTimeOut() override { return Real()->m_bTechnicalTimeOut(); }
    void TechnicalTimeOutUpdated() override { Real()->m_bTechnicalTimeOut.NetworkStateChanged(); }
    bool& MatchWaitingForResume() override { return Real()->m_bMatchWaitingForResume(); }
    void MatchWaitingForResumeUpdated() override { Real()->m_bMatchWaitingForResume.NetworkStateChanged(); }
    int32_t& FreezeTime() override { return Real()->m_iFreezeTime(); }
    void FreezeTimeUpdated() override { Real()->m_iFreezeTime.NetworkStateChanged(); }
    int32_t& RoundTime() override { return Real()->m_iRoundTime(); }
    void RoundTimeUpdated() override { Real()->m_iRoundTime.NetworkStateChanged(); }
    float& MatchStartTime() override { return Real()->m_fMatchStartTime(); }
    void MatchStartTimeUpdated() override { Real()->m_fMatchStartTime.NetworkStateChanged(); }
    float& RoundStartTime() override { return Real()->m_fRoundStartTime(); }
    void RoundStartTimeUpdated() override { Real()->m_fRoundStartTime.NetworkStateChanged(); }
    float& RestartRoundTime() override { return Real()->m_flRestartRoundTime(); }
    void RestartRoundTimeUpdated() override { Real()->m_flRestartRoundTime.NetworkStateChanged(); }
    bool& GameRestart() override { return Real()->m_bGameRestart(); }
    void GameRestartUpdated() override { Real()->m_bGameRestart.NetworkStateChanged(); }
    float& GameStartTime() override { return Real()->m_flGameStartTime(); }
    void GameStartTimeUpdated() override { Real()->m_flGameStartTime.NetworkStateChanged(); }
    float& TimeUntilNextPhaseStarts() override { return Real()->m_timeUntilNextPhaseStarts(); }
    void TimeUntilNextPhaseStartsUpdated() override { Real()->m_timeUntilNextPhaseStarts.NetworkStateChanged(); }
    int32_t& GamePhase() override { return Real()->m_gamePhase(); }
    void GamePhaseUpdated() override { Real()->m_gamePhase.NetworkStateChanged(); }
    int32_t& TotalRoundsPlayed() override { return Real()->m_totalRoundsPlayed(); }
    void TotalRoundsPlayedUpdated() override { Real()->m_totalRoundsPlayed.NetworkStateChanged(); }
    int32_t& RoundsPlayedThisPhase() override { return Real()->m_nRoundsPlayedThisPhase(); }
    void RoundsPlayedThisPhaseUpdated() override { Real()->m_nRoundsPlayedThisPhase.NetworkStateChanged(); }
    int32_t& OvertimePlaying() override { return Real()->m_nOvertimePlaying(); }
    void OvertimePlayingUpdated() override { Real()->m_nOvertimePlaying.NetworkStateChanged(); }
    int32_t& HostagesRemaining() override { return Real()->m_iHostagesRemaining(); }
    void HostagesRemainingUpdated() override { Real()->m_iHostagesRemaining.NetworkStateChanged(); }
    bool& AnyHostageReached() override { return Real()->m_bAnyHostageReached(); }
    void AnyHostageReachedUpdated() override { Real()->m_bAnyHostageReached.NetworkStateChanged(); }
    bool& MapHasBombTarget() override { return Real()->m_bMapHasBombTarget(); }
    void MapHasBombTargetUpdated() override { Real()->m_bMapHasBombTarget.NetworkStateChanged(); }
    bool& MapHasRescueZone() override { return Real()->m_bMapHasRescueZone(); }
    void MapHasRescueZoneUpdated() override { Real()->m_bMapHasRescueZone.NetworkStateChanged(); }
    bool& MapHasBuyZone() override { return Real()->m_bMapHasBuyZone(); }
    void MapHasBuyZoneUpdated() override { Real()->m_bMapHasBuyZone.NetworkStateChanged(); }
    bool& IsQueuedMatchmaking() override { return Real()->m_bIsQueuedMatchmaking(); }
    void IsQueuedMatchmakingUpdated() override { Real()->m_bIsQueuedMatchmaking.NetworkStateChanged(); }
    int32_t& QueuedMatchmakingMode() override { return Real()->m_nQueuedMatchmakingMode(); }
    void QueuedMatchmakingModeUpdated() override { Real()->m_nQueuedMatchmakingMode.NetworkStateChanged(); }
    bool& IsValveDS() override { return Real()->m_bIsValveDS(); }
    void IsValveDSUpdated() override { Real()->m_bIsValveDS.NetworkStateChanged(); }
    bool& LogoMap() override { return Real()->m_bLogoMap(); }
    void LogoMapUpdated() override { Real()->m_bLogoMap.NetworkStateChanged(); }
    bool& PlayAllStepSoundsOnServer() override { return Real()->m_bPlayAllStepSoundsOnServer(); }
    void PlayAllStepSoundsOnServerUpdated() override { Real()->m_bPlayAllStepSoundsOnServer.NetworkStateChanged(); }
    int32_t& SpectatorSlotCount() override { return Real()->m_iSpectatorSlotCount(); }
    void SpectatorSlotCountUpdated() override { Real()->m_iSpectatorSlotCount.NetworkStateChanged(); }
    int32_t& MatchDevice() override { return Real()->m_MatchDevice(); }
    void MatchDeviceUpdated() override { Real()->m_MatchDevice.NetworkStateChanged(); }
    bool& HasMatchStarted() override { return Real()->m_bHasMatchStarted(); }
    void HasMatchStartedUpdated() override { Real()->m_bHasMatchStarted.NetworkStateChanged(); }
    int32_t& NextMapInMapgroup() override { return Real()->m_nNextMapInMapgroup(); }
    void NextMapInMapgroupUpdated() override { Real()->m_nNextMapInMapgroup.NetworkStateChanged(); }
    char* TournamentEventName() override { return Real()->m_szTournamentEventName(); }
    char* TournamentEventStage() override { return Real()->m_szTournamentEventStage(); }
    char* MatchStatTxt() override { return Real()->m_szMatchStatTxt(); }
    char* TournamentPredictionsTxt() override { return Real()->m_szTournamentPredictionsTxt(); }
    int32_t& TournamentPredictionsPct() override { return Real()->m_nTournamentPredictionsPct(); }
    void TournamentPredictionsPctUpdated() override { Real()->m_nTournamentPredictionsPct.NetworkStateChanged(); }
    float& MMItemDropRevealStartTime() override { return Real()->m_flCMMItemDropRevealStartTime(); }
    void MMItemDropRevealStartTimeUpdated() override { Real()->m_flCMMItemDropRevealStartTime.NetworkStateChanged(); }
    float& MMItemDropRevealEndTime() override { return Real()->m_flCMMItemDropRevealEndTime(); }
    void MMItemDropRevealEndTimeUpdated() override { Real()->m_flCMMItemDropRevealEndTime.NetworkStateChanged(); }
    bool& IsDroppingItems() override { return Real()->m_bIsDroppingItems(); }
    void IsDroppingItemsUpdated() override { Real()->m_bIsDroppingItems.NetworkStateChanged(); }
    bool& IsQuestEligible() override { return Real()->m_bIsQuestEligible(); }
    void IsQuestEligibleUpdated() override { Real()->m_bIsQuestEligible.NetworkStateChanged(); }
    bool& IsHltvActive() override { return Real()->m_bIsHltvActive(); }
    void IsHltvActiveUpdated() override { Real()->m_bIsHltvActive.NetworkStateChanged(); }
    bool& BombPlanted() override { return Real()->m_bBombPlanted(); }
    void BombPlantedUpdated() override { Real()->m_bBombPlanted.NetworkStateChanged(); }
    uint16_t* ProhibitedItemIndices() override { return Real()->m_arrProhibitedItemIndices(); }
    uint32_t* TournamentActiveCasterAccounts() override { return Real()->m_arrTournamentActiveCasterAccounts(); }
    int32_t& NumBestOfMaps() override { return Real()->m_numBestOfMaps(); }
    void NumBestOfMapsUpdated() override { Real()->m_numBestOfMaps.NetworkStateChanged(); }
    int32_t& HalloweenMaskListSeed() override { return Real()->m_nHalloweenMaskListSeed(); }
    void HalloweenMaskListSeedUpdated() override { Real()->m_nHalloweenMaskListSeed.NetworkStateChanged(); }
    bool& BombDropped() override { return Real()->m_bBombDropped(); }
    void BombDroppedUpdated() override { Real()->m_bBombDropped.NetworkStateChanged(); }
    int32_t& RoundWinStatus() override { return Real()->m_iRoundWinStatus(); }
    void RoundWinStatusUpdated() override { Real()->m_iRoundWinStatus.NetworkStateChanged(); }
    int32_t& RoundWinReason() override { return Real()->m_eRoundWinReason(); }
    void RoundWinReasonUpdated() override { Real()->m_eRoundWinReason.NetworkStateChanged(); }
    bool& TCantBuy() override { return Real()->m_bTCantBuy(); }
    void TCantBuyUpdated() override { Real()->m_bTCantBuy.NetworkStateChanged(); }
    bool& TCantBuy() override { return Real()->m_bCTCantBuy(); }
    void TCantBuyUpdated() override { Real()->m_bCTCantBuy.NetworkStateChanged(); }
    int32_t* MatchStats_RoundResults() override { return Real()->m_iMatchStats_RoundResults(); }
    int32_t* MatchStats_PlayersAlive_CT() override { return Real()->m_iMatchStats_PlayersAlive_CT(); }
    int32_t* MatchStats_PlayersAlive_T() override { return Real()->m_iMatchStats_PlayersAlive_T(); }
    float* TeamRespawnWaveTimes() override { return Real()->m_TeamRespawnWaveTimes(); }
    float* NextRespawnWave() override { return Real()->m_flNextRespawnWave(); }
    Vector& MinimapMins() override { return Real()->m_vMinimapMins(); }
    void MinimapMinsUpdated() override { Real()->m_vMinimapMins.NetworkStateChanged(); }
    Vector& MinimapMaxs() override { return Real()->m_vMinimapMaxs(); }
    void MinimapMaxsUpdated() override { Real()->m_vMinimapMaxs.NetworkStateChanged(); }
    float* MinimapVerticalSectionHeights() override { return Real()->m_MinimapVerticalSectionHeights(); }
    uint64_t& UllLocalMatchID() override { return Real()->m_ullLocalMatchID(); }
    void UllLocalMatchIDUpdated() override { Real()->m_ullLocalMatchID.NetworkStateChanged(); }
    int32_t* EndMatchMapGroupVoteTypes() override { return Real()->m_nEndMatchMapGroupVoteTypes(); }
    int32_t* EndMatchMapGroupVoteOptions() override { return Real()->m_nEndMatchMapGroupVoteOptions(); }
    int32_t& EndMatchMapVoteWinner() override { return Real()->m_nEndMatchMapVoteWinner(); }
    void EndMatchMapVoteWinnerUpdated() override { Real()->m_nEndMatchMapVoteWinner.NetworkStateChanged(); }
    int32_t& NumConsecutiveCTLoses() override { return Real()->m_iNumConsecutiveCTLoses(); }
    void NumConsecutiveCTLosesUpdated() override { Real()->m_iNumConsecutiveCTLoses.NetworkStateChanged(); }
    int32_t& NumConsecutiveTerroristLoses() override { return Real()->m_iNumConsecutiveTerroristLoses(); }
    void NumConsecutiveTerroristLosesUpdated() override { Real()->m_iNumConsecutiveTerroristLoses.NetworkStateChanged(); }
    bool& HasHostageBeenTouched() override { return Real()->m_bHasHostageBeenTouched(); }
    void HasHostageBeenTouchedUpdated() override { Real()->m_bHasHostageBeenTouched.NetworkStateChanged(); }
    float& IntermissionStartTime() override { return Real()->m_flIntermissionStartTime(); }
    void IntermissionStartTimeUpdated() override { Real()->m_flIntermissionStartTime.NetworkStateChanged(); }
    float& IntermissionEndTime() override { return Real()->m_flIntermissionEndTime(); }
    void IntermissionEndTimeUpdated() override { Real()->m_flIntermissionEndTime.NetworkStateChanged(); }
    bool& LevelInitialized() override { return Real()->m_bLevelInitialized(); }
    void LevelInitializedUpdated() override { Real()->m_bLevelInitialized.NetworkStateChanged(); }
    int32_t& TotalRoundsPlayed() override { return Real()->m_iTotalRoundsPlayed(); }
    void TotalRoundsPlayedUpdated() override { Real()->m_iTotalRoundsPlayed.NetworkStateChanged(); }
    int32_t& UnBalancedRounds() override { return Real()->m_iUnBalancedRounds(); }
    void UnBalancedRoundsUpdated() override { Real()->m_iUnBalancedRounds.NetworkStateChanged(); }
    bool& EndMatchOnRoundReset() override { return Real()->m_endMatchOnRoundReset(); }
    void EndMatchOnRoundResetUpdated() override { Real()->m_endMatchOnRoundReset.NetworkStateChanged(); }
    bool& EndMatchOnThink() override { return Real()->m_endMatchOnThink(); }
    void EndMatchOnThinkUpdated() override { Real()->m_endMatchOnThink.NetworkStateChanged(); }
    int32_t& NumTerrorist() override { return Real()->m_iNumTerrorist(); }
    void NumTerroristUpdated() override { Real()->m_iNumTerrorist.NetworkStateChanged(); }
    int32_t& NumCT() override { return Real()->m_iNumCT(); }
    void NumCTUpdated() override { Real()->m_iNumCT.NetworkStateChanged(); }
    int32_t& NumSpawnableTerrorist() override { return Real()->m_iNumSpawnableTerrorist(); }
    void NumSpawnableTerroristUpdated() override { Real()->m_iNumSpawnableTerrorist.NetworkStateChanged(); }
    int32_t& NumSpawnableCT() override { return Real()->m_iNumSpawnableCT(); }
    void NumSpawnableCTUpdated() override { Real()->m_iNumSpawnableCT.NetworkStateChanged(); }
    CUtlVector<int32_t>& SelectedHostageSpawnIndices() override { return Real()->m_arrSelectedHostageSpawnIndices(); }
    void SelectedHostageSpawnIndicesUpdated() override { Real()->m_arrSelectedHostageSpawnIndices.NetworkStateChanged(); }
    int32_t& SpawnPointsRandomSeed() override { return Real()->m_nSpawnPointsRandomSeed(); }
    void SpawnPointsRandomSeedUpdated() override { Real()->m_nSpawnPointsRandomSeed.NetworkStateChanged(); }
    bool& FirstConnected() override { return Real()->m_bFirstConnected(); }
    void FirstConnectedUpdated() override { Real()->m_bFirstConnected.NetworkStateChanged(); }
    bool& CompleteReset() override { return Real()->m_bCompleteReset(); }
    void CompleteResetUpdated() override { Real()->m_bCompleteReset.NetworkStateChanged(); }
    bool& PickNewTeamsOnReset() override { return Real()->m_bPickNewTeamsOnReset(); }
    void PickNewTeamsOnResetUpdated() override { Real()->m_bPickNewTeamsOnReset.NetworkStateChanged(); }
    bool& ScrambleTeamsOnRestart() override { return Real()->m_bScrambleTeamsOnRestart(); }
    void ScrambleTeamsOnRestartUpdated() override { Real()->m_bScrambleTeamsOnRestart.NetworkStateChanged(); }
    bool& SwapTeamsOnRestart() override { return Real()->m_bSwapTeamsOnRestart(); }
    void SwapTeamsOnRestartUpdated() override { Real()->m_bSwapTeamsOnRestart.NetworkStateChanged(); }
    CUtlVector<int32_t>& EndMatchTiedVotes() override { return Real()->m_nEndMatchTiedVotes(); }
    void EndMatchTiedVotesUpdated() override { Real()->m_nEndMatchTiedVotes.NetworkStateChanged(); }
    bool& NeedToAskPlayersForContinueVote() override { return Real()->m_bNeedToAskPlayersForContinueVote(); }
    void NeedToAskPlayersForContinueVoteUpdated() override { Real()->m_bNeedToAskPlayersForContinueVote.NetworkStateChanged(); }
    uint32_t& NumQueuedMatchmakingAccounts() override { return Real()->m_numQueuedMatchmakingAccounts(); }
    void NumQueuedMatchmakingAccountsUpdated() override { Real()->m_numQueuedMatchmakingAccounts.NetworkStateChanged(); }
    float& AvgPlayerRank() override { return Real()->m_fAvgPlayerRank(); }
    void AvgPlayerRankUpdated() override { Real()->m_fAvgPlayerRank.NetworkStateChanged(); }
    char*& QueuedMatchmakingReservationString() override { return Real()->m_pQueuedMatchmakingReservationString(); }
    void QueuedMatchmakingReservationStringUpdated() override { Real()->m_pQueuedMatchmakingReservationString.NetworkStateChanged(); }
    uint32_t& NumTotalTournamentDrops() override { return Real()->m_numTotalTournamentDrops(); }
    void NumTotalTournamentDropsUpdated() override { Real()->m_numTotalTournamentDrops.NetworkStateChanged(); }
    uint32_t& NumSpectatorsCountMax() override { return Real()->m_numSpectatorsCountMax(); }
    void NumSpectatorsCountMaxUpdated() override { Real()->m_numSpectatorsCountMax.NetworkStateChanged(); }
    uint32_t& NumSpectatorsCountMaxTV() override { return Real()->m_numSpectatorsCountMaxTV(); }
    void NumSpectatorsCountMaxTVUpdated() override { Real()->m_numSpectatorsCountMaxTV.NetworkStateChanged(); }
    uint32_t& NumSpectatorsCountMaxLnk() override { return Real()->m_numSpectatorsCountMaxLnk(); }
    void NumSpectatorsCountMaxLnkUpdated() override { Real()->m_numSpectatorsCountMaxLnk.NetworkStateChanged(); }
    int32_t& TsAliveAtFreezetimeEnd() override { return Real()->m_nCTsAliveAtFreezetimeEnd(); }
    void TsAliveAtFreezetimeEndUpdated() override { Real()->m_nCTsAliveAtFreezetimeEnd.NetworkStateChanged(); }
    int32_t& TerroristsAliveAtFreezetimeEnd() override { return Real()->m_nTerroristsAliveAtFreezetimeEnd(); }
    void TerroristsAliveAtFreezetimeEndUpdated() override { Real()->m_nTerroristsAliveAtFreezetimeEnd.NetworkStateChanged(); }
    bool& ForceTeamChangeSilent() override { return Real()->m_bForceTeamChangeSilent(); }
    void ForceTeamChangeSilentUpdated() override { Real()->m_bForceTeamChangeSilent.NetworkStateChanged(); }
    bool& LoadingRoundBackupData() override { return Real()->m_bLoadingRoundBackupData(); }
    void LoadingRoundBackupDataUpdated() override { Real()->m_bLoadingRoundBackupData.NetworkStateChanged(); }
    int32_t& MatchInfoShowType() override { return Real()->m_nMatchInfoShowType(); }
    void MatchInfoShowTypeUpdated() override { Real()->m_nMatchInfoShowType.NetworkStateChanged(); }
    float& MatchInfoDecidedTime() override { return Real()->m_flMatchInfoDecidedTime(); }
    void MatchInfoDecidedTimeUpdated() override { Real()->m_flMatchInfoDecidedTime.NetworkStateChanged(); }
    int32_t& MTeamDMLastWinningTeamNumber() override { return Real()->mTeamDMLastWinningTeamNumber(); }
    void MTeamDMLastWinningTeamNumberUpdated() override { Real()->mTeamDMLastWinningTeamNumber.NetworkStateChanged(); }
    float& MTeamDMLastThinkTime() override { return Real()->mTeamDMLastThinkTime(); }
    void MTeamDMLastThinkTimeUpdated() override { Real()->mTeamDMLastThinkTime.NetworkStateChanged(); }
    float& TeamDMLastAnnouncementTime() override { return Real()->m_flTeamDMLastAnnouncementTime(); }
    void TeamDMLastAnnouncementTimeUpdated() override { Real()->m_flTeamDMLastAnnouncementTime.NetworkStateChanged(); }
    int32_t& AccountTerrorist() override { return Real()->m_iAccountTerrorist(); }
    void AccountTerroristUpdated() override { Real()->m_iAccountTerrorist.NetworkStateChanged(); }
    int32_t& AccountCT() override { return Real()->m_iAccountCT(); }
    void AccountCTUpdated() override { Real()->m_iAccountCT.NetworkStateChanged(); }
    int32_t& SpawnPointCount_Terrorist() override { return Real()->m_iSpawnPointCount_Terrorist(); }
    void SpawnPointCount_TerroristUpdated() override { Real()->m_iSpawnPointCount_Terrorist.NetworkStateChanged(); }
    int32_t& SpawnPointCount_CT() override { return Real()->m_iSpawnPointCount_CT(); }
    void SpawnPointCount_CTUpdated() override { Real()->m_iSpawnPointCount_CT.NetworkStateChanged(); }
    int32_t& MaxNumTerrorists() override { return Real()->m_iMaxNumTerrorists(); }
    void MaxNumTerroristsUpdated() override { Real()->m_iMaxNumTerrorists.NetworkStateChanged(); }
    int32_t& MaxNumCTs() override { return Real()->m_iMaxNumCTs(); }
    void MaxNumCTsUpdated() override { Real()->m_iMaxNumCTs.NetworkStateChanged(); }
    int32_t& LoserBonusMostRecentTeam() override { return Real()->m_iLoserBonusMostRecentTeam(); }
    void LoserBonusMostRecentTeamUpdated() override { Real()->m_iLoserBonusMostRecentTeam.NetworkStateChanged(); }
    float& TmNextPeriodicThink() override { return Real()->m_tmNextPeriodicThink(); }
    void TmNextPeriodicThinkUpdated() override { Real()->m_tmNextPeriodicThink.NetworkStateChanged(); }
    bool& VoiceWonMatchBragFired() override { return Real()->m_bVoiceWonMatchBragFired(); }
    void VoiceWonMatchBragFiredUpdated() override { Real()->m_bVoiceWonMatchBragFired.NetworkStateChanged(); }
    float& WarmupNextChatNoticeTime() override { return Real()->m_fWarmupNextChatNoticeTime(); }
    void WarmupNextChatNoticeTimeUpdated() override { Real()->m_fWarmupNextChatNoticeTime.NetworkStateChanged(); }
    int32_t& HostagesRescued() override { return Real()->m_iHostagesRescued(); }
    void HostagesRescuedUpdated() override { Real()->m_iHostagesRescued.NetworkStateChanged(); }
    int32_t& HostagesTouched() override { return Real()->m_iHostagesTouched(); }
    void HostagesTouchedUpdated() override { Real()->m_iHostagesTouched.NetworkStateChanged(); }
    float& NextHostageAnnouncement() override { return Real()->m_flNextHostageAnnouncement(); }
    void NextHostageAnnouncementUpdated() override { Real()->m_flNextHostageAnnouncement.NetworkStateChanged(); }
    bool& NoTerroristsKilled() override { return Real()->m_bNoTerroristsKilled(); }
    void NoTerroristsKilledUpdated() override { Real()->m_bNoTerroristsKilled.NetworkStateChanged(); }
    bool& NoCTsKilled() override { return Real()->m_bNoCTsKilled(); }
    void NoCTsKilledUpdated() override { Real()->m_bNoCTsKilled.NetworkStateChanged(); }
    bool& NoEnemiesKilled() override { return Real()->m_bNoEnemiesKilled(); }
    void NoEnemiesKilledUpdated() override { Real()->m_bNoEnemiesKilled.NetworkStateChanged(); }
    bool& CanDonateWeapons() override { return Real()->m_bCanDonateWeapons(); }
    void CanDonateWeaponsUpdated() override { Real()->m_bCanDonateWeapons.NetworkStateChanged(); }
    float& FirstKillTime() override { return Real()->m_firstKillTime(); }
    void FirstKillTimeUpdated() override { Real()->m_firstKillTime.NetworkStateChanged(); }
    float& FirstBloodTime() override { return Real()->m_firstBloodTime(); }
    void FirstBloodTimeUpdated() override { Real()->m_firstBloodTime.NetworkStateChanged(); }
    bool& HostageWasInjured() override { return Real()->m_hostageWasInjured(); }
    void HostageWasInjuredUpdated() override { Real()->m_hostageWasInjured.NetworkStateChanged(); }
    bool& HostageWasKilled() override { return Real()->m_hostageWasKilled(); }
    void HostageWasKilledUpdated() override { Real()->m_hostageWasKilled.NetworkStateChanged(); }
    bool& VoteCalled() override { return Real()->m_bVoteCalled(); }
    void VoteCalledUpdated() override { Real()->m_bVoteCalled.NetworkStateChanged(); }
    bool& ServerVoteOnReset() override { return Real()->m_bServerVoteOnReset(); }
    void ServerVoteOnResetUpdated() override { Real()->m_bServerVoteOnReset.NetworkStateChanged(); }
    float& VoteCheckThrottle() override { return Real()->m_flVoteCheckThrottle(); }
    void VoteCheckThrottleUpdated() override { Real()->m_flVoteCheckThrottle.NetworkStateChanged(); }
    bool& BuyTimeEnded() override { return Real()->m_bBuyTimeEnded(); }
    void BuyTimeEndedUpdated() override { Real()->m_bBuyTimeEnded.NetworkStateChanged(); }
    int32_t& LastFreezeEndBeep() override { return Real()->m_nLastFreezeEndBeep(); }
    void LastFreezeEndBeepUpdated() override { Real()->m_nLastFreezeEndBeep.NetworkStateChanged(); }
    bool& TargetBombed() override { return Real()->m_bTargetBombed(); }
    void TargetBombedUpdated() override { Real()->m_bTargetBombed.NetworkStateChanged(); }
    bool& BombDefused() override { return Real()->m_bBombDefused(); }
    void BombDefusedUpdated() override { Real()->m_bBombDefused.NetworkStateChanged(); }
    bool& MapHasBombZone() override { return Real()->m_bMapHasBombZone(); }
    void MapHasBombZoneUpdated() override { Real()->m_bMapHasBombZone.NetworkStateChanged(); }
    Vector& MainCTSpawnPos() override { return Real()->m_vecMainCTSpawnPos(); }
    void MainCTSpawnPosUpdated() override { Real()->m_vecMainCTSpawnPos.NetworkStateChanged(); }
    CUtlVector<CHandle<SpawnPoint>>& TSpawnPointsMasterList() override { return Real()->m_CTSpawnPointsMasterList(); }
    void TSpawnPointsMasterListUpdated() override { Real()->m_CTSpawnPointsMasterList.NetworkStateChanged(); }
    CUtlVector<CHandle<SpawnPoint>>& TerroristSpawnPointsMasterList() override { return Real()->m_TerroristSpawnPointsMasterList(); }
    void TerroristSpawnPointsMasterListUpdated() override { Real()->m_TerroristSpawnPointsMasterList.NetworkStateChanged(); }
    bool& RespawningAllRespawnablePlayers() override { return Real()->m_bRespawningAllRespawnablePlayers(); }
    void RespawningAllRespawnablePlayersUpdated() override { Real()->m_bRespawningAllRespawnablePlayers.NetworkStateChanged(); }
    int32_t& NextCTSpawnPoint() override { return Real()->m_iNextCTSpawnPoint(); }
    void NextCTSpawnPointUpdated() override { Real()->m_iNextCTSpawnPoint.NetworkStateChanged(); }
    float& TSpawnPointUsedTime() override { return Real()->m_flCTSpawnPointUsedTime(); }
    void TSpawnPointUsedTimeUpdated() override { Real()->m_flCTSpawnPointUsedTime.NetworkStateChanged(); }
    int32_t& NextTerroristSpawnPoint() override { return Real()->m_iNextTerroristSpawnPoint(); }
    void NextTerroristSpawnPointUpdated() override { Real()->m_iNextTerroristSpawnPoint.NetworkStateChanged(); }
    float& TerroristSpawnPointUsedTime() override { return Real()->m_flTerroristSpawnPointUsedTime(); }
    void TerroristSpawnPointUsedTimeUpdated() override { Real()->m_flTerroristSpawnPointUsedTime.NetworkStateChanged(); }
    CUtlVector<CHandle<SpawnPoint>>& TSpawnPoints() override { return Real()->m_CTSpawnPoints(); }
    void TSpawnPointsUpdated() override { Real()->m_CTSpawnPoints.NetworkStateChanged(); }
    CUtlVector<CHandle<SpawnPoint>>& TerroristSpawnPoints() override { return Real()->m_TerroristSpawnPoints(); }
    void TerroristSpawnPointsUpdated() override { Real()->m_TerroristSpawnPoints.NetworkStateChanged(); }
    bool& IsUnreservedGameServer() override { return Real()->m_bIsUnreservedGameServer(); }
    void IsUnreservedGameServerUpdated() override { Real()->m_bIsUnreservedGameServer.NetworkStateChanged(); }
    float& AutobalanceDisplayTime() override { return Real()->m_fAutobalanceDisplayTime(); }
    void AutobalanceDisplayTimeUpdated() override { Real()->m_fAutobalanceDisplayTime.NetworkStateChanged(); }
    bool& AllowWeaponSwitch() override { return Real()->m_bAllowWeaponSwitch(); }
    void AllowWeaponSwitchUpdated() override { Real()->m_bAllowWeaponSwitch.NetworkStateChanged(); }
    bool& RoundTimeWarningTriggered() override { return Real()->m_bRoundTimeWarningTriggered(); }
    void RoundTimeWarningTriggeredUpdated() override { Real()->m_bRoundTimeWarningTriggered.NetworkStateChanged(); }
    float& PhaseChangeAnnouncementTime() override { return Real()->m_phaseChangeAnnouncementTime(); }
    void PhaseChangeAnnouncementTimeUpdated() override { Real()->m_phaseChangeAnnouncementTime.NetworkStateChanged(); }
    float& NextUpdateTeamClanNamesTime() override { return Real()->m_fNextUpdateTeamClanNamesTime(); }
    void NextUpdateTeamClanNamesTimeUpdated() override { Real()->m_fNextUpdateTeamClanNamesTime.NetworkStateChanged(); }
    float& LastThinkTime() override { return Real()->m_flLastThinkTime(); }
    void LastThinkTimeUpdated() override { Real()->m_flLastThinkTime.NetworkStateChanged(); }
    float& AccumulatedRoundOffDamage() override { return Real()->m_fAccumulatedRoundOffDamage(); }
    void AccumulatedRoundOffDamageUpdated() override { Real()->m_fAccumulatedRoundOffDamage.NetworkStateChanged(); }
    int32_t& ShorthandedBonusLastEvalRound() override { return Real()->m_nShorthandedBonusLastEvalRound(); }
    void ShorthandedBonusLastEvalRoundUpdated() override { Real()->m_nShorthandedBonusLastEvalRound.NetworkStateChanged(); }
    int32_t& MatchAbortedEarlyReason() override { return Real()->m_nMatchAbortedEarlyReason(); }
    void MatchAbortedEarlyReasonUpdated() override { Real()->m_nMatchAbortedEarlyReason.NetworkStateChanged(); }
    bool& HasTriggeredRoundStartMusic() override { return Real()->m_bHasTriggeredRoundStartMusic(); }
    void HasTriggeredRoundStartMusicUpdated() override { Real()->m_bHasTriggeredRoundStartMusic.NetworkStateChanged(); }
    bool& SwitchingTeamsAtRoundReset() override { return Real()->m_bSwitchingTeamsAtRoundReset(); }
    void SwitchingTeamsAtRoundResetUpdated() override { Real()->m_bSwitchingTeamsAtRoundReset.NetworkStateChanged(); }
    CCSGameModeRules*& GameModeRules() override { return Real()->m_pGameModeRules(); }
    void GameModeRulesUpdated() override { Real()->m_pGameModeRules.NetworkStateChanged(); }
    CHandle<CBaseEntity>& PlayerResource() override { return Real()->m_hPlayerResource(); }
    void PlayerResourceUpdated() override { Real()->m_hPlayerResource.NetworkStateChanged(); }
    CRetakeGameRules& RetakeRules() override { return Real()->m_RetakeRules(); }
    void RetakeRulesUpdated() override { Real()->m_RetakeRules.NetworkStateChanged(); }
    CUtlVector<int32_t>* TeamUniqueKillWeaponsMatch() override { return Real()->m_arrTeamUniqueKillWeaponsMatch(); }
    bool* TeamLastKillUsedUniqueWeaponMatch() override { return Real()->m_bTeamLastKillUsedUniqueWeaponMatch(); }
    uint8_t& MatchEndCount() override { return Real()->m_nMatchEndCount(); }
    void MatchEndCountUpdated() override { Real()->m_nMatchEndCount.NetworkStateChanged(); }
    int32_t& TTeamIntroVariant() override { return Real()->m_nTTeamIntroVariant(); }
    void TTeamIntroVariantUpdated() override { Real()->m_nTTeamIntroVariant.NetworkStateChanged(); }
    int32_t& TTeamIntroVariant() override { return Real()->m_nCTTeamIntroVariant(); }
    void TTeamIntroVariantUpdated() override { Real()->m_nCTTeamIntroVariant.NetworkStateChanged(); }
    bool& TeamIntroPeriod() override { return Real()->m_bTeamIntroPeriod(); }
    void TeamIntroPeriodUpdated() override { Real()->m_bTeamIntroPeriod.NetworkStateChanged(); }
    float& TeamIntroPeriodEnd() override { return Real()->m_fTeamIntroPeriodEnd(); }
    void TeamIntroPeriodEndUpdated() override { Real()->m_fTeamIntroPeriodEnd.NetworkStateChanged(); }
    bool& PlayedTeamIntroVO() override { return Real()->m_bPlayedTeamIntroVO(); }
    void PlayedTeamIntroVOUpdated() override { Real()->m_bPlayedTeamIntroVO.NetworkStateChanged(); }
    int32_t& RoundEndWinnerTeam() override { return Real()->m_iRoundEndWinnerTeam(); }
    void RoundEndWinnerTeamUpdated() override { Real()->m_iRoundEndWinnerTeam.NetworkStateChanged(); }
    int32_t& RoundEndReason() override { return Real()->m_eRoundEndReason(); }
    void RoundEndReasonUpdated() override { Real()->m_eRoundEndReason.NetworkStateChanged(); }
    bool& RoundEndShowTimerDefend() override { return Real()->m_bRoundEndShowTimerDefend(); }
    void RoundEndShowTimerDefendUpdated() override { Real()->m_bRoundEndShowTimerDefend.NetworkStateChanged(); }
    int32_t& RoundEndTimerTime() override { return Real()->m_iRoundEndTimerTime(); }
    void RoundEndTimerTimeUpdated() override { Real()->m_iRoundEndTimerTime.NetworkStateChanged(); }
    CUtlString& RoundEndFunFactToken() override { return Real()->m_sRoundEndFunFactToken(); }
    void RoundEndFunFactTokenUpdated() override { Real()->m_sRoundEndFunFactToken.NetworkStateChanged(); }
    int32_t& RoundEndFunFactPlayerSlot() override { return Real()->m_iRoundEndFunFactPlayerSlot(); }
    void RoundEndFunFactPlayerSlotUpdated() override { Real()->m_iRoundEndFunFactPlayerSlot.NetworkStateChanged(); }
    int32_t& RoundEndFunFactData1() override { return Real()->m_iRoundEndFunFactData1(); }
    void RoundEndFunFactData1Updated() override { Real()->m_iRoundEndFunFactData1.NetworkStateChanged(); }
    int32_t& RoundEndFunFactData2() override { return Real()->m_iRoundEndFunFactData2(); }
    void RoundEndFunFactData2Updated() override { Real()->m_iRoundEndFunFactData2.NetworkStateChanged(); }
    int32_t& RoundEndFunFactData3() override { return Real()->m_iRoundEndFunFactData3(); }
    void RoundEndFunFactData3Updated() override { Real()->m_iRoundEndFunFactData3.NetworkStateChanged(); }
    CUtlString& RoundEndMessage() override { return Real()->m_sRoundEndMessage(); }
    void RoundEndMessageUpdated() override { Real()->m_sRoundEndMessage.NetworkStateChanged(); }
    int32_t& RoundEndPlayerCount() override { return Real()->m_iRoundEndPlayerCount(); }
    void RoundEndPlayerCountUpdated() override { Real()->m_iRoundEndPlayerCount.NetworkStateChanged(); }
    bool& RoundEndNoMusic() override { return Real()->m_bRoundEndNoMusic(); }
    void RoundEndNoMusicUpdated() override { Real()->m_bRoundEndNoMusic.NetworkStateChanged(); }
    int32_t& RoundEndLegacy() override { return Real()->m_iRoundEndLegacy(); }
    void RoundEndLegacyUpdated() override { Real()->m_iRoundEndLegacy.NetworkStateChanged(); }
    uint8_t& RoundEndCount() override { return Real()->m_nRoundEndCount(); }
    void RoundEndCountUpdated() override { Real()->m_nRoundEndCount.NetworkStateChanged(); }
    int32_t& RoundStartRoundNumber() override { return Real()->m_iRoundStartRoundNumber(); }
    void RoundStartRoundNumberUpdated() override { Real()->m_iRoundStartRoundNumber.NetworkStateChanged(); }
    uint8_t& RoundStartCount() override { return Real()->m_nRoundStartCount(); }
    void RoundStartCountUpdated() override { Real()->m_nRoundStartCount.NetworkStateChanged(); }
    double& LastPerfSampleTime() override { return Real()->m_flLastPerfSampleTime(); }
    void LastPerfSampleTimeUpdated() override { Real()->m_flLastPerfSampleTime.NetworkStateChanged(); }

    void TerminateRound(float flDelay, int32_t eRoundEndReason) override { Real()->TerminateRound(flDelay, eRoundEndReason); }
    IBaseEntity* FindPickerEntity(IBasePlayerController* pPlayer) override { return Real()->FindPickerEntity(pPlayer); }
    ICSPlayerController* GetClientAimTarget(ICSPlayerController* pPlayer) override { return Real()->GetClientAimTarget(pPlayer); }
};

#endif // _INCLUDE_CCSGAMERULESIMPL_H
