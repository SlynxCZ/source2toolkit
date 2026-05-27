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

#ifndef _INCLUDE_CFUNCTRACKCHANGEIMPL_H
#define _INCLUDE_CFUNCTRACKCHANGEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IFuncTrackChange.h"
#include "schema/entity/classes/CFuncTrackChange.h"
#include "CFuncPlatRotImpl.h"

class CFuncTrackChangeImpl : public CFuncPlatRotImpl, public IFuncTrackChange
{

public:
    explicit CFuncTrackChangeImpl(CFuncTrackChange* p) : CFuncPlatRotImpl(p) {}

private:
    CFuncTrackChange* Real() { return static_cast<CFuncTrackChange*>(m_pReal); }

public:
    CHandle<CPathTrack>& TrackTop() override { return Real()->m_trackTop(); }
    void TrackTopUpdated() override { Real()->m_trackTop.NetworkStateChanged(); }
    CHandle<CPathTrack>& TrackBottom() override { return Real()->m_trackBottom(); }
    void TrackBottomUpdated() override { Real()->m_trackBottom.NetworkStateChanged(); }
    CHandle<CFuncTrackTrain>& Train() override { return Real()->m_train(); }
    void TrainUpdated() override { Real()->m_train.NetworkStateChanged(); }
    CUtlSymbolLarge& TrackTopName() override { return Real()->m_trackTopName(); }
    void TrackTopNameUpdated() override { Real()->m_trackTopName.NetworkStateChanged(); }
    CUtlSymbolLarge& TrackBottomName() override { return Real()->m_trackBottomName(); }
    void TrackBottomNameUpdated() override { Real()->m_trackBottomName.NetworkStateChanged(); }
    CUtlSymbolLarge& TrainName() override { return Real()->m_trainName(); }
    void TrainNameUpdated() override { Real()->m_trainName.NetworkStateChanged(); }
    TRAIN_CODE& Code() override { return Real()->m_code(); }
    void CodeUpdated() override { Real()->m_code.NetworkStateChanged(); }
    int32_t& TargetState() override { return Real()->m_targetState(); }
    void TargetStateUpdated() override { Real()->m_targetState.NetworkStateChanged(); }
    int32_t& Use() override { return Real()->m_use(); }
    void UseUpdated() override { Real()->m_use.NetworkStateChanged(); }
};

#endif // _INCLUDE_CFUNCTRACKCHANGEIMPL_H
