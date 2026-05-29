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

#ifndef _INCLUDE_CENVWINDSHAREDIMPL_H
#define _INCLUDE_CENVWINDSHAREDIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvWindShared.h"
#include "schema/entity/classes/CEnvWindShared.h"

class CEnvWindSharedImpl : public virtual IEnvWindShared
{

protected:
    void* m_pReal;

public:
    explicit CEnvWindSharedImpl(void* p) : m_pReal(p) {}

private:
    CEnvWindShared* Real() { return static_cast<CEnvWindShared*>(m_pReal); }
    CEnvWindShared* Real() const { return static_cast<CEnvWindShared*>(m_pReal); }

public:
    CEnvWindShared* GetOriginal() const override { return Real(); }
    float& StartTime() override { return Real()->m_flStartTime(); }
    void StartTimeUpdated() override { Real()->m_flStartTime.NetworkStateChanged(); }
    uint32_t& WindSeed() override { return Real()->m_iWindSeed(); }
    void WindSeedUpdated() override { Real()->m_iWindSeed.NetworkStateChanged(); }
    uint16_t& MinWind() override { return Real()->m_iMinWind(); }
    void MinWindUpdated() override { Real()->m_iMinWind.NetworkStateChanged(); }
    uint16_t& MaxWind() override { return Real()->m_iMaxWind(); }
    void MaxWindUpdated() override { Real()->m_iMaxWind.NetworkStateChanged(); }
    int32_t& WindRadius() override { return Real()->m_windRadius(); }
    void WindRadiusUpdated() override { Real()->m_windRadius.NetworkStateChanged(); }
    uint16_t& MinGust() override { return Real()->m_iMinGust(); }
    void MinGustUpdated() override { Real()->m_iMinGust.NetworkStateChanged(); }
    uint16_t& MaxGust() override { return Real()->m_iMaxGust(); }
    void MaxGustUpdated() override { Real()->m_iMaxGust.NetworkStateChanged(); }
    float& MinGustDelay() override { return Real()->m_flMinGustDelay(); }
    void MinGustDelayUpdated() override { Real()->m_flMinGustDelay.NetworkStateChanged(); }
    float& MaxGustDelay() override { return Real()->m_flMaxGustDelay(); }
    void MaxGustDelayUpdated() override { Real()->m_flMaxGustDelay.NetworkStateChanged(); }
    float& GustDuration() override { return Real()->m_flGustDuration(); }
    void GustDurationUpdated() override { Real()->m_flGustDuration.NetworkStateChanged(); }
    uint16_t& GustDirChange() override { return Real()->m_iGustDirChange(); }
    void GustDirChangeUpdated() override { Real()->m_iGustDirChange.NetworkStateChanged(); }
    uint16_t& InitialWindDir() override { return Real()->m_iInitialWindDir(); }
    void InitialWindDirUpdated() override { Real()->m_iInitialWindDir.NetworkStateChanged(); }
    float& InitialWindSpeed() override { return Real()->m_flInitialWindSpeed(); }
    void InitialWindSpeedUpdated() override { Real()->m_flInitialWindSpeed.NetworkStateChanged(); }
    Vector& Location() override { return Real()->m_location(); }
    void LocationUpdated() override { Real()->m_location.NetworkStateChanged(); }
    CEntityIOOutput& OnGustStart() override { return Real()->m_OnGustStart(); }
    void OnGustStartUpdated() override { Real()->m_OnGustStart.NetworkStateChanged(); }
    CEntityIOOutput& OnGustEnd() override { return Real()->m_OnGustEnd(); }
    void OnGustEndUpdated() override { Real()->m_OnGustEnd.NetworkStateChanged(); }
    CHandle<CBaseEntity>& EntOwner() override { return Real()->m_hEntOwner(); }
    void EntOwnerUpdated() override { Real()->m_hEntOwner.NetworkStateChanged(); }
};

inline IEnvWindShared* CEnvWindShared::ToInterface() { return new CEnvWindSharedImpl(this); }
inline IEnvWindShared* IEnvWindShared::FromOriginal(CEnvWindShared* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CENVWINDSHAREDIMPL_H
