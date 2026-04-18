//========= Copyright (c), Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#ifndef CSOURCE1LEGACYGAMEEVENTSYSTEM_H
#define CSOURCE1LEGACYGAMEEVENTSYSTEM_H
#ifdef _WIN32
#pragma once
#endif
#include "utlstring.h"

class IGameEventListener2;

class CSource1LegacyGameEventGameSystem
{
public:
    CUtlString* GetName();

    IGameEventListener2* GetLegacyGameEventListener(int slot);
};

#endif //CSOURCE1LEGACYGAMEEVENTSYSTEM_H
