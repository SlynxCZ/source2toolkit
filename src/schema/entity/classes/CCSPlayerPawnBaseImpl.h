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

#ifndef _INCLUDE_CCSPLAYERPAWNBASEIMPL_H
#define _INCLUDE_CCSPLAYERPAWNBASEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayerPawnBase.h"
#include "schema/entity/classes/CCSPlayerPawnBase.h"
#include "CBasePlayerPawnImpl.h"

class CCSPlayerPawnBaseImpl : public CBasePlayerPawnImpl, public ICSPlayerPawnBase
{

public:
    explicit CCSPlayerPawnBaseImpl(CCSPlayerPawnBase* p) : CBasePlayerPawnImpl(p) {}

private:
    CCSPlayerPawnBase* Real() { return static_cast<CCSPlayerPawnBase*>(m_pReal); }
    CCSPlayerPawnBase* Real() const { return static_cast<CCSPlayerPawnBase*>(m_pReal); }

public:
    CCSPlayerPawnBase* GetOriginal() const override { return Real(); }
    ::CTouchExpansionComponent& TouchExpansionComponent() override { return Real()->m_CTouchExpansionComponent(); }
    void TouchExpansionComponentUpdated() override { Real()->m_CTouchExpansionComponent.NetworkStateChanged(); }
    CCSPlayer_PingServices*& PingServices() override { return Real()->m_pPingServices(); }
    void PingServicesUpdated() override { Real()->m_pPingServices.NetworkStateChanged(); }
    float& BlindUntilTime() override { return Real()->m_blindUntilTime(); }
    void BlindUntilTimeUpdated() override { Real()->m_blindUntilTime.NetworkStateChanged(); }
    float& BlindStartTime() override { return Real()->m_blindStartTime(); }
    void BlindStartTimeUpdated() override { Real()->m_blindStartTime.NetworkStateChanged(); }
    ::CSPlayerState& PlayerState() override { return Real()->m_iPlayerState(); }
    void PlayerStateUpdated() override { Real()->m_iPlayerState.NetworkStateChanged(); }
    bool& Respawning() override { return Real()->m_bRespawning(); }
    void RespawningUpdated() override { Real()->m_bRespawning.NetworkStateChanged(); }
    bool& HasMovedSinceSpawn() override { return Real()->m_bHasMovedSinceSpawn(); }
    void HasMovedSinceSpawnUpdated() override { Real()->m_bHasMovedSinceSpawn.NetworkStateChanged(); }
    int32_t& NumSpawns() override { return Real()->m_iNumSpawns(); }
    void NumSpawnsUpdated() override { Real()->m_iNumSpawns.NetworkStateChanged(); }
    float& IdleTimeSinceLastAction() override { return Real()->m_flIdleTimeSinceLastAction(); }
    void IdleTimeSinceLastActionUpdated() override { Real()->m_flIdleTimeSinceLastAction.NetworkStateChanged(); }
    float& NextRadarUpdateTime() override { return Real()->m_fNextRadarUpdateTime(); }
    void NextRadarUpdateTimeUpdated() override { Real()->m_fNextRadarUpdateTime.NetworkStateChanged(); }
    float& FlashDuration() override { return Real()->m_flFlashDuration(); }
    void FlashDurationUpdated() override { Real()->m_flFlashDuration.NetworkStateChanged(); }
    float& FlashMaxAlpha() override { return Real()->m_flFlashMaxAlpha(); }
    void FlashMaxAlphaUpdated() override { Real()->m_flFlashMaxAlpha.NetworkStateChanged(); }
    float& ProgressBarStartTime() override { return Real()->m_flProgressBarStartTime(); }
    void ProgressBarStartTimeUpdated() override { Real()->m_flProgressBarStartTime.NetworkStateChanged(); }
    int32_t& ProgressBarDuration() override { return Real()->m_iProgressBarDuration(); }
    void ProgressBarDurationUpdated() override { Real()->m_iProgressBarDuration.NetworkStateChanged(); }
    CHandle<CCSPlayerController>& OriginalController() override { return Real()->m_hOriginalController(); }
    void OriginalControllerUpdated() override { Real()->m_hOriginalController.NetworkStateChanged(); }
};

inline ICSPlayerPawnBase* CCSPlayerPawnBase::ToInterface() { return new CCSPlayerPawnBaseImpl(this); }
inline ICSPlayerPawnBase* ICSPlayerPawnBase::FromOriginal(CCSPlayerPawnBase* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSPLAYERPAWNBASEIMPL_H
