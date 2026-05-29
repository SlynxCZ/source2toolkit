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

#include "schema/entity/classes/CBaseEntity.h"

#include "source2toolkit/schema/entityio.h"
#include "source2toolkit/schema/entity/classes/IEntityInstance.h"
#include "source2toolkit/utils/plat.h"
#include "source2toolkit/utils/virtual.h"

namespace entities
{
    EntitiesManager entitiesManager;

    IBaseEntity* EntitiesManager::FindPickerEntity(IBasePlayerController* pPlayer, ICSGameRules* pGameRules)
    {
        static int offset = shared::g_pGameConfig->GetOffset("CGameRules_FindPickerEntity");
        auto* gr = pGameRules ? pGameRules->GetOriginal() : static_cast<CBaseEntity*>(shared::g_pGameRules);
        return CALL_VIRTUAL(CBaseEntity*, offset, gr, pPlayer ? pPlayer->GetOriginal() : nullptr, nullptr)->ToInterface();
    }

    IBaseEntity* EntitiesManager::FindEntityByClassname(IEntityInstance* pStart, const char* name)
    {
        return addresses::toolkitAddresses.FindEntityByClassName(shared::g_pEntitySystem, pStart->GetOriginal(), name)->ToInterface();
    }

    IBaseEntity* EntitiesManager::FindEntityByName(IEntityInstance* pStartEntity, const char* szName, IEntityInstance* pSearchingEntity, IEntityInstance* pActivator, IEntityInstance* pCaller, IEntityFindFilter* pFilter)
    {
        return addresses::toolkitAddresses.FindEntityByName(shared::g_pEntitySystem, pStartEntity->GetOriginal(), szName, pSearchingEntity->GetOriginal(), pActivator->GetOriginal(), pCaller->GetOriginal(), pFilter)->ToInterface();
    }

    IBaseEntity* EntitiesManager::CreateEntityByName(const char* pszClassName)
    {
        return addresses::toolkitAddresses.CreateEntityByName(pszClassName, -1)->ToInterface();
    }

    void EntitiesManager::AddEntityListener(IEntityListener* pListener)
    {
        shared::g_pEntitySystem->AddListenerEntity(pListener);
    }

    void EntitiesManager::RemoveEntityListener(IEntityListener* pListener)
    {
        shared::g_pEntitySystem->RemoveListenerEntity(pListener);
    }

    void EntitiesManager::AcceptInput(IEntityInstance* pTarget, const char* pszInput, IEntityInstance* pActivator, IEntityInstance* pCaller, const char* pszValue)
    {
        addresses::toolkitAddresses.AcceptInput(pTarget->GetOriginal(), pszInput, pActivator->GetOriginal(), pCaller->GetOriginal(), variant_t(pszValue), 0, nullptr);
    }

    void EntitiesManager::AddEntityIOEvent(IEntityInstance* pTarget, const char* pszInput, IEntityInstance* pActivator, IEntityInstance* pCaller, const char* pszValue, float flDelay)
    {
        addresses::toolkitAddresses.AddEntityIOEvent(shared::g_pEntitySystem, pTarget->GetOriginal(), pszInput, pActivator->GetOriginal(), pCaller->GetOriginal(), variant_t(pszValue), flDelay, 0, nullptr, nullptr);
    }

    void EntitiesManager::AddEntityIOListener(IEntityIOListener* pListener, const char* pchClassName, const char* pchOutputName, Mode nMode)
    {
        OutputKey key{
            pchClassName ? pchClassName : "*",
            pchOutputName ? pchOutputName : "*"
        };

        if (nMode == Mode::Post)
            inlinehooks::entityIOListenerStack[key].m_vecPost.push_back(pListener);
        else
            inlinehooks::entityIOListenerStack[key].m_vecPre.push_back(pListener);
    }

    void EntitiesManager::RemoveEntityIOListener(IEntityIOListener* pListener, const char* pchClassName, const char* pchOutputName, Mode nMode)
    {
        if (!pchClassName && !pchOutputName)
        {
            for (auto it = inlinehooks::entityIOListenerStack.begin(); it != inlinehooks::entityIOListenerStack.end(); )
            {
                auto& vec = nMode == Mode::Post ? it->second.m_vecPost : it->second.m_vecPre;

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

        auto& vec = nMode == Mode::Post ? it->second.m_vecPost : it->second.m_vecPre;

        std::erase(vec, pListener);

        if (it->second.m_vecPre.empty() && it->second.m_vecPost.empty())
            inlinehooks::entityIOListenerStack.erase(it);
    }
}
