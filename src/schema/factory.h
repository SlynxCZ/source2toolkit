//
// Created by Michal Přikryl on 11.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#ifndef FACTORY_H
#define FACTORY_H

#include "core/addresses.h"

template <typename T>
class EntityFactory
{
public:
    static T* New(const char* pszClassName)
    {
        return reinterpret_cast<T*>(addresses::CBaseEntity_CreateEntityByName(pszClassName, -1));
    }
};

#endif //FACTORY_H
