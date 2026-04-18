//========= Copyright (c), Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#include "CServerSideClient_GameEventLegacyProxy.h"

#include "source2toolkit/utils/addresses.h"
#include "source2toolkit/utils/gameconfig.h"

CPlayerSlot CServerSideClient_GameEventLegacyProxy::GetPlayerSlot()
{
    return *(CPlayerSlot*)(UTIL_Offset((uintptr_t)this, UTIL_GetOffset("CLCMsg_ListenEvents_PlayerSlot")));
}
