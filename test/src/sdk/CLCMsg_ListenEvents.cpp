//========= Copyright (c), Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#include "CLCMsg_ListenEvents.h"

#include "source2toolkit/utils/addresses.h"
#include "source2toolkit/utils/gameconfig.h"

CPlayerSlot CLCMsg_ListenEvents::GetPlayerSlot()
{
    return *(CPlayerSlot*)(UTIL_Offset((uintptr_t)this, UTIL_GetOffset("CLCMsg_ListenEvents_PlayerSlot")));
}

int CLCMsg_ListenEvents::GetEventMaskSize()
{
    return *(int*)(UTIL_Offset((uintptr_t)this, UTIL_GetOffset("CLCMsg_ListenEvents_EventMaskSize")));
}

uint32_t* CLCMsg_ListenEvents::GetEventMaskData()
{
    return *(uint32_t**)(UTIL_Offset((uintptr_t)this, UTIL_GetOffset("CLCMsg_ListenEvents_EventMaskData")));
}

uint32_t CLCMsg_ListenEvents::GetEventMask(int index)
{
    int size = GetEventMaskSize();

    if (index < 0 || index >= size)
        return 0;

    return GetEventMaskData()[index];
}