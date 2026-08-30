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
        RESOLVE_SIG(g_pSource2Server, "CBaseEntity::CreateEntityByName", shared::g_pGameConfig->GetSignature("CBaseEntity_CreateEntityByName"), toolkitAddresses.CreateEntityByName);
        RESOLVE_SIG(g_pSource2Server, "CBaseEntity::DispatchSpawn", shared::g_pGameConfig->GetSignature("CBaseEntity_DispatchSpawn"), toolkitAddresses.DispatchSpawn);
        RESOLVE_SIG(g_pSource2Server, "CBaseEntity::TakeDamageOld", shared::g_pGameConfig->GetSignature("CBaseEntity_TakeDamageOld"), toolkitAddresses.TakeDamageOld);
        RESOLVE_SIG(g_pSource2Server, "CBaseModelEntity::SetModel", shared::g_pGameConfig->GetSignature("CBaseModelEntity_SetModel"), toolkitAddresses.SetModel);
        RESOLVE_SIG(g_pSource2Server, "CBasePlayerController::SetPawn", shared::g_pGameConfig->GetSignature("CBasePlayerController_SetPawn"), toolkitAddresses.SetPawn);
        // Windows has no published signature for this one; RESOLVE_SIG_OPTIONAL
        // leaves it null there rather than failing the whole address table.
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CBasePlayerPawn::SnapViewAngles", shared::g_pGameConfig->GetSignature("CBasePlayerPawn_SnapViewAngles"), toolkitAddresses.SnapViewAngles);
        RESOLVE_SIG(g_pSource2Server, "CGameRules::TerminateRound", shared::g_pGameConfig->GetSignature("CGameRules_TerminateRound"), toolkitAddresses.TerminateRound);
        RESOLVE_SIG(g_pSource2Server, "CCSPlayer_WeaponServices::Destroy", shared::g_pGameConfig->GetSignature("CCSPlayer_WeaponServices_Destroy"), toolkitAddresses.Destroy);
        RESOLVE_SIG(g_pSource2Server, "LegacyGameEventListener", shared::g_pGameConfig->GetSignature("LegacyGameEventListener"), toolkitAddresses.LegacyGameEventListener);
        RESOLVE_SIG(g_pSource2Server, "CCSPlayerController::SwitchTeam", shared::g_pGameConfig->GetSignature("CCSPlayerController_SwitchTeam"), toolkitAddresses.SwitchTeam);
        RESOLVE_SIG(g_pSource2Server, "CEntityInstance::AcceptInput", shared::g_pGameConfig->GetSignature("CEntityInstance_AcceptInput"), toolkitAddresses.AcceptInput);
        RESOLVE_SIG(g_pSource2Server, "CEntityIOOutput::FireOutputInternal", shared::g_pGameConfig->GetSignature("CEntityIOOutput_FireOutputInternal"), toolkitAddresses.FireOutputInternal);
        RESOLVE_SIG(g_pSource2Server, "CEntitySystem::AddEntityIOEvent", shared::g_pGameConfig->GetSignature("CEntitySystem_AddEntityIOEvent"), toolkitAddresses.AddEntityIOEvent);
        RESOLVE_SIG(g_pSource2Server, "CGameEntitySystem::FindEntityByClassName", shared::g_pGameConfig->GetSignature("CGameEntitySystem_FindEntityByClassName"), toolkitAddresses.FindEntityByClassName);
        RESOLVE_SIG(g_pSource2Server, "CGameEntitySystem::FindEntityByName", shared::g_pGameConfig->GetSignature("CGameEntitySystem_FindEntityByName"), toolkitAddresses.FindEntityByName);
        RESOLVE_SIG(g_pSource2Server, "CTakeDamageInfo::CTakeDamageInfo", shared::g_pGameConfig->GetSignature("CTakeDamageInfo_CTakeDamageInfo"), toolkitAddresses.CTakeDamageInfo);
        RESOLVE_SIG(shared::g_pGameEventSystem, "INetworkMessageProcessingPreFilter::FilterMessage", shared::g_pGameConfig->GetSignature("INetworkMessageProcessingPreFilter_FilterMessage"), toolkitAddresses.FilterMessage);

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

    CBaseEntity_CreateEntityByName_t Addresses::CBaseEntity_CreateEntityByName()
    {
        return CreateEntityByName.RCast<CBaseEntity_CreateEntityByName_t>();
    }

    CBaseEntity_DispatchSpawn_t Addresses::CBaseEntity_DispatchSpawn()
    {
        return DispatchSpawn.RCast<CBaseEntity_DispatchSpawn_t>();
    }

    CBaseEntity_TakeDamageOld_t Addresses::CBaseEntity_TakeDamageOld()
    {
        return TakeDamageOld.RCast<CBaseEntity_TakeDamageOld_t>();
    }

    CBaseModelEntity_SetModel_t Addresses::CBaseModelEntity_SetModel()
    {
        return SetModel.RCast<CBaseModelEntity_SetModel_t>();
    }

    CBasePlayerController_SetPawn_t Addresses::CBasePlayerController_SetPawn()
    {
        return SetPawn.RCast<CBasePlayerController_SetPawn_t>();
    }

    CBasePlayerPawn_SnapViewAngles_t Addresses::CBasePlayerPawn_SnapViewAngles()
    {
        return SnapViewAngles.RCast<CBasePlayerPawn_SnapViewAngles_t>();
    }

    CGameRules_TerminateRound_t Addresses::CGameRules_TerminateRound()
    {
        return TerminateRound.RCast<CGameRules_TerminateRound_t>();
    }

    CCSPlayer_WeaponServices_Destroy_t Addresses::CCSPlayer_WeaponServices_Destroy()
    {
        return Destroy.RCast<CCSPlayer_WeaponServices_Destroy_t>();
    }

    LegacyGameEventListener_t Addresses::LegacyGameEventListener()
    {
        return LegacyGameEventListener.RCast<LegacyGameEventListener_t>();
    }

    CCSPlayerController_SwitchTeam_t Addresses::CCSPlayerController_SwitchTeam()
    {
        return SwitchTeam.RCast<CCSPlayerController_SwitchTeam_t>();
    }

    CEntityInstance_AcceptInput_t Addresses::CEntityInstance_AcceptInput()
    {
        return AcceptInput.RCast<CEntityInstance_AcceptInput_t>();
    }

    CEntityIOOutput_FireOutputInternal_t Addresses::CEntityIOOutput_FireOutputInternal()
    {
        return FireOutputInternal.RCast<CEntityIOOutput_FireOutputInternal_t>();
    }

    CEntitySystem_AddEntityIOEvent_t Addresses::CEntitySystem_AddEntityIOEvent()
    {
        return AddEntityIOEvent.RCast<CEntitySystem_AddEntityIOEvent_t>();
    }

    CGameEntitySystem_FindEntityByClassName_t Addresses::CGameEntitySystem_FindEntityByClassName()
    {
        return FindEntityByClassName.RCast<CGameEntitySystem_FindEntityByClassName_t>();
    }

    CGameEntitySystem_FindEntityByName_t Addresses::CGameEntitySystem_FindEntityByName()
    {
        return FindEntityByName.RCast<CGameEntitySystem_FindEntityByName_t>();
    }

    CTakeDamageInfo_CTakeDamageInfo_t Addresses::CTakeDamageInfo_CTakeDamageInfo()
    {
        return CTakeDamageInfo.RCast<CTakeDamageInfo_CTakeDamageInfo_t>();
    }

    INetworkMessageProcessingPreFilter_FilterMessage_t Addresses::INetworkMessageProcessingPreFilter_FilterMessage()
    {
        return FilterMessage.RCast<INetworkMessageProcessingPreFilter_FilterMessage_t>();
    }
}
