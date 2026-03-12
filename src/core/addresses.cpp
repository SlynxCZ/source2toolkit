//
// Created by Michal Přikryl on 04.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "addresses.h"

#include "Shared.h"

bool addresses::Initialize()
{
    RESOLVE_SIG(shared::g_pServer, "CBaseEntity::CreateEntityByName", shared::g_pGameConfig->GetSignature("CBaseEntity_CreateEntityByName"), addresses::CBaseEntity_CreateEntityByName);
    RESOLVE_SIG(shared::g_pServer, "CBaseEntity::DispatchSpawn", shared::g_pGameConfig->GetSignature("CBaseEntity_DispatchSpawn"), addresses::CBaseEntity_DispatchSpawn);
    RESOLVE_SIG(shared::g_pServer, "CBaseModelEntity::SetModel", shared::g_pGameConfig->GetSignature("CBaseModelEntity_SetModel"), addresses::CBaseModelEntity_SetModel);
    RESOLVE_SIG(shared::g_pServer, "CBasePlayerController::SetPawn", shared::g_pGameConfig->GetSignature("CBasePlayerController_SetPawn"), addresses::CBasePlayerController_SetPawn);
    RESOLVE_SIG(shared::g_pServer, "CBasePlayerPawn::RemovePlayerItem", shared::g_pGameConfig->GetSignature("CBasePlayerPawn_RemovePlayerItem"), addresses::CBasePlayerPawn_RemovePlayerItem);
    RESOLVE_SIG(shared::g_pServer, "CGameRules::TerminateRound", shared::g_pGameConfig->GetSignature("CGameRules_TerminateRound"), addresses::CGameRules_TerminateRound);
    RESOLVE_SIG(shared::g_pServer, "CCSPlayerController::LegacyGameEventListener", shared::g_pGameConfig->GetSignature("CCSPlayerController_LegacyGameEventListener"), addresses::CCSPlayerController_LegacyGameEventListener);
    RESOLVE_SIG(shared::g_pServer, "CCSPlayerController::SwitchTeam", shared::g_pGameConfig->GetSignature("CCSPlayerController_SwitchTeam"), addresses::CCSPlayerController_SwitchTeam);
    RESOLVE_SIG(shared::g_pServer, "CEntityInstance::AcceptInput", shared::g_pGameConfig->GetSignature("CEntityInstance_AcceptInput"), addresses::CEntityInstance_AcceptInput);
    RESOLVE_SIG(shared::g_pServer, "CEntitySystem::AddEntityIOEvent", shared::g_pGameConfig->GetSignature("CEntitySystem_AddEntityIOEvent"), addresses::CEntitySystem_AddEntityIOEvent);
    RESOLVE_SIG(shared::g_pServer, "CGameEntitySystem::FindEntityByClassName", shared::g_pGameConfig->GetSignature("CGameEntitySystem_FindEntityByClassName"), addresses::CGameEntitySystem_FindEntityByClassName);
    RESOLVE_SIG(shared::g_pServer, "CGameEntitySystem::FindEntityByName", shared::g_pGameConfig->GetSignature("CGameEntitySystem_FindEntityByName"), addresses::CGameEntitySystem_FindEntityByName);

    return true;
}
