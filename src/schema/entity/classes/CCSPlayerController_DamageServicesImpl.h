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

#ifndef _INCLUDE_CCSPLAYERCONTROLLER_DAMAGESERVICESIMPL_H
#define _INCLUDE_CCSPLAYERCONTROLLER_DAMAGESERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayerController_DamageServices.h"
#include "schema/entity/classes/CCSPlayerController_DamageServices.h"
#include "CPlayerControllerComponentImpl.h"

class CCSPlayerController_DamageServicesImpl : public CPlayerControllerComponentImpl, public ICSPlayerController_DamageServices
{

public:
    explicit CCSPlayerController_DamageServicesImpl(CCSPlayerController_DamageServices* p) : CPlayerControllerComponentImpl(p) {}

private:
    CCSPlayerController_DamageServices* Real() { return static_cast<CCSPlayerController_DamageServices*>(m_pReal); }

public:
    int32_t& SendUpdate() override { return Real()->m_nSendUpdate(); }
    void SendUpdateUpdated() override { Real()->m_nSendUpdate.NetworkStateChanged(); }
    CUtlVector<CDamageRecord>& DamageList() override { return Real()->m_DamageList(); }
    void DamageListUpdated() override { Real()->m_DamageList.NetworkStateChanged(); }
};

#endif // _INCLUDE_CCSPLAYERCONTROLLER_DAMAGESERVICESIMPL_H
