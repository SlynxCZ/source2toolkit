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
#include "inlinehooks.h"

#include "addresses.h"
#include "commands.h"
#include "events.h"
#include "shared.h"
#include "source2toolkit/utils/plat.h"
#include "utils/scheduler.h"
#include "dynlibutils/module.h"
#include "iserver.h"
#include "schema/cgameresourceserviceserver.h"
#include "source2toolkit/schema/entity/classes/CCSGameRulesProxy.h"

namespace inlinehooks
{
    Inlines inlines;
    std::unordered_map<OutputKey, EntityIOCallbackPair, OutputKeyHash> entityIOListenerStack;

    Inlines::Inlines() :
        m_FireOutputInternal(this, &Inlines::Hook_FireOutputInternal, nullptr),
        m_PlatDebug(this, &Inlines::Hook_PlatDebug, nullptr)
    {
    }

    void Inlines::InitListeners()
    {
        m_FireOutputInternal.Configure(addresses::toolkitAddresses.FireOutputInternal);

        auto platDebugAddr = DynLibUtils::CModule("tier0").GetFunctionByName("Plat_DebugString_Buffered").RCast<void (*)(void*, void*)>();
        if (platDebugAddr)
        {
            m_PlatDebug.Configure(platDebugAddr);
        }
    }

    void Inlines::DestructListeners()
    {
        m_FireOutputInternal.~Function();
        m_PlatDebug.~Function();
    }

    KHook::Return<void> Inlines::Hook_FireOutputInternal(CEntityIOOutput* pThis, CEntityInstance* pActivator, CEntityInstance* pCaller, void* variantValue, float delay, void* unk01, void* unk02)
    {
        const char* outputName = pThis->m_pDesc->m_pName;
        const char* callerClass = pCaller ? pCaller->GetClassname() : "*";

        std::vector<OutputKey> searchKeys{
            {"*", outputName},
            {"*", "*"}
        };

        if (pCaller)
        {
            searchKeys.push_back({callerClass, outputName});
            searchKeys.push_back({callerClass, "*"});
        }

        std::unordered_set<EntityIOCallbackPair*> unique;

        for (auto& key : searchKeys)
        {
            auto it = entityIOListenerStack.find(key);
            if (it != entityIOListenerStack.end())
                unique.insert(&it->second);
        }

        std::vector matched(unique.begin(), unique.end());

        KHook::Action finalAction = KHook::Action::Ignore;

        for (auto* pair : matched)
        {
            for (auto* listener : pair->m_vecPre)
            {
                auto action = listener->OnEntityOutput(
                    outputName,
                    pActivator,
                    pCaller,
                    delay,
                    Mode::Pre
                );

                if (action == Action::Supersede)
                    return {KHook::Action::Supersede};

                if (static_cast<KHook::Action>(action) > finalAction)
                    finalAction = static_cast<KHook::Action>(action);
            }
        }

        if (finalAction != KHook::Action::Supersede)
        {
            m_FireOutputInternal.CallOriginal(
                pThis, pActivator, pCaller, variantValue, delay, unk01, unk02
            );
        }

        for (auto* pair : matched)
        {
            for (auto* listener : pair->m_vecPost)
            {
                listener->OnEntityOutput(
                    outputName,
                    pActivator,
                    pCaller,
                    delay,
                    Mode::Post
                );
            }
        }

        return {KHook::Action::Supersede};
    }

    KHook::Return<void> Inlines::Hook_PlatDebug(void* unk001, void* unk002)
    {
        if (!unk001)
            return { KHook::Action::Supersede };

        return { KHook::Action::Ignore };
    }
}
