//
// Created by Michal Přikryl on 04.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "source2toolkit/IToolkitAddresses.h"

#include "utils/log.h"

#include "platform.h"
#include "dynlibutils/module.h"
#include "dynlibutils/memaddr.h"

#include "playerslot.h"
#include "variant.h"

#define RESOLVE_SIG(handle, name, pattern, variable)                  \
{                                                                     \
    auto& mod = toolkitAddresses.GetOrLoadModule(handle);             \
    auto addr = mod.FindPattern(pattern);                             \
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

class CEntityInstance;
class CEntityIOOutput;
class CEntitySystem;
class CEntityKeyValues;
class CBaseEntity;
class CBasePlayerWeapon;
class CBaseModelEntity;
class CBasePlayerPawn;
class CBasePlayerController;
class CGameRules;
class CCSPlayerController;
class IGameEventListener2;
class IGameEventManager2;
class IEntityFindFilter;

namespace addresses
{
    bool Initialize();

    class Addresses : public IToolkitAddresses {
    public:
        DynLibUtils::CModule& GetOrLoadModule(void* ptr);
    public:
        void* GetModuleHandle(void* modulePtr) override;
        uintptr_t GetModuleBase(void* modulePtr) override;
        const char* GetModulePath(void* modulePtr) override;

        uintptr_t FindPattern(void* modulePtr, const char* pattern) override;
        uintptr_t FindPatternInSection(void* modulePtr, const char* section, const char* pattern) override;

        uintptr_t GetFunctionByName(void* modulePtr, const char* symbol) override;
        uintptr_t GetVirtualTableByName(void* modulePtr, const char* name) override;

        uintptr_t Offset(uintptr_t address, ptrdiff_t offset) override;
        uintptr_t OffsetSelf(uintptr_t& address, ptrdiff_t offset) override;

        uintptr_t Deref(uintptr_t address, int count = 1) override;
        uintptr_t DerefSelf(uintptr_t& address, int count = 1) override;

        uintptr_t ResolveRelativeAddress(uintptr_t address, ptrdiff_t offset = 0x0, ptrdiff_t size = 0x4) override;
        uintptr_t FollowNearCall(uintptr_t address, ptrdiff_t offset = 0x1, ptrdiff_t size = 0x5) override;

        CBaseEntity_CreateEntityByName_t CBaseEntity_CreateEntityByName() override;
        CBaseEntity_DispatchSpawn_t CBaseEntity_DispatchSpawn() override;
        CBaseModelEntity_SetModel_t CBaseModelEntity_SetModel() override;
        CBasePlayerController_SetPawn_t CBasePlayerController_SetPawn() override;
        CBasePlayerPawn_RemovePlayerItem_t CBasePlayerPawn_RemovePlayerItem() override;
        CGameRules_TerminateRound_t CGameRules_TerminateRound() override;
        CCSPlayerController_LegacyGameEventListener_t CCSPlayerController_LegacyGameEventListener() override;
        CCSPlayerController_SwitchTeam_t CCSPlayerController_SwitchTeam() override;
        CEntityInstance_AcceptInput_t CEntityInstance_AcceptInput() override;
        CEntityIOOutput_FireOutputInternal_t CEntityIOOutput_FireOutputInternal() override;
        CEntitySystem_AddEntityIOEvent_t CEntitySystem_AddEntityIOEvent() override;
        CGameEntitySystem_FindEntityByClassName_t CGameEntitySystem_FindEntityByClassName() override;
        CGameEntitySystem_FindEntityByName_t CGameEntitySystem_FindEntityByName() override;
    public:
        CBaseEntity_CreateEntityByName_t CreateEntityByName = nullptr;
        CBaseEntity_DispatchSpawn_t DispatchSpawn = nullptr;
        CBaseModelEntity_SetModel_t SetModel = nullptr;
        CBasePlayerController_SetPawn_t SetPawn = nullptr;
        CBasePlayerPawn_RemovePlayerItem_t RemovePlayerItem = nullptr;
        CGameRules_TerminateRound_t TerminateRound = nullptr;
        CCSPlayerController_LegacyGameEventListener_t LegacyGameEventListener = nullptr;
        CCSPlayerController_SwitchTeam_t SwitchTeam = nullptr;
        CEntityInstance_AcceptInput_t AcceptInput = nullptr;
        CEntityIOOutput_FireOutputInternal_t FireOutputInternal = nullptr;
        CEntitySystem_AddEntityIOEvent_t AddEntityIOEvent = nullptr;
        CGameEntitySystem_FindEntityByClassName_t FindEntityByClassName = nullptr;
        CGameEntitySystem_FindEntityByName_t FindEntityByName = nullptr;
    private:
        std::unordered_map<uintptr_t, DynLibUtils::CModule> m_Modules;
    };

    extern Addresses toolkitAddresses;
}
