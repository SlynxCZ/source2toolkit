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

#ifndef _INCLUDE_CFUNCLADDERIMPL_H
#define _INCLUDE_CFUNCLADDERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IFuncLadder.h"
#include "schema/entity/classes/CFuncLadder.h"
#include "CBaseModelEntityImpl.h"

class CFuncLadderImpl : public CBaseModelEntityImpl, public IFuncLadder
{

public:
    explicit CFuncLadderImpl(CFuncLadder* p) : CBaseModelEntityImpl(p) {}

private:
    CFuncLadder* Real() { return static_cast<CFuncLadder*>(m_pReal); }

public:
    Vector& LadderDir() override { return Real()->m_vecLadderDir(); }
    void LadderDirUpdated() override { Real()->m_vecLadderDir.NetworkStateChanged(); }
    CUtlVector<CHandle<CInfoLadderDismount>>& Dismounts() override { return Real()->m_Dismounts(); }
    void DismountsUpdated() override { Real()->m_Dismounts.NetworkStateChanged(); }
    Vector& LocalTop() override { return Real()->m_vecLocalTop(); }
    void LocalTopUpdated() override { Real()->m_vecLocalTop.NetworkStateChanged(); }
    Vector& PlayerMountPositionTop() override { return Real()->m_vecPlayerMountPositionTop(); }
    void PlayerMountPositionTopUpdated() override { Real()->m_vecPlayerMountPositionTop.NetworkStateChanged(); }
    Vector& PlayerMountPositionBottom() override { return Real()->m_vecPlayerMountPositionBottom(); }
    void PlayerMountPositionBottomUpdated() override { Real()->m_vecPlayerMountPositionBottom.NetworkStateChanged(); }
    float& AutoRideSpeed() override { return Real()->m_flAutoRideSpeed(); }
    void AutoRideSpeedUpdated() override { Real()->m_flAutoRideSpeed.NetworkStateChanged(); }
    bool& Disabled() override { return Real()->m_bDisabled(); }
    void DisabledUpdated() override { Real()->m_bDisabled.NetworkStateChanged(); }
    bool& FakeLadder() override { return Real()->m_bFakeLadder(); }
    void FakeLadderUpdated() override { Real()->m_bFakeLadder.NetworkStateChanged(); }
    bool& HasSlack() override { return Real()->m_bHasSlack(); }
    void HasSlackUpdated() override { Real()->m_bHasSlack.NetworkStateChanged(); }
    CUtlSymbolLarge& SurfacePropName() override { return Real()->m_surfacePropName(); }
    void SurfacePropNameUpdated() override { Real()->m_surfacePropName.NetworkStateChanged(); }
    CEntityIOOutput& OnPlayerGotOnLadder() override { return Real()->m_OnPlayerGotOnLadder(); }
    void OnPlayerGotOnLadderUpdated() override { Real()->m_OnPlayerGotOnLadder.NetworkStateChanged(); }
    CEntityIOOutput& OnPlayerGotOffLadder() override { return Real()->m_OnPlayerGotOffLadder(); }
    void OnPlayerGotOffLadderUpdated() override { Real()->m_OnPlayerGotOffLadder.NetworkStateChanged(); }
};

#endif // _INCLUDE_CFUNCLADDERIMPL_H
