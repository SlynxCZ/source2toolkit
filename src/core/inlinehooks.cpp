//
// Created by Michal Přikryl on 03.04.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
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
