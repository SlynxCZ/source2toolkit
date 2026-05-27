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

#ifndef _INCLUDE_CFOGVOLUMEIMPL_H
#define _INCLUDE_CFOGVOLUMEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IFogVolume.h"
#include "schema/entity/classes/CFogVolume.h"
#include "CServerOnlyModelEntityImpl.h"

class CFogVolumeImpl : public CServerOnlyModelEntityImpl, public IFogVolume
{

public:
    explicit CFogVolumeImpl(CFogVolume* p) : CServerOnlyModelEntityImpl(p) {}

private:
    CFogVolume* Real() { return static_cast<CFogVolume*>(m_pReal); }

public:
    CUtlSymbolLarge& FogName() override { return Real()->m_fogName(); }
    void FogNameUpdated() override { Real()->m_fogName.NetworkStateChanged(); }
    CUtlSymbolLarge& PostProcessName() override { return Real()->m_postProcessName(); }
    void PostProcessNameUpdated() override { Real()->m_postProcessName.NetworkStateChanged(); }
    CUtlSymbolLarge& ColorCorrectionName() override { return Real()->m_colorCorrectionName(); }
    void ColorCorrectionNameUpdated() override { Real()->m_colorCorrectionName.NetworkStateChanged(); }
    bool& Disabled() override { return Real()->m_bDisabled(); }
    void DisabledUpdated() override { Real()->m_bDisabled.NetworkStateChanged(); }
    bool& InFogVolumesList() override { return Real()->m_bInFogVolumesList(); }
    void InFogVolumesListUpdated() override { Real()->m_bInFogVolumesList.NetworkStateChanged(); }
};

#endif // _INCLUDE_CFOGVOLUMEIMPL_H
