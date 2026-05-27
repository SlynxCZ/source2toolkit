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

#ifndef _INCLUDE_CCSPLAYER_RADIOSERVICESIMPL_H
#define _INCLUDE_CCSPLAYER_RADIOSERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/ICSPlayer_RadioServices.h"
#include "schema/entity/classes/CCSPlayer_RadioServices.h"
#include "CPlayerPawnComponentImpl.h"

class CCSPlayer_RadioServicesImpl : public CPlayerPawnComponentImpl, public ICSPlayer_RadioServices
{

public:
    explicit CCSPlayer_RadioServicesImpl(CCSPlayer_RadioServices* p) : CPlayerPawnComponentImpl(p) {}

private:
    CCSPlayer_RadioServices* Real() { return static_cast<CCSPlayer_RadioServices*>(m_pReal); }

public:
    float& GotHostageTalkTimer() override { return Real()->m_flGotHostageTalkTimer(); }
    void GotHostageTalkTimerUpdated() override { Real()->m_flGotHostageTalkTimer.NetworkStateChanged(); }
    float& DefusingTalkTimer() override { return Real()->m_flDefusingTalkTimer(); }
    void DefusingTalkTimerUpdated() override { Real()->m_flDefusingTalkTimer.NetworkStateChanged(); }
    float& C4PlantTalkTimer() override { return Real()->m_flC4PlantTalkTimer(); }
    void C4PlantTalkTimerUpdated() override { Real()->m_flC4PlantTalkTimer.NetworkStateChanged(); }
    float* RadioTokenSlots() override { return Real()->m_flRadioTokenSlots(); }
    bool& IgnoreRadio() override { return Real()->m_bIgnoreRadio(); }
    void IgnoreRadioUpdated() override { Real()->m_bIgnoreRadio.NetworkStateChanged(); }
};

#endif // _INCLUDE_CCSPLAYER_RADIOSERVICESIMPL_H
