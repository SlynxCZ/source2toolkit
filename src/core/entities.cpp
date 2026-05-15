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
#include "entities.h"

#include "addresses.h"
#include "commands.h"
#include "events.h"
#include "shared.h"

#include "source2toolkit/utils/plat.h"
#include "source2toolkit/schema/entityio.h"
#include "source2toolkit/schema/entity/classes/CBeam.h"

namespace entities
{
    EntitiesManager entitiesManager;

    CBaseEntity* EntitiesManager::FindPickerEntity(CBasePlayerController* pPlayer, CCSGameRules* pGameRules)
    {
        return UTIL_FindPickerEntity(pPlayer, pGameRules);
    }

    CBaseEntity* EntitiesManager::FindEntityByClassname(CEntityInstance* pStart, const char* name)
    {
        return UTIL_FindEntityByClassname(pStart, name);
    }

    CBaseEntity* EntitiesManager::FindEntityByName(CEntityInstance* pStartEntity, const char* szName, CEntityInstance* pSearchingEntity, CEntityInstance* pActivator, CEntityInstance* pCaller, IEntityFindFilter* pFilter)
    {
        return UTIL_FindEntityByName(pStartEntity, szName, pSearchingEntity, pActivator, pCaller, pFilter);
    }

    CBaseEntity* EntitiesManager::CreateEntityByName(const char* pszClassName)
    {
        return UTIL_CreateEntityByName(pszClassName);
    }

    void EntitiesManager::AddEntityListener(IEntityListener* pListener)
    {
        UTIL_AddEntityListener(pListener);
    }

    void EntitiesManager::RemoveEntityListener(IEntityListener* pListener)
    {
        UTIL_RemoveEntityListener(pListener);
    }

    void EntitiesManager::AcceptInput(CEntityInstance* pTarget, const char* pszInput, CEntityInstance* pActivator, CEntityInstance* pCaller, const char* pszValue)
    {
        return UTIL_AcceptInput(pTarget, pszInput, pActivator, pCaller, pszValue);
    }

    void EntitiesManager::AddEntityIOEvent(CEntityInstance* pTarget, const char* pszInput, CEntityInstance* pActivator, CEntityInstance* pCaller, const char* pszValue, float flDelay)
    {
        return UTIL_AddEntityIOEvent(pTarget, pszInput, pActivator, pCaller, pszValue, flDelay);
    }

    void EntitiesManager::AddEntityIOListener(IEntityIOListener* pListener, const char* pchClassName, const char* pchOutputName, Mode nMode)
    {
        UTIL_AddEntityIOListener(pListener, pchClassName, pchOutputName, nMode);
    }

    void EntitiesManager::RemoveEntityIOListener(IEntityIOListener* pListener, const char* pchClassName, const char* pchOutputName, Mode nMode)
    {
        UTIL_RemoveEntityIOListener(pListener, pchClassName, pchOutputName, nMode);
    }
}
