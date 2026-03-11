//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "Shared.h"
#include "icvar.h"
#include "iserver.h"
#include "schemasystem.h"

namespace shared
{
    ICvar* g_pCVar = nullptr;
    IServerGameDLL* g_pServer = nullptr;
    IVEngineServer* g_pEngine = nullptr;
    CSchemaSystem* g_pSchemaSystem = nullptr;
    IGameEventManager2* g_pGameEventManager = nullptr;
    IGameEventSystem* g_pGameEventSystem = nullptr;
    ISource2GameEntities* g_pGameEntities = nullptr;
    INetworkMessages* g_pNetworkMessages = nullptr;
    INetworkServerService* g_pNetworkServerService = nullptr;
    CGameEntitySystem* g_pEntitySystem = nullptr;
    IServerGameClients* g_pGameClients = nullptr;
    CGlobalVars *g_pGlobalVars = nullptr;
    CGameResourceService *g_pGameResourceServiceServer = nullptr;
    CGameConfig *g_pGameConfig = nullptr;

    CGlobalVars *getGlobalVars() {
        INetworkGameServer *server = g_pNetworkServerService->GetIGameServer();
        if (!server) return nullptr;
        if (!g_pGlobalVars) g_pGlobalVars = server->GetGlobals();
        return g_pNetworkServerService->GetIGameServer()->GetGlobals();
    }

    bool g_bDetoursLoaded = false;
}
