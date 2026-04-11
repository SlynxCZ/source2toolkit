//
// Created by Michal Přikryl on 04.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "addresses.h"

#include "shared.h"

namespace addresses
{
    Addresses toolkitAddresses;

    bool Initialize()
    {
        RESOLVE_SIG(shared::g_pServer, "CBaseEntity::CreateEntityByName", shared::g_pGameConfig->GetSignature("CBaseEntity_CreateEntityByName"), toolkitAddresses.CreateEntityByName);
        RESOLVE_SIG(shared::g_pServer, "CBaseEntity::DispatchSpawn", shared::g_pGameConfig->GetSignature("CBaseEntity_DispatchSpawn"), toolkitAddresses.DispatchSpawn);
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
        RESOLVE_SIG(shared::g_pServer, "CGameEventManager::Init", shared::g_pGameConfig->GetSignature("CGameEventManager_Init"), toolkitAddresses.GameEventManagerInit);

        return true;
    }

    CBaseEntity_CreateEntityByName_t Addresses::CBaseEntity_CreateEntityByName()
    {
        return CreateEntityByName;
    }

    CBaseEntity_DispatchSpawn_t Addresses::CBaseEntity_DispatchSpawn()
    {
        return DispatchSpawn;
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

    CGameEventManager_Init_t Addresses::CGameEventManager_Init()
    {
        return GameEventManagerInit;
    }
}