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
        CBaseEntity_CreateEntityByName_t CBaseEntity_CreateEntityByName() override;
        CBaseEntity_DispatchSpawn_t CBaseEntity_DispatchSpawn() override;
        CBaseEntity_TakeDamageOld_t CBaseEntity_TakeDamageOld() override;
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
        CTakeDamageInfo_CTakeDamageInfo_t CTakeDamageInfo_CTakeDamageInfo() override;
    public:
        CBaseEntity_CreateEntityByName_t CreateEntityByName = nullptr;
        CBaseEntity_DispatchSpawn_t DispatchSpawn = nullptr;
        CBaseEntity_TakeDamageOld_t TakeDamageOld = nullptr;
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
        CTakeDamageInfo_CTakeDamageInfo_t CTakeDamageInfo = nullptr;
    private:
        std::unordered_map<uintptr_t, DynLibUtils::CModule> m_Modules;
    };

    extern Addresses toolkitAddresses;
}
