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
    extern IServerGameDLL* g_pServer;
    extern IVEngineServer* g_pEngine;
    extern CSchemaSystem* g_pSchemaSystem;
    extern IGameEventManager2* g_pGameEventManager;
    extern IGameEventSystem* g_pGameEventSystem;
    extern ISource2GameEntities* g_pGameEntities;
    extern INetworkMessages* g_pNetworkMessages;
    extern INetworkServerService* g_pNetworkServerService;
    extern CGameEntitySystem* g_pEntitySystem;
    extern IServerGameClients* g_pGameClients;
    extern CGlobalVars* g_pGlobalVars;
    extern CGameResourceService* g_pGameResourceServiceServer;
    extern CGameConfig* g_pGameConfig;
    extern CCSGameRules* g_pGameRules;

    CGlobalVars* getGlobalVars();

    extern bool g_bDetoursLoaded;
}
