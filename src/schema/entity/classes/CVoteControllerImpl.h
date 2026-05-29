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

#ifndef _INCLUDE_CVOTECONTROLLERIMPL_H
#define _INCLUDE_CVOTECONTROLLERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IVoteController.h"
#include "schema/entity/classes/CVoteController.h"
#include "CBaseEntityImpl.h"

class CVoteControllerImpl : public CBaseEntityImpl, public virtual IVoteController
{

public:
    explicit CVoteControllerImpl(CVoteController* p) : CBaseEntityImpl(p) {}

private:
    CVoteController* Real() { return static_cast<CVoteController*>(m_pReal); }
    CVoteController* Real() const { return static_cast<CVoteController*>(m_pReal); }

public:
    CVoteController* GetOriginal() const override { return Real(); }
    int32_t& ActiveIssueIndex() override { return Real()->m_iActiveIssueIndex(); }
    void ActiveIssueIndexUpdated() override { Real()->m_iActiveIssueIndex.NetworkStateChanged(); }
    int32_t& OnlyTeamToVote() override { return Real()->m_iOnlyTeamToVote(); }
    void OnlyTeamToVoteUpdated() override { Real()->m_iOnlyTeamToVote.NetworkStateChanged(); }
    int32_t* VoteOptionCount() override { return Real()->m_nVoteOptionCount(); }
    int32_t& PotentialVotes() override { return Real()->m_nPotentialVotes(); }
    void PotentialVotesUpdated() override { Real()->m_nPotentialVotes.NetworkStateChanged(); }
    bool& IsYesNoVote() override { return Real()->m_bIsYesNoVote(); }
    void IsYesNoVoteUpdated() override { Real()->m_bIsYesNoVote.NetworkStateChanged(); }
    ::CountdownTimer& AcceptingVotesTimer() override { return Real()->m_acceptingVotesTimer(); }
    void AcceptingVotesTimerUpdated() override { Real()->m_acceptingVotesTimer.NetworkStateChanged(); }
    ::CountdownTimer& ExecuteCommandTimer() override { return Real()->m_executeCommandTimer(); }
    void ExecuteCommandTimerUpdated() override { Real()->m_executeCommandTimer.NetworkStateChanged(); }
    ::CountdownTimer& ResetVoteTimer() override { return Real()->m_resetVoteTimer(); }
    void ResetVoteTimerUpdated() override { Real()->m_resetVoteTimer.NetworkStateChanged(); }
    int32_t* VotesCast() override { return Real()->m_nVotesCast(); }
    int32_t& PlayerHoldingVote() override { return Real()->m_playerHoldingVote(); }
    void PlayerHoldingVoteUpdated() override { Real()->m_playerHoldingVote.NetworkStateChanged(); }
    int32_t& PlayerOverrideForVote() override { return Real()->m_playerOverrideForVote(); }
    void PlayerOverrideForVoteUpdated() override { Real()->m_playerOverrideForVote.NetworkStateChanged(); }
    int32_t& HighestCountIndex() override { return Real()->m_nHighestCountIndex(); }
    void HighestCountIndexUpdated() override { Real()->m_nHighestCountIndex.NetworkStateChanged(); }
    CUtlVector<CBaseIssue*>& PotentialIssues() override { return Real()->m_potentialIssues(); }
    void PotentialIssuesUpdated() override { Real()->m_potentialIssues.NetworkStateChanged(); }
    CUtlVector<char*>& VoteOptions() override { return Real()->m_VoteOptions(); }
    void VoteOptionsUpdated() override { Real()->m_VoteOptions.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IVoteController* CVoteController::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IVoteController*>(tagIt->second.ptr_for_return);
    auto* impl = new CVoteControllerImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IVoteController*>(impl));
    return impl;
}
inline IVoteController* IVoteController::FromRaw(CEntityInstance* p) { return p ? static_cast<CVoteController*>(p)->ToInterface() : nullptr; }
inline IVoteController* IVoteController::FromOriginal(CVoteController* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CVOTECONTROLLERIMPL_H
