//
// Created by Michal Přikryl on 03.04.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "inlinehooks.h"

#include "addresses.h"
#include "commands.h"
#include "events.h"
#include "shared.h"
#include "utils/plat.h"
#include "utils/scheduler.h"
#include "dynlibutils/module.h"
#include "iserver.h"
#include "schema/cgameresourceserviceserver.h"
#include "schema/entity/classes/CCSGameRulesProxy.h"

namespace inlinehooks
{
    Inlines inlines;
    std::unordered_map<OutputKey, EntityIOCallbackPair, OutputKeyHash> entityIOListenerStack;

    Inlines::Inlines() :
        m_FireOutputInternal(this, &Inlines::Hook_FireOutputInternal, nullptr)
    {
    }

    void Inlines::InitListeners()
    {
        m_FireOutputInternal.Configure(addresses::CEntityIOOutput_FireOutputInternal);
    }

    void Inlines::DestructListeners()
    {
        m_FireOutputInternal.~Function();
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
                    false
                );

                if (action == KHook::Action::Supersede)
                    return {KHook::Action::Supersede};

                if (action > finalAction)
                    finalAction = action;
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
                    true
                );
            }
        }

        return {KHook::Action::Supersede};
    }
}
