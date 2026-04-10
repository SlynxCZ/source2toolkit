//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "source2toolkit/schema/entityio.h"

#include "ISmmPlugin.h"
#include "eiface.h"
#include "entitysystem.h"

#include "dynlibutils/memaddr.h"

namespace inlinehooks {
    class Inlines {
    public:
        Inlines();

        void InitListeners();
        void DestructListeners();
    public:
        KHook::Return<void> Hook_FireOutputInternal(CEntityIOOutput* pThis, CEntityInstance* pActivator, CEntityInstance* pCaller, void* variantValue, float delay, void* unk01, void* unk02);
    protected:
        KHook::Function<void, CEntityIOOutput*, CEntityInstance*, CEntityInstance*, void*, float, void*, void*> m_FireOutputInternal;
    };

    extern Inlines inlines;
    extern std::unordered_map<OutputKey, EntityIOCallbackPair, OutputKeyHash> entityIOListenerStack;
}
