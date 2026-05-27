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

#ifndef _INCLUDE_CPOINTCOMMENTARYNODEIMPL_H
#define _INCLUDE_CPOINTCOMMENTARYNODEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPointCommentaryNode.h"
#include "schema/entity/classes/CPointCommentaryNode.h"
#include "CBaseAnimGraphImpl.h"

class CPointCommentaryNodeImpl : public CBaseAnimGraphImpl, public IPointCommentaryNode
{

public:
    explicit CPointCommentaryNodeImpl(CPointCommentaryNode* p) : CBaseAnimGraphImpl(p) {}

private:
    CPointCommentaryNode* Real() { return static_cast<CPointCommentaryNode*>(m_pReal); }

public:
    CUtlSymbolLarge& PreCommands() override { return Real()->m_iszPreCommands(); }
    void PreCommandsUpdated() override { Real()->m_iszPreCommands.NetworkStateChanged(); }
    CUtlSymbolLarge& PostCommands() override { return Real()->m_iszPostCommands(); }
    void PostCommandsUpdated() override { Real()->m_iszPostCommands.NetworkStateChanged(); }
    CUtlSymbolLarge& CommentaryFile() override { return Real()->m_iszCommentaryFile(); }
    void CommentaryFileUpdated() override { Real()->m_iszCommentaryFile.NetworkStateChanged(); }
    CUtlSymbolLarge& ViewTarget() override { return Real()->m_iszViewTarget(); }
    void ViewTargetUpdated() override { Real()->m_iszViewTarget.NetworkStateChanged(); }
    CHandle<CBaseEntity>& ViewTarget() override { return Real()->m_hViewTarget(); }
    void ViewTargetUpdated() override { Real()->m_hViewTarget.NetworkStateChanged(); }
    CHandle<CBaseEntity>& ViewTargetAngles() override { return Real()->m_hViewTargetAngles(); }
    void ViewTargetAnglesUpdated() override { Real()->m_hViewTargetAngles.NetworkStateChanged(); }
    CUtlSymbolLarge& ViewPosition() override { return Real()->m_iszViewPosition(); }
    void ViewPositionUpdated() override { Real()->m_iszViewPosition.NetworkStateChanged(); }
    CHandle<CBaseEntity>& ViewPosition() override { return Real()->m_hViewPosition(); }
    void ViewPositionUpdated() override { Real()->m_hViewPosition.NetworkStateChanged(); }
    CHandle<CBaseEntity>& ViewPositionMover() override { return Real()->m_hViewPositionMover(); }
    void ViewPositionMoverUpdated() override { Real()->m_hViewPositionMover.NetworkStateChanged(); }
    bool& PreventMovement() override { return Real()->m_bPreventMovement(); }
    void PreventMovementUpdated() override { Real()->m_bPreventMovement.NetworkStateChanged(); }
    bool& UnderCrosshair() override { return Real()->m_bUnderCrosshair(); }
    void UnderCrosshairUpdated() override { Real()->m_bUnderCrosshair.NetworkStateChanged(); }
    bool& Unstoppable() override { return Real()->m_bUnstoppable(); }
    void UnstoppableUpdated() override { Real()->m_bUnstoppable.NetworkStateChanged(); }
    float& FinishedTime() override { return Real()->m_flFinishedTime(); }
    void FinishedTimeUpdated() override { Real()->m_flFinishedTime.NetworkStateChanged(); }
    Vector& FinishOrigin() override { return Real()->m_vecFinishOrigin(); }
    void FinishOriginUpdated() override { Real()->m_vecFinishOrigin.NetworkStateChanged(); }
    QAngle& OriginalAngles() override { return Real()->m_vecOriginalAngles(); }
    void OriginalAnglesUpdated() override { Real()->m_vecOriginalAngles.NetworkStateChanged(); }
    QAngle& FinishAngles() override { return Real()->m_vecFinishAngles(); }
    void FinishAnglesUpdated() override { Real()->m_vecFinishAngles.NetworkStateChanged(); }
    bool& PreventChangesWhileMoving() override { return Real()->m_bPreventChangesWhileMoving(); }
    void PreventChangesWhileMovingUpdated() override { Real()->m_bPreventChangesWhileMoving.NetworkStateChanged(); }
    bool& Disabled() override { return Real()->m_bDisabled(); }
    void DisabledUpdated() override { Real()->m_bDisabled.NetworkStateChanged(); }
    Vector& TeleportOrigin() override { return Real()->m_vecTeleportOrigin(); }
    void TeleportOriginUpdated() override { Real()->m_vecTeleportOrigin.NetworkStateChanged(); }
    float& AbortedPlaybackAt() override { return Real()->m_flAbortedPlaybackAt(); }
    void AbortedPlaybackAtUpdated() override { Real()->m_flAbortedPlaybackAt.NetworkStateChanged(); }
    CEntityIOOutput& OnCommentaryStarted() override { return Real()->m_pOnCommentaryStarted(); }
    void OnCommentaryStartedUpdated() override { Real()->m_pOnCommentaryStarted.NetworkStateChanged(); }
    CEntityIOOutput& OnCommentaryStopped() override { return Real()->m_pOnCommentaryStopped(); }
    void OnCommentaryStoppedUpdated() override { Real()->m_pOnCommentaryStopped.NetworkStateChanged(); }
    bool& Active() override { return Real()->m_bActive(); }
    void ActiveUpdated() override { Real()->m_bActive.NetworkStateChanged(); }
    float& StartTime() override { return Real()->m_flStartTime(); }
    void StartTimeUpdated() override { Real()->m_flStartTime.NetworkStateChanged(); }
    float& StartTimeInCommentary() override { return Real()->m_flStartTimeInCommentary(); }
    void StartTimeInCommentaryUpdated() override { Real()->m_flStartTimeInCommentary.NetworkStateChanged(); }
    CUtlSymbolLarge& Title() override { return Real()->m_iszTitle(); }
    void TitleUpdated() override { Real()->m_iszTitle.NetworkStateChanged(); }
    CUtlSymbolLarge& Speakers() override { return Real()->m_iszSpeakers(); }
    void SpeakersUpdated() override { Real()->m_iszSpeakers.NetworkStateChanged(); }
    int32_t& NodeNumber() override { return Real()->m_iNodeNumber(); }
    void NodeNumberUpdated() override { Real()->m_iNodeNumber.NetworkStateChanged(); }
    int32_t& NodeNumberMax() override { return Real()->m_iNodeNumberMax(); }
    void NodeNumberMaxUpdated() override { Real()->m_iNodeNumberMax.NetworkStateChanged(); }
    bool& ListenedTo() override { return Real()->m_bListenedTo(); }
    void ListenedToUpdated() override { Real()->m_bListenedTo.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPOINTCOMMENTARYNODEIMPL_H
