//
// Created by Michal Přikryl on 04.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "CBasePlayerPawn.h"

#include "core/addresses.h"
#include "core/shared.h"

void CBasePlayerPawn::CommitSuicide(bool bExplode, bool bForce) {
    CALL_VIRTUAL(void, shared::g_pGameConfig->GetOffset("CBasePlayerPawn_CommitSuicide"), this, bExplode, bForce);
}

void CBasePlayerPawn::RemovePlayerItem(CBasePlayerWeapon* pWeapon) {
    if (!pWeapon) return;

    addresses::CBasePlayerPawn_RemovePlayerItem(this, pWeapon);
}