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
#include "addresses.h"

#include "shared.h"

namespace addresses
{
    Addresses toolkitAddresses;

    bool Initialize()
    {
        RESOLVE_SIG(shared::g_pServer, "CBaseEntity::CreateEntityByName", shared::g_pGameConfig->GetSignature("CBaseEntity_CreateEntityByName"), toolkitAddresses.CreateEntityByName);
        RESOLVE_SIG(shared::g_pServer, "CBaseEntity::DispatchSpawn", shared::g_pGameConfig->GetSignature("CBaseEntity_DispatchSpawn"), toolkitAddresses.DispatchSpawn);
        RESOLVE_SIG(shared::g_pServer, "CBaseEntity::TakeDamageOld", shared::g_pGameConfig->GetSignature("CBaseEntity_TakeDamageOld"), toolkitAddresses.TakeDamageOld);
        RESOLVE_SIG(shared::g_pServer, "CBaseModelEntity::SetModel", shared::g_pGameConfig->GetSignature("CBaseModelEntity_SetModel"), toolkitAddresses.SetModel);
        RESOLVE_SIG(shared::g_pServer, "CBasePlayerController::SetPawn", shared::g_pGameConfig->GetSignature("CBasePlayerController_SetPawn"), toolkitAddresses.SetPawn);
        RESOLVE_SIG(shared::g_pServer, "CBasePlayerPawn::RemovePlayerItem", shared::g_pGameConfig->GetSignature("CBasePlayerPawn_RemovePlayerItem"), toolkitAddresses.RemovePlayerItem);
        RESOLVE_SIG(shared::g_pServer, "CGameRules::TerminateRound", shared::g_pGameConfig->GetSignature("CGameRules_TerminateRound"), toolkitAddresses.TerminateRound);
        RESOLVE_SIG(shared::g_pServer, "CCSPlayerController::LegacyGameEventListener", shared::g_pGameConfig->GetSignature("CCSPlayerController_LegacyGameEventListener"), toolkitAddresses.LegacyGameEventListener);
        RESOLVE_SIG(shared::g_pServer, "CCSPlayerController::SwitchTeam", shared::g_pGameConfig->GetSignature("CCSPlayerController_SwitchTeam"), toolkitAddresses.SwitchTeam);
        RESOLVE_SIG(shared::g_pServer, "CEntityInstance::AcceptInput", shared::g_pGameConfig->GetSignature("CEntityInstance_AcceptInput"), toolkitAddresses.AcceptInput);
        RESOLVE_SIG(shared::g_pServer, "CEntityIOOutput::FireOutputInternal", shared::g_pGameConfig->GetSignature("CEntityIOOutput_FireOutputInternal"), toolkitAddresses.FireOutputInternal);
        RESOLVE_SIG(shared::g_pServer, "CEntitySystem::AddEntityIOEvent", shared::g_pGameConfig->GetSignature("CEntitySystem_AddEntityIOEvent"), toolkitAddresses.AddEntityIOEvent);
        RESOLVE_SIG(shared::g_pServer, "CGameEntitySystem::FindEntityByClassName", shared::g_pGameConfig->GetSignature("CGameEntitySystem_FindEntityByClassName"), toolkitAddresses.FindEntityByClassName);
        RESOLVE_SIG(shared::g_pServer, "CGameEntitySystem::FindEntityByName", shared::g_pGameConfig->GetSignature("CGameEntitySystem_FindEntityByName"), toolkitAddresses.FindEntityByName);
        RESOLVE_SIG(shared::g_pServer, "CTakeDamageInfo::CTakeDamageInfo", shared::g_pGameConfig->GetSignature("CTakeDamageInfo_CTakeDamageInfo"), toolkitAddresses.CTakeDamageInfo);

        return true;
    }

    DynLibUtils::CModule& Addresses::GetOrLoadModule(void* ptr)
    {
        uintptr_t key = reinterpret_cast<uintptr_t>(ptr);

        auto it = m_Modules.find(key);
        if (it != m_Modules.end())
            return it->second;

        auto [iter, _] = m_Modules.emplace(key, DynLibUtils::CModule(DynLibUtils::CMemory(ptr)));
        return iter->second;
    }

    DynLibUtils::CModule& Addresses::GetOrLoadModule(const char* name)
    {
        std::string key(name);

        auto it = m_ModulesByName.find(key);
        if (it != m_ModulesByName.end())
            return it->second;

        auto [iter, _] =
            m_ModulesByName.emplace(key, DynLibUtils::CModule(key));

        return iter->second;
    }

    void* Addresses::GetModulePtr(const char* moduleName)
    {
        return &GetOrLoadModule(moduleName);
    }

    void* Addresses::GetModulePtr(void* classPtr)
    {
        return &GetOrLoadModule(classPtr);
    }

    void* Addresses::GetModuleHandle(void* modulePtr)
    {
        auto& mod = GetOrLoadModule(modulePtr);
        return mod.GetModuleHandle();
    }

