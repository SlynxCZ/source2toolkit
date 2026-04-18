//========= Copyright (c), Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#include "CSource1LegacyGameEventGameSystem.h"

#include "main.h"

#include "source2toolkit/IToolkitApi.h"
#include "source2toolkit/utils/addresses.h"
#include "source2toolkit/utils/gameconfig.h"

CUtlString* CSource1LegacyGameEventGameSystem::GetName()
{
    return (CUtlString*)(UTIL_Offset((uintptr_t)this, UTIL_GetOffset("CSource1LegacyGameEventGameSystem_Name")));
}

IGameEventListener2* CSource1LegacyGameEventGameSystem::GetLegacyGameEventListener(int slot)
{
    if (slot < 0 || slot > 63)
    {
        TOOLKIT_LOG(&g_Plugin, "Invalid player slot");
        return nullptr;
    }

    return g_ToolkitAPI->Addresses()->CCSPlayerController_LegacyGameEventListener()(CPlayerSlot(slot));
}