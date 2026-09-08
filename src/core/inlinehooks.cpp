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
#include "networkmessages.h"
#include "plugin.h"
#include "shared.h"
#include "source2toolkit/utils/plat.h"
#include "core/scheduler.h"
#include "source2toolkit/schema/serversideclient.h"
#include "dynlibutils/module.hpp"
#include "iserver.h"

#include <unordered_set>

namespace inlinehooks
{
    Inlines inlines;
    std::unordered_map<OutputKey, EntityIOCallbackPair, OutputKeyHash> entityIOListenerStack;

    Inlines::Inlines() :
        // bool INetworkMessageProcessingPreFilter::FilterMessage(const CNetMessage* pData, INetChannel* pChannel)
        KHOOK_NEW(m_hFilterMessage, this, &Inlines::Hook_FilterMessage, nullptr),
        // void CEntityIOOutput::FireOutputInternal(CEntityInstance* pActivator, CEntityInstance* pCaller, void* variantValue, float delay, void* unk01, void* unk02)
        KHOOK_NEW(m_hFireOutputInternal, this, &Inlines::Hook_FireOutputInternal, nullptr)
    {
    }

    void Inlines::InitListeners()
    {
        // Configure() is what places the detour; an address the scan did not
        // find leaves that hook dormant rather than patching address zero.
        if (void* pFilterMessage = addresses::toolkitAddresses.FilterMessage.GetPtr())
            m_hFilterMessage->Configure(pFilterMessage);

        if (void* pFireOutputInternal = addresses::toolkitAddresses.FireOutputInternal.GetPtr())
            m_hFireOutputInternal->Configure(pFireOutputInternal);
    }

    void Inlines::DestructListeners()
    {
        delete m_hFilterMessage;
        delete m_hFireOutputInternal;
        m_hFilterMessage = nullptr;
        m_hFireOutputInternal = nullptr;
    }

    KHook::Return<bool> Inlines::Hook_FilterMessage(INetworkMessageProcessingPreFilterCustom* pThis, const CNetMessage* pData, INetChannel* pChannel)
    {
        //  is the pre-filter subobject, not the whole client -- that is
        // what INetworkMessageProcessingPreFilterCustom's pad-based layout is
        // for, so the slot can be read without hand-rolling the delta.
        if (!pThis || !pData)
            return { KHook::Action::Ignore, true };

        INetworkMessageInternal* pNetMsg = pData->GetNetMessage();
        if (!pNetMsg)
            return { KHook::Action::Ignore, true };

        NetMessageInfo_t* pInfo = pNetMsg->GetNetMessageInfo();
        if (!pInfo)
            return { KHook::Action::Ignore, true };

        const Action action = networkmessages::DispatchClientHook(pThis->GetPlayerSlot(), pInfo->m_MessageId, const_cast<CNetMessage*>(pData));

        return { static_cast<KHook::Action>(action), true };
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

        Action finalAction = Action::Ignore;

        for (auto* pair : matched)
        {
            for (auto* listener : pair->m_vecPre)
            {
                auto action = listener->OnEntityOutput(
                    outputName,
                    pActivator,
                    pCaller,
                    delay,
                    false
                );

                if (action == Action::Supersede)
                    return { KHook::Action::Supercede };

                if (action > finalAction)
                    finalAction = action;
            }
        }

        if (finalAction != Action::Supersede)
        {
            m_hFireOutputInternal->CallOriginal(pThis, pActivator, pCaller, variantValue, delay, unk01, unk02);
        }

        for (auto* pair : matched)
        {
            for (auto* listener : pair->m_vecPost)
            {
                listener->OnEntityOutput(outputName, pActivator, pCaller, delay, true);
            }
        }

        // The original already ran above, so supersede rather than let KHook
        // call it a second time.
        return { KHook::Action::Supercede };
    }
}
