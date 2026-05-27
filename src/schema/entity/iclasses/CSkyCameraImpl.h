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

#ifndef _INCLUDE_CSKYCAMERAIMPL_H
#define _INCLUDE_CSKYCAMERAIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/ISkyCamera.h"
#include "schema/entity/classes/CSkyCamera.h"
#include "CBaseEntityImpl.h"

class CSkyCameraImpl : public CBaseEntityImpl, public ISkyCamera
{

public:
    explicit CSkyCameraImpl(CSkyCamera* p) : CBaseEntityImpl(p) {}

private:
    CSkyCamera* Real() { return static_cast<CSkyCamera*>(m_pReal); }

public:
    sky3dparams_t& SkyboxData() override { return Real()->m_skyboxData(); }
    void SkyboxDataUpdated() override { Real()->m_skyboxData.NetworkStateChanged(); }
    CUtlStringToken* SkyboxSlotToken() override { return Real()->m_skyboxSlotToken(); }
    bool& UseAngles() override { return Real()->m_bUseAngles(); }
    void UseAnglesUpdated() override { Real()->m_bUseAngles.NetworkStateChanged(); }
    CSkyCamera*& Next() override { return Real()->m_pNext(); }
    void NextUpdated() override { Real()->m_pNext.NetworkStateChanged(); }
};

#endif // _INCLUDE_CSKYCAMERAIMPL_H
