//========= Copyright (c), Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#ifndef CSERVERSIDECLIENT_GAMEEVENTLEGACYPROXY_H
#define CSERVERSIDECLIENT_GAMEEVENTLEGACYPROXY_H
#ifdef _WIN32
#pragma once
#endif
#include "playerslot.h"
#include "igameevents.h"

class CServerSideClient_GameEventLegacyProxy : public IGameEventListener2
{
public:
    CPlayerSlot GetPlayerSlot();
};

#endif //CSERVERSIDECLIENT_GAMEEVENTLEGACYPROXY_H
