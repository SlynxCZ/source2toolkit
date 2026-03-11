//
// Created by Michal Přikryl on 11.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "CCSGameRules.h"

#include "CCSPlayerController.h"
#include "CCSPlayerPawn.h"
#include "schema/entity.h"

#include "core/addresses.h"
#include "core/shared.h"

void CCSGameRules::TerminateRound(float flDelay, int32_t eRoundEndReason)
{
    addresses::CGameRules_TerminateRound(this, flDelay, eRoundEndReason, 0, 0);
}

CBaseEntity* CCSGameRules::FindPickerEntity(CBasePlayerController* pPlayer)
{
    return UTIL_FindPickerEntity(pPlayer, this);
}

CCSPlayerController* CCSGameRules::GetClientAimTarget(CCSPlayerController* pPlayer)
{
    auto* pPawn = static_cast<CCSPlayerPawn*>(UTIL_FindPickerEntity(pPlayer, this));
    if (!pPawn) return nullptr;

    return pPawn->GetClassname() == "player" ? pPawn->m_hOriginalController().Get() : nullptr;
}