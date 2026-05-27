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

#ifndef _INCLUDE_CBASEPLATTRAINIMPL_H
#define _INCLUDE_CBASEPLATTRAINIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBasePlatTrain.h"
#include "schema/entity/classes/CBasePlatTrain.h"
#include "CBaseToggleImpl.h"

class CBasePlatTrainImpl : public CBaseToggleImpl, public IBasePlatTrain
{

public:
    explicit CBasePlatTrainImpl(CBasePlatTrain* p) : CBaseToggleImpl(p) {}

private:
    CBasePlatTrain* Real() { return static_cast<CBasePlatTrain*>(m_pReal); }

public:
    CUtlSymbolLarge& NoiseMoving() override { return Real()->m_NoiseMoving(); }
    void NoiseMovingUpdated() override { Real()->m_NoiseMoving.NetworkStateChanged(); }
    CUtlSymbolLarge& NoiseArrived() override { return Real()->m_NoiseArrived(); }
    void NoiseArrivedUpdated() override { Real()->m_NoiseArrived.NetworkStateChanged(); }
    float& Volume() override { return Real()->m_volume(); }
    void VolumeUpdated() override { Real()->m_volume.NetworkStateChanged(); }
    float& TWidth() override { return Real()->m_flTWidth(); }
    void TWidthUpdated() override { Real()->m_flTWidth.NetworkStateChanged(); }
    float& TLength() override { return Real()->m_flTLength(); }
    void TLengthUpdated() override { Real()->m_flTLength.NetworkStateChanged(); }
};

#endif // _INCLUDE_CBASEPLATTRAINIMPL_H
