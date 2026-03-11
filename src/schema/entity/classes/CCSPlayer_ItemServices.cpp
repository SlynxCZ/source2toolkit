//
// Created by Michal Přikryl on 11.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "CCSPlayer_ItemServices.h"

#include "core/shared.h"

void CCSPlayer_ItemServices::DropActivePlayerWeapon(CBasePlayerWeapon* pActiveWeapon)
{
    CALL_VIRTUAL(void, shared::g_pGameConfig->GetOffset("CCSPlayer_ItemServices_DropActivePlayerWeapon"), this, pActiveWeapon);
}

void CCSPlayer_ItemServices::RemoveWeapons()
{
    CALL_VIRTUAL(void, shared::g_pGameConfig->GetOffset("CCSPlayer_ItemServices_RemoveWeapons"), this);
}

CBasePlayerWeapon* CCSPlayer_ItemServices::GiveNamedItem(const char* pszItem)
{
    return CALL_VIRTUAL(CBasePlayerWeapon*, shared::g_pGameConfig->GetOffset("CCSPlayer_ItemServices_GiveNamedItem"), this, pszItem);
}