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

#ifndef _INCLUDE_CENVWINDVOLUMEIMPL_H
#define _INCLUDE_CENVWINDVOLUMEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvWindVolume.h"
#include "schema/entity/classes/CEnvWindVolume.h"
#include "CBaseEntityImpl.h"

class CEnvWindVolumeImpl : public CBaseEntityImpl, public IEnvWindVolume
{

public:
    explicit CEnvWindVolumeImpl(CEnvWindVolume* p) : CBaseEntityImpl(p) {}

private:
    CEnvWindVolume* Real() { return static_cast<CEnvWindVolume*>(m_pReal); }

public:
    bool& Active() override { return Real()->m_bActive(); }
    void ActiveUpdated() override { Real()->m_bActive.NetworkStateChanged(); }
    Vector& BoxMins() override { return Real()->m_vBoxMins(); }
    void BoxMinsUpdated() override { Real()->m_vBoxMins.NetworkStateChanged(); }
    Vector& BoxMaxs() override { return Real()->m_vBoxMaxs(); }
    void BoxMaxsUpdated() override { Real()->m_vBoxMaxs.NetworkStateChanged(); }
    bool& StartDisabled() override { return Real()->m_bStartDisabled(); }
    void StartDisabledUpdated() override { Real()->m_bStartDisabled.NetworkStateChanged(); }
    int32_t& Shape() override { return Real()->m_nShape(); }
    void ShapeUpdated() override { Real()->m_nShape.NetworkStateChanged(); }
    float& WindSpeedMultiplier() override { return Real()->m_fWindSpeedMultiplier(); }
    void WindSpeedMultiplierUpdated() override { Real()->m_fWindSpeedMultiplier.NetworkStateChanged(); }
    float& WindTurbulenceMultiplier() override { return Real()->m_fWindTurbulenceMultiplier(); }
    void WindTurbulenceMultiplierUpdated() override { Real()->m_fWindTurbulenceMultiplier.NetworkStateChanged(); }
    float& WindSpeedVariationMultiplier() override { return Real()->m_fWindSpeedVariationMultiplier(); }
    void WindSpeedVariationMultiplierUpdated() override { Real()->m_fWindSpeedVariationMultiplier.NetworkStateChanged(); }
    float& WindDirectionVariationMultiplier() override { return Real()->m_fWindDirectionVariationMultiplier(); }
    void WindDirectionVariationMultiplierUpdated() override { Real()->m_fWindDirectionVariationMultiplier.NetworkStateChanged(); }
};

#endif // _INCLUDE_CENVWINDVOLUMEIMPL_H
