/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
 * AlliedModders LLC. All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl and
 * AlliedModders LLC give you permission to link the code of this program
 * (as well as its derivative works) to "Counter-Strike 2," "Source 2,"
 * "Steam," and any Game MODs or server software running on software by
 * Valve Corporation. You must obey the GNU General Public License in all
 * respects for all other code used.
 *
 * Additionally, this exception applies to all derivative works unless
 * otherwise stated in LICENSE.txt.
 *
 * Authors:
 *   - Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl
 *   - AlliedModders LLC
 *
 * Project: Source2Toolkit
 */
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
