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

#ifndef _INCLUDE_CPOSTPROCESSINGVOLUMEIMPL_H
#define _INCLUDE_CPOSTPROCESSINGVOLUMEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IPostProcessingVolume.h"
#include "schema/entity/classes/CPostProcessingVolume.h"
#include "CBaseTriggerImpl.h"

class CPostProcessingVolumeImpl : public CBaseTriggerImpl, public IPostProcessingVolume
{

public:
    explicit CPostProcessingVolumeImpl(CPostProcessingVolume* p) : CBaseTriggerImpl(p) {}

private:
    CPostProcessingVolume* Real() { return static_cast<CPostProcessingVolume*>(m_pReal); }

public:
    CStrongHandle<InfoForResourceTypeCPostProcessingResource>& PostSettings() override { return Real()->m_hPostSettings(); }
    void PostSettingsUpdated() override { Real()->m_hPostSettings.NetworkStateChanged(); }
    float& FadeDuration() override { return Real()->m_flFadeDuration(); }
    void FadeDurationUpdated() override { Real()->m_flFadeDuration.NetworkStateChanged(); }
    float& MinLogExposure() override { return Real()->m_flMinLogExposure(); }
    void MinLogExposureUpdated() override { Real()->m_flMinLogExposure.NetworkStateChanged(); }
    float& MaxLogExposure() override { return Real()->m_flMaxLogExposure(); }
    void MaxLogExposureUpdated() override { Real()->m_flMaxLogExposure.NetworkStateChanged(); }
    float& MinExposure() override { return Real()->m_flMinExposure(); }
    void MinExposureUpdated() override { Real()->m_flMinExposure.NetworkStateChanged(); }
    float& MaxExposure() override { return Real()->m_flMaxExposure(); }
    void MaxExposureUpdated() override { Real()->m_flMaxExposure.NetworkStateChanged(); }
    float& ExposureCompensation() override { return Real()->m_flExposureCompensation(); }
    void ExposureCompensationUpdated() override { Real()->m_flExposureCompensation.NetworkStateChanged(); }
    float& ExposureFadeSpeedUp() override { return Real()->m_flExposureFadeSpeedUp(); }
    void ExposureFadeSpeedUpUpdated() override { Real()->m_flExposureFadeSpeedUp.NetworkStateChanged(); }
    float& ExposureFadeSpeedDown() override { return Real()->m_flExposureFadeSpeedDown(); }
    void ExposureFadeSpeedDownUpdated() override { Real()->m_flExposureFadeSpeedDown.NetworkStateChanged(); }
    float& TonemapEVSmoothingRange() override { return Real()->m_flTonemapEVSmoothingRange(); }
    void TonemapEVSmoothingRangeUpdated() override { Real()->m_flTonemapEVSmoothingRange.NetworkStateChanged(); }
    bool& Master() override { return Real()->m_bMaster(); }
    void MasterUpdated() override { Real()->m_bMaster.NetworkStateChanged(); }
    bool& ExposureControl() override { return Real()->m_bExposureControl(); }
    void ExposureControlUpdated() override { Real()->m_bExposureControl.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPOSTPROCESSINGVOLUMEIMPL_H
