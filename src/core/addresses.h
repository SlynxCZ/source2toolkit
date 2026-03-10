//
// Created by Michal Přikryl on 04.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once

#include "utils/log.h"

#include "platform.h"
#include "dynlibutils/module.h"
#include "dynlibutils/memaddr.h"

#define RESOLVE_SIG(handle, name, pattern, variable)                  \
{                                                                     \
    auto addr = DynLibUtils::CModule(handle).FindPattern(pattern);    \
                                                                      \
    if (!addr)                                                        \
    {                                                                 \
        FP_DEBUG("Failed to find '{}'", name);                        \
        return false;                                                 \
    }                                                                 \
                                                                      \
    variable = addr.RCast<decltype(variable)>();                      \
                                                                      \
    FP_DEBUG("Found '{}' at {}", name, fmt::ptr(variable));           \
}

class CEntityKeyValues;
class CBaseEntity;
class CBasePlayerWeapon;
class CBaseModelEntity;
class CBasePlayerPawn;
class CBasePlayerController;

namespace addresses
{
    bool Initialize();

    inline void(FASTCALL* CBaseEntity_DispatchSpawn)(CBaseEntity* pEntity, CEntityKeyValues* pEntityKeyValues);
    inline void(FASTCALL* CBaseModelEntity_SetModel)(CBaseModelEntity* pModel, const char* szModel);
    inline void(FASTCALL* CBasePlayerController_SetPawn)(CBasePlayerController* pController, CBasePlayerPawn* pPawn, bool a3, bool a4, bool a5, bool a6);
    inline void(FASTCALL* CBasePlayerPawn_RemovePlayerItem)(CBasePlayerPawn* pPawn, CBasePlayerWeapon* pWeapon);
}
