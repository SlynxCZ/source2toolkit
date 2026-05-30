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
#include "main.h"

#include "source2toolkit/IToolkitApi.h"
#include "source2toolkit/IToolkitAddresses.h"
#include "source2toolkit/IToolkitCommands.h"
#include "source2toolkit/IToolkitConVars.h"
#include "source2toolkit/IToolkitEntities.h"
#include "source2toolkit/IToolkitEvents.h"
#include "source2toolkit/IToolkitGameConfig.h"
#include "source2toolkit/IToolkitMemory.h"
#include "source2toolkit/IToolkitMenus.h"
#include "source2toolkit/IToolkitModule.h"
#include "source2toolkit/IToolkitMySQL.h"
#include "source2toolkit/IToolkitScheduler.h"
#include "source2toolkit/IToolkitTrace.h"
#include "source2toolkit/IToolkitTypes.h"

#include "source2toolkit/schema/entity/classes/CCSPlayerController.h"
#include "source2toolkit/schema/schema.h"
#include "source2toolkit/schema/serversideclient.h"

#include "steam/steam_api.h"
#include "steam/steam_gameserver.h"
#include "steam/steam_api_common.h"

#include "khook.hpp"
#include "eiface.h"
#include "igameeventsystem.h"
#include "iserver.h"
#include "schemasystem.h"
#include "interfaces/interfaces.h"
#include "networksystem/inetworkmessages.h"

#include <cstdio>

Plugin g_Plugin;
TOOLKIT_EXPOSE(source2toolkit_test, g_Plugin);

IToolkitModule* g_pLibSteamApi = nullptr;
IGameEventSystem* g_pGameEventSystem = nullptr;
CSteamGameServerAPIContext* g_pSteamAPI = nullptr;

Plugin::Plugin() :
    m_pGameServerSteamAPIActivated(new KHook::Virtual(&ISource2Server::GameServerSteamAPIActivated, this, &Plugin::CSource2Server_GameServerSteamAPIActivated, nullptr))
{
}

bool Plugin::Load(PluginId id, IToolkitAPI* api, char* error, size_t maxlen, bool late)
{
    TOOLKIT_SAVEVARS();

    GET_VALVE_IFACE_CURRENT(GetEngineFactory, g_pEngineServer, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
    GET_VALVE_IFACE_CURRENT(GetEngineFactory, g_pCVar, ICvar, CVAR_INTERFACE_VERSION);
    GET_VALVE_IFACE_CURRENT(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
    GET_VALVE_IFACE_CURRENT(GetFileSystemFactory, g_pFullFileSystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION);
    GET_VALVE_IFACE_CURRENT(GetServerFactory, g_pSource2Server, ISource2Server, INTERFACEVERSION_SERVERGAMEDLL);
    GET_VALVE_IFACE_CURRENT(GetServerFactory, g_pSource2GameClients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);
    GET_VALVE_IFACE_CURRENT(GetEngineFactory, g_pNetworkServerService, INetworkServerService, NETWORKSERVERSERVICE_INTERFACE_VERSION);
    GET_VALVE_IFACE_CURRENT(GetEngineFactory, g_pSchemaSystem, CSchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
    GET_VALVE_IFACE_CURRENT(GetEngineFactory, g_pGameEventSystem, IGameEventSystem, GAMEEVENTSYSTEM_INTERFACE_VERSION);
    GET_VALVE_IFACE_CURRENT(GetEngineFactory, g_pNetworkMessages, INetworkMessages, NETWORKMESSAGES_INTERFACE_VERSION);
    GET_VALVE_IFACE_CURRENT(GetServerFactory, g_pSource2GameEntities, ISource2GameEntities, SOURCE2GAMEENTITIES_INTERFACE_VERSION);

    api->AddListener(this, this);

    // Function hooks
    {
        m_pGameServerSteamAPIActivated->Add(g_pSource2Server);
    }

    // Console commands
    g_ToolkitAPI->Commands()->RegConCommand(g_PluginID, "test", [](const CCommandContext& ctx, const CCommand& args, Mode)
    {
        CCSPlayerController* player = CCSPlayerController::FromSlot(ctx.GetPlayerSlot());
        if (!player) return;

        TOOLKIT_LOG(&g_Plugin, "test: player=%p, original=%p, name=%s, steamid=%llu\n", player, player->GetOriginal(), player->GetPlayerName(), player->GetSteamID());
    });

    TOOLKIT_LOG(this, "Load( id=%d, api=%p, late=%d ) done\n", id, api, late);

    return true;
}

bool Plugin::Unload(char* error, size_t maxlen)
{
    m_pGameServerSteamAPIActivated->Remove(g_pSource2Server);

    TOOLKIT_LOG(this, "Unload() done\n");

    return true;
}

void Plugin::OnPluginLoad(PluginId id)
{
    TOOLKIT_LOG(this, "OnPluginLoad( id=%d )\n", id);
}

void Plugin::OnPluginUnload(PluginId id)
{
    TOOLKIT_LOG(this, "OnPluginUnload( id=%d )\n", id);
}

void Plugin::OnAllToolkitPluginsLoaded()
{
    TOOLKIT_LOG(this, "OnAllToolkitPluginsLoaded()\n");
}

void Plugin::OnAllMetamodPluginsLoaded()
{
    TOOLKIT_LOG(this, "OnAllMetamodPluginsLoaded()\n");
}

void Plugin::OnLevelInit(const char* mapName, const char* mapEntities, const char* oldLevel, const char* landmarkName, bool loadGame, bool background)
{
    TOOLKIT_LOG(this, "OnLevelInit( map=%s, old=%s, landmark=%s, loadGame=%d, background=%d )\n", mapName ? mapName : "nullptr", oldLevel ? oldLevel : "nullptr", landmarkName ? landmarkName : "nullptr", loadGame, background);
}

void Plugin::OnLevelShutdown()
{
    TOOLKIT_LOG(this, "OnLevelShutdown()\n");
}

KHook::Return<void> Plugin::CSource2Server_GameServerSteamAPIActivated(ISource2Server* pThis)
{
    TOOLKIT_LOG(this, "CSource2Server_GameServerSteamAPIActivated( pThis=%p )\n", pThis);

    g_pSteamAPI = new CSteamGameServerAPIContext();
    g_pSteamAPI->Init();

    return {KHook::Action::Ignore};
}

const char* Plugin::GetVersion()
{
    return "1.0.0";
}

const char* Plugin::GetAuthor()
{
    return "Slynx";
}

const char* Plugin::GetDescription()
{
    return "Source2Toolkit test plugin";
}

const char* Plugin::GetName()
{
    return "Source2Toolkit test";
}
