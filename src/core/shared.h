//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "eiface.h"
#include "icvar.h"
#include "schemasystem.h"
#include "entitysystem.h"
#include "igameevents.h"
#include "vector"
#include "gameconfig.h"
#include "igameeventsystem.h"
#include <memory>

class CCSGameRules;
class CGameResourceService;

namespace shared
{
    extern ICvar* g_pCVar;
    extern IVEngineServer* g_pEngine;
    extern CGameEntitySystem* g_pEntitySystem;
    extern IGameEventManager2* g_pGameEventManager;
    extern IGameEventSystem* g_pGameEventSystem;
    extern CGameResourceService* g_pGameResourceServiceServer;
    extern INetworkMessages* g_pNetworkMessages;
    extern INetworkServerService* g_pNetworkServerService;
    extern CSchemaSystem* g_pSchemaSystem;
    extern IServerGameDLL* g_pServer;
    extern IServerGameClients* g_pGameClients;
    extern ISource2GameEntities* g_pGameEntities;

    extern CGlobalVars* g_pGlobalVars;
    extern CGameConfig* g_pGameConfig;
    extern CCSGameRules* g_pGameRules;

    CGlobalVars* getGlobalVars();

    extern bool g_bDetoursLoaded;
}
