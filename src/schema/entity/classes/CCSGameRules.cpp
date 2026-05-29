/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
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
 * As a special exception, Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl and
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
 *   - Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl
 *   - AlliedModders LLC
 *
 * Project: Source2Toolkit
 */

#include "schema/entity/classes/CCSGameRulesImpl.h"
#include "schema/entity/classes/CCSPlayerController.h"
#include "schema/entity/classes/CCSPlayerPawn.h"

#include "source2toolkit/schema/entity/classes/ICSPlayerController.h"
#include "source2toolkit/schema/entity/classes/ICSPlayerPawn.h"

#include "core/addresses.h"
#include "core/entities.h"
#include "core/gameconfig.h"
#include "core/shared.h"
#include "core/virtualhooks.h"

void CCSGameRules::TerminateRound(float flDelay, int32_t eRoundEndReason)
{
    addresses::toolkitAddresses.TerminateRound(this, flDelay, eRoundEndReason, 0, 0);
}

IBaseEntity* CCSGameRules::FindPickerEntity(IBasePlayerController* pPlayer)
{
    return entities::entitiesManager.FindPickerEntity(pPlayer, this->ToInterface());
}

ICSPlayerController* CCSGameRules::GetClientAimTarget(ICSPlayerController* pPlayer)
{
    auto* pEntity = FindPickerEntity(pPlayer);
    if (!pEntity || V_strcmp(pEntity->GetClassname(), "player") != 0) return nullptr;

    auto* pPawn = static_cast<CCSPlayerPawn*>(pEntity->GetOriginal());
    auto* pController = static_cast<CCSPlayerController*>(pPawn->m_hController().Get());
    return pController ? pController->ToInterface() : nullptr;
}
ICSGameRules* CCSGameRules::ToInterface()
{ return new CCSGameRulesImpl(this); }

ICSGameRules* ICSGameRules::FromRaw(CEntityInstance* p)
{ return nullptr; }

ICSGameRules* ICSGameRules::FromOriginal(CCSGameRules* p)
{ return CCSGameRules::FromOriginal(p); }
