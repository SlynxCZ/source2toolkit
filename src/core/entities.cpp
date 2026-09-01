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
#include "inlinehooks.h"
#include "shared.h"

#include "source2toolkit/schema/entity/classes/CBaseEntity.h"
#include "source2toolkit/schema/entity/classes/CBasePlayerController.h"
#include "source2toolkit/schema/entity/classes/CCSGameRules.h"

#include "source2toolkit/schema/entityio.h"

#include "source2toolkit/utils/plat.h"
#include "source2toolkit/utils/virtual.h"

#include <algorithm>

namespace entities
{
    EntitiesManager entitiesManager;

    CCSGameRules* EntitiesManager::GetGameRules()
    {
        // Captured from cs_gamerules by the entity listener, so it is whatever
        // the current map has -- null only before that entity exists.
        return shared::g_pGameRules;
    }

    CBaseEntity* EntitiesManager::FindPickerEntity(CBasePlayerController* pPlayer, CCSGameRules* pGameRules)
    {
        static int offset = shared::g_pGameConfig->GetOffset("CGameRules::FindPickerEntity");
        auto* gr = pGameRules ? pGameRules : shared::g_pGameRules;
        return CALL_VIRTUAL(CBaseEntity*, offset, gr, pPlayer ? pPlayer : nullptr, nullptr);
    }

    CBaseEntity* EntitiesManager::FindEntityByClassname(CEntityInstance* pStart, const char* name)
    {
        // Nothing to search before the first StartupServer.
        if (!shared::g_pEntitySystem)
            return nullptr;

        return addresses::toolkitAddresses.CGameEntitySystem_FindEntityByClassName()(shared::g_pEntitySystem, pStart, name);
    }

    CBaseEntity* EntitiesManager::FindEntityByName(CEntityInstance* pStartEntity, const char* szName, CEntityInstance* pSearchingEntity, CEntityInstance* pActivator, CEntityInstance* pCaller, IEntityFindFilter* pFilter)
    {
        if (!shared::g_pEntitySystem)
            return nullptr;

        return addresses::toolkitAddresses.CGameEntitySystem_FindEntityByName()(shared::g_pEntitySystem, pStartEntity, szName, pSearchingEntity, pActivator, pCaller, pFilter);
    }

    CBaseEntity* EntitiesManager::CreateEntityByName(const char* pszClassName)
    {
        return addresses::toolkitAddresses.CBaseEntity_CreateEntityByName()(pszClassName, -1);
    }

    void EntitiesManager::AddEntityListener(IEntityListener* pListener)
    {
        if (!pListener)
            return;

        if (std::find(m_Listeners.begin(), m_Listeners.end(), pListener) != m_Listeners.end())
            return;

        m_Listeners.push_back(pListener);

        // Null while a plugin is still loading -- the engine has not made the
        // entity system yet. AttachEntityListeners() picks it up on
        // StartupServer.
        if (shared::g_pEntitySystem)
            shared::g_pEntitySystem->AddListenerEntity(pListener);
    }

    void EntitiesManager::RemoveEntityListener(IEntityListener* pListener)
    {
        if (!pListener)
            return;

        std::erase(m_Listeners, pListener);

        if (shared::g_pEntitySystem)
            shared::g_pEntitySystem->RemoveListenerEntity(pListener);
    }

    void EntitiesManager::AttachEntityListeners()
    {
        if (!shared::g_pEntitySystem)
            return;

        // The list is kept, not consumed: a new map can mean a new entity
        // system, and every listener has to be put on that one too.
        for (IEntityListener* pListener : m_Listeners)
            shared::g_pEntitySystem->AddListenerEntity(pListener);
    }

    void EntitiesManager::AcceptInput(CEntityInstance* pTarget, const char* pszInput, CEntityInstance* pActivator, CEntityInstance* pCaller, const char* pszValue)
    {
        addresses::toolkitAddresses.CEntityInstance_AcceptInput()(pTarget, pszInput, pActivator, pCaller, variant_t(pszValue));
    }

    void EntitiesManager::AddEntityIOEvent(CEntityInstance* pTarget, const char* pszInput, CEntityInstance* pActivator, CEntityInstance* pCaller, const char* pszValue, float flDelay)
    {
        if (!shared::g_pEntitySystem)
            return;

        addresses::toolkitAddresses.CEntitySystem_AddEntityIOEvent()(shared::g_pEntitySystem, pTarget, pszInput, pActivator, pCaller, variant_t(pszValue), flDelay, nullptr, nullptr);
    }

    void EntitiesManager::AddEntityIOListener(IEntityIOListener* pListener, const char* pchClassName, const char* pchOutputName, bool post)
    {
        OutputKey key{
            pchClassName ? pchClassName : "*",
            pchOutputName ? pchOutputName : "*"
        };

        if (post)
            inlinehooks::entityIOListenerStack[key].m_vecPost.push_back(pListener);
        else
            inlinehooks::entityIOListenerStack[key].m_vecPre.push_back(pListener);
    }

    void EntitiesManager::RemoveEntityIOListener(IEntityIOListener* pListener, const char* pchClassName, const char* pchOutputName, bool post)
    {
        if (!pchClassName && !pchOutputName)
        {
            for (auto it = inlinehooks::entityIOListenerStack.begin(); it != inlinehooks::entityIOListenerStack.end(); )
            {
                auto& vec = post ? it->second.m_vecPost : it->second.m_vecPre;

                std::erase(vec, pListener);

                if (it->second.m_vecPre.empty() && it->second.m_vecPost.empty())
                    it = inlinehooks::entityIOListenerStack.erase(it);
                else
                    ++it;
            }
            return;
        }

        OutputKey key{
            pchClassName ? pchClassName : "*",
            pchOutputName ? pchOutputName : "*"
        };

        auto it = inlinehooks::entityIOListenerStack.find(key);
        if (it == inlinehooks::entityIOListenerStack.end())
            return;

        auto& vec = post ? it->second.m_vecPost : it->second.m_vecPre;

        std::erase(vec, pListener);

        if (it->second.m_vecPre.empty() && it->second.m_vecPost.empty())
            inlinehooks::entityIOListenerStack.erase(it);
    }
}
