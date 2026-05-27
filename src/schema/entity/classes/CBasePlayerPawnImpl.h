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

#ifndef _INCLUDE_CBASEPLAYERPAWNIMPL_H
#define _INCLUDE_CBASEPLAYERPAWNIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBasePlayerPawn.h"
#include "schema/entity/classes/CBasePlayerPawn.h"
#include "CBaseCombatCharacterImpl.h"

class CBasePlayerPawnImpl : public CBaseCombatCharacterImpl, public IBasePlayerPawn
{

public:
    explicit CBasePlayerPawnImpl(CBasePlayerPawn* p) : CBaseCombatCharacterImpl(p) {}

private:
    CBasePlayerPawn* Real() { return static_cast<CBasePlayerPawn*>(m_pReal); }

public:
    CPlayer_WeaponServices*& WeaponServices() override { return Real()->m_pWeaponServices(); }
    void WeaponServicesUpdated() override { Real()->m_pWeaponServices.NetworkStateChanged(); }
    CPlayer_ItemServices*& ItemServices() override { return Real()->m_pItemServices(); }
    void ItemServicesUpdated() override { Real()->m_pItemServices.NetworkStateChanged(); }
    CPlayer_AutoaimServices*& AutoaimServices() override { return Real()->m_pAutoaimServices(); }
    void AutoaimServicesUpdated() override { Real()->m_pAutoaimServices.NetworkStateChanged(); }
    CPlayer_ObserverServices*& ObserverServices() override { return Real()->m_pObserverServices(); }
    void ObserverServicesUpdated() override { Real()->m_pObserverServices.NetworkStateChanged(); }
    CPlayer_WaterServices*& WaterServices() override { return Real()->m_pWaterServices(); }
    void WaterServicesUpdated() override { Real()->m_pWaterServices.NetworkStateChanged(); }
    CPlayer_UseServices*& UseServices() override { return Real()->m_pUseServices(); }
    void UseServicesUpdated() override { Real()->m_pUseServices.NetworkStateChanged(); }
    CPlayer_FlashlightServices*& FlashlightServices() override { return Real()->m_pFlashlightServices(); }
    void FlashlightServicesUpdated() override { Real()->m_pFlashlightServices.NetworkStateChanged(); }
    CPlayer_CameraServices*& CameraServices() override { return Real()->m_pCameraServices(); }
    void CameraServicesUpdated() override { Real()->m_pCameraServices.NetworkStateChanged(); }
    CPlayer_MovementServices*& MovementServices() override { return Real()->m_pMovementServices(); }
    void MovementServicesUpdated() override { Real()->m_pMovementServices.NetworkStateChanged(); }
    CUtlVector<ViewAngleServerChange_t>& ServerViewAngleChanges() override { return Real()->m_ServerViewAngleChanges(); }
    void ServerViewAngleChangesUpdated() override { Real()->m_ServerViewAngleChanges.NetworkStateChanged(); }
    QAngle& V_angle() override { return Real()->v_angle(); }
    void V_angleUpdated() override { Real()->v_angle.NetworkStateChanged(); }
    QAngle& V_anglePrevious() override { return Real()->v_anglePrevious(); }
    void V_anglePreviousUpdated() override { Real()->v_anglePrevious.NetworkStateChanged(); }
    uint32_t& HideHUD() override { return Real()->m_iHideHUD(); }
    void HideHUDUpdated() override { Real()->m_iHideHUD.NetworkStateChanged(); }
    sky3dparams_t& Skybox3d() override { return Real()->m_skybox3d(); }
    void Skybox3dUpdated() override { Real()->m_skybox3d.NetworkStateChanged(); }
    float& TimeLastHurt() override { return Real()->m_fTimeLastHurt(); }
    void TimeLastHurtUpdated() override { Real()->m_fTimeLastHurt.NetworkStateChanged(); }
    float& DeathTime() override { return Real()->m_flDeathTime(); }
    void DeathTimeUpdated() override { Real()->m_flDeathTime.NetworkStateChanged(); }
    float& NextSuicideTime() override { return Real()->m_fNextSuicideTime(); }
    void NextSuicideTimeUpdated() override { Real()->m_fNextSuicideTime.NetworkStateChanged(); }
    bool& InitHUD() override { return Real()->m_fInitHUD(); }
    void InitHUDUpdated() override { Real()->m_fInitHUD.NetworkStateChanged(); }
    CAI_Expresser*& Expresser() override { return Real()->m_pExpresser(); }
    void ExpresserUpdated() override { Real()->m_pExpresser.NetworkStateChanged(); }
    CHandle<CBasePlayerController>& Controller() override { return Real()->m_hController(); }
    void ControllerUpdated() override { Real()->m_hController.NetworkStateChanged(); }
    CHandle<CBasePlayerController>& DefaultController() override { return Real()->m_hDefaultController(); }
    void DefaultControllerUpdated() override { Real()->m_hDefaultController.NetworkStateChanged(); }
    float& HltvReplayDelay() override { return Real()->m_fHltvReplayDelay(); }
    void HltvReplayDelayUpdated() override { Real()->m_fHltvReplayDelay.NetworkStateChanged(); }
    float& HltvReplayEnd() override { return Real()->m_fHltvReplayEnd(); }
    void HltvReplayEndUpdated() override { Real()->m_fHltvReplayEnd.NetworkStateChanged(); }
    CEntityIndex& HltvReplayEntity() override { return Real()->m_iHltvReplayEntity(); }
    void HltvReplayEntityUpdated() override { Real()->m_iHltvReplayEntity.NetworkStateChanged(); }
    CUtlVector<sndopvarlatchdata_t>& SndOpvarLatchData() override { return Real()->m_sndOpvarLatchData(); }
    void SndOpvarLatchDataUpdated() override { Real()->m_sndOpvarLatchData.NetworkStateChanged(); }

    void CommitSuicide(bool bExplode, bool bForce) override { Real()->CommitSuicide(bExplode, bForce); }
    void RemovePlayerItem(CBasePlayerWeapon* pWeapon) override { Real()->RemovePlayerItem(pWeapon); }
};

#endif // _INCLUDE_CBASEPLAYERPAWNIMPL_H
