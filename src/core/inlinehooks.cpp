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

// bool INetworkMessageProcessingPreFilter:FilterMessage(const CNetMessage* pData, INetChannel* pChannel)
SH_DECL_INLINEHOOK2(FilterMessage, INetworkMessageProcessingPreFilterCustom, bool, const CNetMessage*, INetChannel*);

// void CEntityIOOutput::FireOutputInternal(CEntityInstance* pActivator, CEntityInstance* pCaller, void* variantValue, float delay, void* unk01, void* unk02)
SH_DECL_INLINEHOOK6_void(FireOutputInternal, CEntityIOOutput, CEntityInstance*, CEntityInstance*, void*, float, void*, void*);

namespace inlinehooks
{
    Inlines inlines;
    std::unordered_map<OutputKey, EntityIOCallbackPair, OutputKeyHash> entityIOListenerStack;

    void Inlines::InitListeners()
    {
        m_iFilterMessageHookID = SH_ADD_INLINEHOOK(FilterMessage, addresses::toolkitAddresses.FilterMessage, SH_MEMBER(this, &Inlines::Hook_FilterMessage), false);
        m_iFireOutputInternalHookID = SH_ADD_INLINEHOOK(FireOutputInternal, addresses::toolkitAddresses.FireOutputInternal, SH_MEMBER(this, &Inlines::Hook_FireOutputInternal), false);
    }

    void Inlines::DestructListeners()
    {
        SH_REMOVE_HOOK_ID(m_iFilterMessageHookID);
        SH_REMOVE_HOOK_ID(m_iFireOutputInternalHookID);
    }

    bool Inlines::Hook_FilterMessage(const CNetMessage* pData, INetChannel* pChannel)
    {
        // `this` is the pre-filter subobject, not the whole client -- that is
        // what INetworkMessageProcessingPreFilterCustom's pad-based layout is
        // for, so the slot can be read without hand-rolling the delta.
        auto* pFilter = META_IFACEPTR(INetworkMessageProcessingPreFilterCustom);
        if (!pFilter || !pData)
            RETURN_META_VALUE(MRES_IGNORED, true);

        INetworkMessageInternal* pNetMsg = pData->GetNetMessage();
        if (!pNetMsg)
            RETURN_META_VALUE(MRES_IGNORED, true);

        NetMessageInfo_t* pInfo = pNetMsg->GetNetMessageInfo();
        if (!pInfo)
            RETURN_META_VALUE(MRES_IGNORED, true);

        const META_RES action = networkmessages::DispatchClientHook(pFilter->GetPlayerSlot(), pInfo->m_MessageId, const_cast<CNetMessage*>(pData));

        RETURN_META_VALUE(action, true);
    }

    void Inlines::Hook_FireOutputInternal(CEntityInstance* pActivator, CEntityInstance* pCaller, void* variantValue, float delay, void* unk01, void* unk02)
    {
        CEntityIOOutput* pThis = META_IFACEPTR(CEntityIOOutput);

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

        META_RES finalAction = MRES_IGNORED;

        for (auto* pair : matched)
        {
            for (auto* listener : pair->m_vecPre)
            {
                auto action = listener->OnEntityOutput(
                    outputName,
                    pActivator,
                    pCaller,
                    delay,
                    MMODE_PRE
                );

                if (action == MRES_SUPERCEDE)
                    RETURN_META(MRES_SUPERCEDE);

                if (action > finalAction)
                    finalAction = action;
            }
        }

        if (finalAction != MRES_SUPERCEDE)
        {
            SH_CALL(FireOutputInternal, addresses::toolkitAddresses.FireOutputInternal, pThis)(pActivator, pCaller, variantValue, delay, unk01, unk02);
        }

        for (auto* pair : matched)
        {
            for (auto* listener : pair->m_vecPost)
            {
                listener->OnEntityOutput(outputName, pActivator, pCaller, delay, MMODE_POST);
            }
        }

        // The original already ran above, so supersede rather than let
        // SourceHook call it a second time.
        RETURN_META(MRES_SUPERCEDE);
    }
}
