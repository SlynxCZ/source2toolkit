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

#ifndef _INCLUDE_CPLAYER_CAMERASERVICESIMPL_H
#define _INCLUDE_CPLAYER_CAMERASERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPlayer_CameraServices.h"
#include "schema/entity/classes/CPlayer_CameraServices.h"
#include "CPlayerPawnComponentImpl.h"

class CPlayer_CameraServicesImpl : public CPlayerPawnComponentImpl, public IPlayer_CameraServices
{

public:
    explicit CPlayer_CameraServicesImpl(CPlayer_CameraServices* p) : CPlayerPawnComponentImpl(p) {}

private:
    CPlayer_CameraServices* Real() { return static_cast<CPlayer_CameraServices*>(m_pReal); }
    CPlayer_CameraServices* Real() const { return static_cast<CPlayer_CameraServices*>(m_pReal); }

public:
    CPlayer_CameraServices* GetOriginal() const override { return Real(); }
    QAngle& CsViewPunchAngle() override { return Real()->m_vecCsViewPunchAngle(); }
    void CsViewPunchAngleUpdated() override { Real()->m_vecCsViewPunchAngle.NetworkStateChanged(); }
    int32_t& CsViewPunchAngleTick() override { return Real()->m_nCsViewPunchAngleTick(); }
    void CsViewPunchAngleTickUpdated() override { Real()->m_nCsViewPunchAngleTick.NetworkStateChanged(); }
    float& CsViewPunchAngleTickRatio() override { return Real()->m_flCsViewPunchAngleTickRatio(); }
    void CsViewPunchAngleTickRatioUpdated() override { Real()->m_flCsViewPunchAngleTickRatio.NetworkStateChanged(); }
    ::fogplayerparams_t& PlayerFog() override { return Real()->m_PlayerFog(); }
    void PlayerFogUpdated() override { Real()->m_PlayerFog.NetworkStateChanged(); }
    CHandle<CColorCorrection>& ColorCorrectionCtrl() override { return Real()->m_hColorCorrectionCtrl(); }
    void ColorCorrectionCtrlUpdated() override { Real()->m_hColorCorrectionCtrl.NetworkStateChanged(); }
    CHandle<CBaseEntity>& ViewEntity() override { return Real()->m_hViewEntity(); }
    void ViewEntityUpdated() override { Real()->m_hViewEntity.NetworkStateChanged(); }
    CHandle<CTonemapController2>& TonemapController() override { return Real()->m_hTonemapController(); }
    void TonemapControllerUpdated() override { Real()->m_hTonemapController.NetworkStateChanged(); }
    ::audioparams_t& Audio() override { return Real()->m_audio(); }
    void AudioUpdated() override { Real()->m_audio.NetworkStateChanged(); }
    CUtlVector<CHandle<CPostProcessingVolume>>& PostProcessingVolumes() override { return Real()->m_PostProcessingVolumes(); }
    void PostProcessingVolumesUpdated() override { Real()->m_PostProcessingVolumes.NetworkStateChanged(); }
    float& OldPlayerZ() override { return Real()->m_flOldPlayerZ(); }
    void OldPlayerZUpdated() override { Real()->m_flOldPlayerZ.NetworkStateChanged(); }
    float& OldPlayerViewOffsetZ() override { return Real()->m_flOldPlayerViewOffsetZ(); }
    void OldPlayerViewOffsetZUpdated() override { Real()->m_flOldPlayerViewOffsetZ.NetworkStateChanged(); }
    CUtlVector<CHandle<CEnvSoundscapeTriggerable>>& TriggerSoundscapeList() override { return Real()->m_hTriggerSoundscapeList(); }
    void TriggerSoundscapeListUpdated() override { Real()->m_hTriggerSoundscapeList.NetworkStateChanged(); }
};

inline IPlayer_CameraServices* CPlayer_CameraServices::ToInterface() { return new CPlayer_CameraServicesImpl(this); }
inline IPlayer_CameraServices* IPlayer_CameraServices::FromOriginal(CPlayer_CameraServices* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPLAYER_CAMERASERVICESIMPL_H
