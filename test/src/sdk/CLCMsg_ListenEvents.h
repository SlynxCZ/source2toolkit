//========= Copyright (c), Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#ifndef CLCMSG_LISTENEVENTS_H
#define CLCMSG_LISTENEVENTS_H
#ifdef _WIN32
#pragma once
#endif
#include "playerslot.h"

class CLCMsg_ListenEvents
{
public:
    CPlayerSlot GetPlayerSlot();

    int GetEventMaskSize();
    uint32_t* GetEventMaskData();
    uint32_t GetEventMask(int index);

    bool HasEvent(int eventId);
};

#endif //CLCMSG_LISTENEVENTS_H
