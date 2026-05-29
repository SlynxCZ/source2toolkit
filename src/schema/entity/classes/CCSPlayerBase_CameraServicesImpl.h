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

#ifndef _INCLUDE_CCSPLAYERBASE_CAMERASERVICESIMPL_H
#define _INCLUDE_CCSPLAYERBASE_CAMERASERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayerBase_CameraServices.h"
#include "schema/entity/classes/CCSPlayerBase_CameraServices.h"
#include "CPlayer_CameraServicesImpl.h"

class CCSPlayerBase_CameraServicesImpl : public CPlayer_CameraServicesImpl, public virtual ICSPlayerBase_CameraServices
{

public:
    explicit CCSPlayerBase_CameraServicesImpl(CCSPlayerBase_CameraServices* p) : CPlayer_CameraServicesImpl(p) {}

private:
    CCSPlayerBase_CameraServices* Real() { return static_cast<CCSPlayerBase_CameraServices*>(m_pReal); }
    CCSPlayerBase_CameraServices* Real() const { return static_cast<CCSPlayerBase_CameraServices*>(m_pReal); }

public:
    CCSPlayerBase_CameraServices* GetOriginal() const override { return Real(); }
    uint32_t& FOV() override { return Real()->m_iFOV(); }
    void FOVUpdated() override { Real()->m_iFOV.NetworkStateChanged(); }
    uint32_t& FOVStart() override { return Real()->m_iFOVStart(); }
    void FOVStartUpdated() override { Real()->m_iFOVStart.NetworkStateChanged(); }
    float& FOVTime() override { return Real()->m_flFOVTime(); }
    void FOVTimeUpdated() override { Real()->m_flFOVTime.NetworkStateChanged(); }
    float& FOVRate() override { return Real()->m_flFOVRate(); }
    void FOVRateUpdated() override { Real()->m_flFOVRate.NetworkStateChanged(); }
    CHandle<CBaseEntity>& ZoomOwner() override { return Real()->m_hZoomOwner(); }
    void ZoomOwnerUpdated() override { Real()->m_hZoomOwner.NetworkStateChanged(); }
    CUtlVector<CHandle<CBaseEntity>>& TriggerFogList() override { return Real()->m_hTriggerFogList(); }
    void TriggerFogListUpdated() override { Real()->m_hTriggerFogList.NetworkStateChanged(); }
    CHandle<CBaseEntity>& LastFogTrigger() override { return Real()->m_hLastFogTrigger(); }
    void LastFogTriggerUpdated() override { Real()->m_hLastFogTrigger.NetworkStateChanged(); }
};

inline ICSPlayerBase_CameraServices* CCSPlayerBase_CameraServices::ToInterface() { return new CCSPlayerBase_CameraServicesImpl(this); }
inline ICSPlayerBase_CameraServices* ICSPlayerBase_CameraServices::FromRaw(CEntityInstance*) { return nullptr; }
inline ICSPlayerBase_CameraServices* ICSPlayerBase_CameraServices::FromOriginal(CCSPlayerBase_CameraServices* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSPLAYERBASE_CAMERASERVICESIMPL_H