    uintptr_t Addresses::GetModuleBase(void* modulePtr)
    {
        auto& mod = GetOrLoadModule(modulePtr);
        return mod.GetModuleBase().GetPtr();
    }

    const char* Addresses::GetModulePath(void* modulePtr)
    {
        auto& mod = GetOrLoadModule(modulePtr);
        return mod.GetModulePath().data();
    }

    uintptr_t Addresses::FindPattern(void* modulePtr, const char* pattern)
    {
        auto& mod = GetOrLoadModule(modulePtr);
        return mod.FindPattern(pattern).GetPtr();
    }

    uintptr_t Addresses::FindPatternInSection(void* modulePtr, const char* section, const char* pattern)
    {
        auto& mod = GetOrLoadModule(modulePtr);
        auto sec = mod.GetSectionByName(section);

        if (!sec.IsSectionValid())
            return 0;

        return mod.FindPattern(pattern, nullptr, &sec).GetPtr();
    }

    uintptr_t Addresses::GetFunctionByName(void* modulePtr, const char* symbol)
    {
        auto& mod = GetOrLoadModule(modulePtr);
        return mod.GetFunctionByName(symbol).GetPtr();
    }

    uintptr_t Addresses::GetVirtualTableByName(void* modulePtr, const char* name)
    {
        auto& mod = GetOrLoadModule(modulePtr);
        return mod.GetVirtualTableByName(name).GetPtr();
    }

    uintptr_t Addresses::Offset(uintptr_t address, ptrdiff_t offset)
    {
        return DynLibUtils::CMemory(address).Offset(offset).GetPtr();
    }

    uintptr_t Addresses::OffsetSelf(uintptr_t& address, ptrdiff_t offset)
    {
        DynLibUtils::CMemory mem(address);
        mem.OffsetSelf(offset);
        address = mem.GetPtr();
        return address;
    }

    uintptr_t Addresses::Deref(uintptr_t address, int count)
    {
        return DynLibUtils::CMemory(address).Deref(count).GetPtr();
    }

    uintptr_t Addresses::DerefSelf(uintptr_t& address, int count)
    {
        DynLibUtils::CMemory mem(address);
        mem.DerefSelf(count);
        address = mem.GetPtr();
        return address;
    }

    uintptr_t Addresses::ResolveRelativeAddress(uintptr_t address, ptrdiff_t offset, ptrdiff_t size)
    {
        return DynLibUtils::CMemory(address).ResolveRelativeAddress(offset, size).GetPtr();
    }

    uintptr_t Addresses::FollowNearCall(uintptr_t address, ptrdiff_t offset, ptrdiff_t size)
    {
        return DynLibUtils::CMemory(address).FollowNearCall(offset, size).GetPtr();
    }

    CBaseEntity_CreateEntityByName_t Addresses::CBaseEntity_CreateEntityByName()
    {
        return CreateEntityByName;
    }

    CBaseEntity_DispatchSpawn_t Addresses::CBaseEntity_DispatchSpawn()
    {
        return DispatchSpawn;
    }

    CBaseEntity_TakeDamageOld_t Addresses::CBaseEntity_TakeDamageOld()
    {
        return TakeDamageOld;
    }

    CBaseModelEntity_SetModel_t Addresses::CBaseModelEntity_SetModel()
    {
        return SetModel;
    }

    CBasePlayerController_SetPawn_t Addresses::CBasePlayerController_SetPawn()
    {
        return SetPawn;
    }

    CBasePlayerPawn_RemovePlayerItem_t Addresses::CBasePlayerPawn_RemovePlayerItem()
    {
        return RemovePlayerItem;
    }

    CGameRules_TerminateRound_t Addresses::CGameRules_TerminateRound()
    {
        return TerminateRound;
    }

    CCSPlayerController_LegacyGameEventListener_t Addresses::CCSPlayerController_LegacyGameEventListener()
    {
        return LegacyGameEventListener;
    }

    CCSPlayerController_SwitchTeam_t Addresses::CCSPlayerController_SwitchTeam()
    {
        return SwitchTeam;
    }

    CEntityInstance_AcceptInput_t Addresses::CEntityInstance_AcceptInput()
    {
        return AcceptInput;
    }

    CEntityIOOutput_FireOutputInternal_t Addresses::CEntityIOOutput_FireOutputInternal()
    {
        return FireOutputInternal;
    }

    CEntitySystem_AddEntityIOEvent_t Addresses::CEntitySystem_AddEntityIOEvent()
    {
        return AddEntityIOEvent;
    }

    CGameEntitySystem_FindEntityByClassName_t Addresses::CGameEntitySystem_FindEntityByClassName()
    {
        return FindEntityByClassName;
    }

    CGameEntitySystem_FindEntityByName_t Addresses::CGameEntitySystem_FindEntityByName()
    {
        return FindEntityByName;
    }

    CTakeDamageInfo_CTakeDamageInfo_t Addresses::CTakeDamageInfo_CTakeDamageInfo()
    {
        return CTakeDamageInfo;
    }
}
