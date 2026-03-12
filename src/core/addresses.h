//
// Created by Michal Přikryl on 04.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "utils/log.h"

#include "platform.h"
#include "dynlibutils/module.h"
#include "dynlibutils/memaddr.h"

#include "playerslot.h"
#include "variant.h"

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

class IGameEventListener2;
class IEntityFindFilter;
class CEntityInstance;
class CEntitySystem;
class CEntityKeyValues;
class CBaseEntity;
class CBasePlayerWeapon;
class CBaseModelEntity;
class CBasePlayerPawn;
class CBasePlayerController;
class CGameRules;
class CCSPlayerController;

namespace addresses
{
    bool Initialize();

    inline CBaseEntity*(FASTCALL* CBaseEntity_CreateEntityByName)(const char* className, int iForceEdictIndex);
    inline void(FASTCALL* CBaseEntity_DispatchSpawn)(CBaseEntity* pEntity, CEntityKeyValues* pEntityKeyValues);
    inline void(FASTCALL* CBaseModelEntity_SetModel)(CBaseModelEntity* pModel, const char* szModel);
    inline void(FASTCALL* CBasePlayerController_SetPawn)(CBasePlayerController* pController, CBasePlayerPawn* pPawn, bool a3, bool a4, bool a5, bool a6);
    inline void(FASTCALL* CBasePlayerPawn_RemovePlayerItem)(CBasePlayerPawn* pPawn, CBasePlayerWeapon* pWeapon);
    inline void(FASTCALL* CGameRules_TerminateRound)(CGameRules* pGameRules, float delay, unsigned int reason, int64 a4, unsigned int a5);
    inline IGameEventListener2*(FASTCALL* CCSPlayerController_LegacyGameEventListener)(CPlayerSlot playerSlot);
    inline void(FASTCALL* CCSPlayerController_SwitchTeam)(CCSPlayerController* pController, unsigned char nTeam);
    inline void(FASTCALL* CEntityInstance_AcceptInput)(CEntityInstance* pThis, const char* pInputName, CEntityInstance* pActivator, CEntityInstance* pCaller, const variant_t& pValue, int nOutputID, void*);
    inline void(FASTCALL* CEntitySystem_AddEntityIOEvent)(CEntitySystem* pEntitySystem, CEntityInstance* pTarget, const char* pszInput, CEntityInstance* pActivator, CEntityInstance* pCaller, const variant_t& pValue, float flDelay, int outputID, void*, void*);
    inline CBaseEntity*(FASTCALL* CGameEntitySystem_FindEntityByClassName)(CEntitySystem* pEntitySystem, CEntityInstance* pStartEntity, const char* szName);
    inline CBaseEntity*(FASTCALL* CGameEntitySystem_FindEntityByName)(CEntitySystem* pEntitySystem, CEntityInstance* pStartEntity, const char* szName, CEntityInstance* pSearchingEntity, CEntityInstance* pActivator, CEntityInstance* pCaller, IEntityFindFilter* pFilter);
}
