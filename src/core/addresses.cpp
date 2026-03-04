//
// Created by Michal Přikryl on 04.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "addresses.h"

#include "Shared.h"

bool addresses::Initialize()
{
    RESOLVE_SIG(shared::g_pServer, "CBaseEntity::DispatchSpawn", shared::g_pGameConfig->GetSignature("CBaseEntity_DispatchSpawn"), addresses::CBaseEntity_DispatchSpawn);
    RESOLVE_SIG(shared::g_pServer, "CBaseModelEntity::SetModel", shared::g_pGameConfig->GetSignature("CBaseModelEntity_SetModel"), addresses::CBaseModelEntity_SetModel);
    RESOLVE_SIG(shared::g_pServer, "CBasePlayerController::SetPawn", shared::g_pGameConfig->GetSignature("CBasePlayerController_SetPawn"), addresses::CBasePlayerController_SetPawn);
    RESOLVE_SIG(shared::g_pServer, "CBasePlayerPawn::RemovePlayerItem", shared::g_pGameConfig->GetSignature("CBasePlayerPawn_RemovePlayerItem"), addresses::CBasePlayerPawn_RemovePlayerItem);

    return true;
}
