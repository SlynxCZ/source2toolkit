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

#ifndef _INCLUDE_CCOLORCORRECTIONVOLUMEIMPL_H
#define _INCLUDE_CCOLORCORRECTIONVOLUMEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IColorCorrectionVolume.h"
#include "schema/entity/classes/CColorCorrectionVolume.h"
#include "CBaseTriggerImpl.h"

class CColorCorrectionVolumeImpl : public CBaseTriggerImpl, public IColorCorrectionVolume
{

public:
    explicit CColorCorrectionVolumeImpl(CColorCorrectionVolume* p) : CBaseTriggerImpl(p) {}

private:
    CColorCorrectionVolume* Real() { return static_cast<CColorCorrectionVolume*>(m_pReal); }

public:
    float& MaxWeight() override { return Real()->m_MaxWeight(); }
    void MaxWeightUpdated() override { Real()->m_MaxWeight.NetworkStateChanged(); }
    float& FadeDuration() override { return Real()->m_FadeDuration(); }
    void FadeDurationUpdated() override { Real()->m_FadeDuration.NetworkStateChanged(); }
    float& Weight() override { return Real()->m_Weight(); }
    void WeightUpdated() override { Real()->m_Weight.NetworkStateChanged(); }
    char* LookupFilename() override { return Real()->m_lookupFilename(); }
    float& LastEnterWeight() override { return Real()->m_LastEnterWeight(); }
    void LastEnterWeightUpdated() override { Real()->m_LastEnterWeight.NetworkStateChanged(); }
    float& LastEnterTime() override { return Real()->m_LastEnterTime(); }
    void LastEnterTimeUpdated() override { Real()->m_LastEnterTime.NetworkStateChanged(); }
    float& LastExitWeight() override { return Real()->m_LastExitWeight(); }
    void LastExitWeightUpdated() override { Real()->m_LastExitWeight.NetworkStateChanged(); }
    float& LastExitTime() override { return Real()->m_LastExitTime(); }
    void LastExitTimeUpdated() override { Real()->m_LastExitTime.NetworkStateChanged(); }
};

#endif // _INCLUDE_CCOLORCORRECTIONVOLUMEIMPL_H
