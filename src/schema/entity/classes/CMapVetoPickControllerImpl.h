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

#ifndef _INCLUDE_CMAPVETOPICKCONTROLLERIMPL_H
#define _INCLUDE_CMAPVETOPICKCONTROLLERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IMapVetoPickController.h"
#include "schema/entity/classes/CMapVetoPickController.h"
#include "CBaseEntityImpl.h"

class CMapVetoPickControllerImpl : public CBaseEntityImpl, public virtual IMapVetoPickController
{

public:
    explicit CMapVetoPickControllerImpl(CMapVetoPickController* p) : CBaseEntityImpl(p) {}

private:
    CMapVetoPickController* Real() { return static_cast<CMapVetoPickController*>(m_pReal); }
    CMapVetoPickController* Real() const { return static_cast<CMapVetoPickController*>(m_pReal); }

public:
    CMapVetoPickController* GetOriginal() const override { return Real(); }
    bool& PlayedIntroVcd() override { return Real()->m_bPlayedIntroVcd(); }
    void PlayedIntroVcdUpdated() override { Real()->m_bPlayedIntroVcd.NetworkStateChanged(); }
    bool& NeedToPlayFiveSecondsRemaining() override { return Real()->m_bNeedToPlayFiveSecondsRemaining(); }
    void NeedToPlayFiveSecondsRemainingUpdated() override { Real()->m_bNeedToPlayFiveSecondsRemaining.NetworkStateChanged(); }
    double& DblPreMatchDraftSequenceTime() override { return Real()->m_dblPreMatchDraftSequenceTime(); }
    void DblPreMatchDraftSequenceTimeUpdated() override { Real()->m_dblPreMatchDraftSequenceTime.NetworkStateChanged(); }
    bool& PreMatchDraftStateChanged() override { return Real()->m_bPreMatchDraftStateChanged(); }
    void PreMatchDraftStateChangedUpdated() override { Real()->m_bPreMatchDraftStateChanged.NetworkStateChanged(); }
    int32_t& DraftType() override { return Real()->m_nDraftType(); }
    void DraftTypeUpdated() override { Real()->m_nDraftType.NetworkStateChanged(); }
    int32_t& TeamWinningCoinToss() override { return Real()->m_nTeamWinningCoinToss(); }
    void TeamWinningCoinTossUpdated() override { Real()->m_nTeamWinningCoinToss.NetworkStateChanged(); }
    int32_t* TeamWithFirstChoice() override { return Real()->m_nTeamWithFirstChoice(); }
    int32_t* VoteMapIdsList() override { return Real()->m_nVoteMapIdsList(); }
    int32_t* AccountIDs() override { return Real()->m_nAccountIDs(); }
    int32_t* MapId0() override { return Real()->m_nMapId0(); }
    int32_t* MapId1() override { return Real()->m_nMapId1(); }
    int32_t* MapId2() override { return Real()->m_nMapId2(); }
    int32_t* MapId3() override { return Real()->m_nMapId3(); }
    int32_t* MapId4() override { return Real()->m_nMapId4(); }
    int32_t* MapId5() override { return Real()->m_nMapId5(); }
    int32_t* StartingSide0() override { return Real()->m_nStartingSide0(); }
    int32_t& CurrentPhase() override { return Real()->m_nCurrentPhase(); }
    void CurrentPhaseUpdated() override { Real()->m_nCurrentPhase.NetworkStateChanged(); }
    int32_t& PhaseStartTick() override { return Real()->m_nPhaseStartTick(); }
    void PhaseStartTickUpdated() override { Real()->m_nPhaseStartTick.NetworkStateChanged(); }
    int32_t& PhaseDurationTicks() override { return Real()->m_nPhaseDurationTicks(); }
    void PhaseDurationTicksUpdated() override { Real()->m_nPhaseDurationTicks.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IMapVetoPickController* CMapVetoPickController::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IMapVetoPickController*>(tagIt->second.ptr_for_return);
    auto* impl = new CMapVetoPickControllerImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IMapVetoPickController*>(impl));
    return impl;
}
inline IMapVetoPickController* IMapVetoPickController::FromRaw(CEntityInstance* p) { return p ? static_cast<CMapVetoPickController*>(p)->ToInterface() : nullptr; }
inline IMapVetoPickController* IMapVetoPickController::FromOriginal(CMapVetoPickController* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CMAPVETOPICKCONTROLLERIMPL_H
