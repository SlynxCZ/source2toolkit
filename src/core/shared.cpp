//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "shared.h"
#include "icvar.h"
#include "iserver.h"
#include "schemasystem.h"

namespace shared
{
    ICvar* g_pCVar = nullptr;
    IVEngineServer* g_pEngine = nullptr;
    CGameEntitySystem* g_pEntitySystem = nullptr;
    IGameEventManager2* g_pGameEventManager = nullptr;
    IGameEventSystem* g_pGameEventSystem = nullptr;
    CGameResourceService* g_pGameResourceServiceServer = nullptr;
    INetworkMessages* g_pNetworkMessages = nullptr;
    INetworkServerService* g_pNetworkServerService = nullptr;
    CSchemaSystem* g_pSchemaSystem = nullptr;
    IServerGameDLL* g_pServer = nullptr;
    IServerGameClients* g_pGameClients = nullptr;
    ISource2GameEntities* g_pGameEntities = nullptr;

    CGlobalVars* g_pGlobalVars = nullptr;
    CGameConfig* g_pGameConfig = nullptr;
    CCSGameRules* g_pGameRules = nullptr;

    CGlobalVars *getGlobalVars() {
        INetworkGameServer *server = g_pNetworkServerService->GetIGameServer();
        if (!server) return nullptr;
        if (!g_pGlobalVars) g_pGlobalVars = server->GetGlobals();
        return g_pNetworkServerService->GetIGameServer()->GetGlobals();
    }

    bool g_bDetoursLoaded = false;
}
