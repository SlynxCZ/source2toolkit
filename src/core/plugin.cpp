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
#include "plugin.h"

#include "addresses.h"
#include "commands.h"
#include "convars.h"
#include "events.h"
#include "gameconfig.h"
#include "inlinehooks.h"
#include "patches.h"
#include "pluginmanager.h"
#include "raytrace.h"
#include "shared.h"
#include "virtualhooks.h"

#include "source2toolkit/utils/plat.h"

#include "schema/cgameresourceserviceserver.h"

#include "utils/log.h"
#include "utils/paths.h"
#include "utils/scheduler.h"

#define VERSION_STRING SEMVER " @ " GITHUB_SHA
#define BUILD_TIMESTAMP __DATE__ " " __TIME__

ToolkitCore g_ToolkitCore;
PLUGIN_EXPOSE(Source2Toolkit, g_ToolkitCore);

bool ToolkitCore::Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
    PLUGIN_SAVEVARS();

    if (late)
    {
        META_CONPRINTF("Plugin can't be loaded manually.\n");
        return false;
    }

    GET_V_IFACE_CURRENT(GetEngineFactory, shared::g_pCVar, ICvar, CVAR_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, shared::g_pEngine, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
    GET_V_IFACE_CURRENT(GetEngineFactory, shared::g_pGameEventSystem, IGameEventSystem, GAMEEVENTSYSTEM_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, shared::g_pGameResourceServiceServer, CGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, shared::g_pNetworkMessages, INetworkMessages, NETWORKMESSAGES_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, shared::g_pNetworkServerService, INetworkServerService, NETWORKSERVERSERVICE_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, shared::g_pSchemaSystem, CSchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetServerFactory, shared::g_pServer, IServerGameDLL, INTERFACEVERSION_SERVERGAMEDLL);
    GET_V_IFACE_CURRENT(GetServerFactory, shared::g_pGameClients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);
    GET_V_IFACE_CURRENT(GetServerFactory, shared::g_pGameEntities, ISource2GameEntities, SOURCE2GAMEENTITIES_INTERFACE_VERSION);

    g_pCVar = shared::g_pCVar;
    g_pEngineServer = shared::g_pEngine;
    g_pGameResourceServiceServer = reinterpret_cast<IGameResourceService*>(shared::g_pGameResourceServiceServer);
    g_pNetworkMessages = shared::g_pNetworkMessages;
    g_pNetworkServerService = shared::g_pNetworkServerService;
    g_pSchemaSystem = shared::g_pSchemaSystem;
    g_pSource2Server = shared::g_pServer;
    g_pSource2GameClients = shared::g_pGameClients;
    g_pSource2GameEntities = shared::g_pGameEntities;

    log::Init();
    scheduler::Init();

    auto coreconfig_path = std::string(paths::GetConfigsDirectory() + "/core");
    shared::g_pCoreConfig = new CCoreConfig(coreconfig_path);
    char coreconfig_error[255] = "";

    if (!shared::g_pCoreConfig->Init(coreconfig_error, sizeof(coreconfig_error)))
    {
        FP_ERROR("Failed to load CCoreConfig. Could not read \'{}\'. Error: {}", coreconfig_path, coreconfig_error);
        return false;
    }

    auto gamedata_folder = paths::GetGamedataDirectory();
    shared::g_pGameConfig = new CGameConfig(gamedata_folder);
    char conf_error[255] = {};

    if (!shared::g_pGameConfig->InitAll(gamedata_folder, conf_error, sizeof(conf_error)))
    {
        FP_ERROR("Failed to load CGameConfig. Error: {}", conf_error);
        return false;
    }

    if (!addresses::Initialize())
    {
        FP_ERROR("Could not initialize addresses.");
        return false;
    }

    if (!patches::Initialize())
    {
        FP_ERROR("Could not initialize patches.");
        return false;
    }

    commands::InitCommands();
    commands::commandsManager.UnlockConCommands();
    convars::convarsManager.UnlockConVars();
    inlinehooks::inlines.InitListeners();
    virtualhooks::virtuals.InitListeners();

    g_SMAPI->AddListener(this, this);
    ConVar_Register(FCVAR_RELEASE | FCVAR_CLIENT_CAN_EXECUTE | FCVAR_GAMEDLL);

    FP_INFO("Load() success!");

    if (!pluginManager.LoadAll())
    {
        FP_ERROR("Could not load plugins.");
        return false;
    }

    return true;
}

bool ToolkitCore::Unload(char* error, size_t maxlen)
{
    pluginManager.UnloadAll();

    commands::DestructCommands();
    events::DestructEvents();
    inlinehooks::inlines.DestructListeners();
    virtualhooks::virtuals.DestructListeners();
    scheduler::Shutdown();

    if (shared::g_pEntitySystem)
        shared::g_pEntitySystem->RemoveListenerEntity(&virtualhooks::entityListener);

    shared::g_bDetoursLoaded = false;

    ConVar_Unregister();

    FP_INFO("Unload() success!");

    log::Close();

    return true;
}

void ToolkitCore::AllPluginsLoaded()
{
    pluginManager.FireMetamodLoaded();
}

void ToolkitCore::OnPluginLoad(PluginId id)
{
    pluginManager.OnPluginLoad(id);
}

void ToolkitCore::OnPluginUnload(PluginId id)
{
    pluginManager.OnPluginUnload(id);
}

void ToolkitCore::OnLevelInit(char const* pMapName, char const* pMapEntities, char const* pOldLevel, char const* pLandmarkName, bool loadGame, bool background)
{
    pluginManager.OnLevelInit(pMapName, pMapEntities, pOldLevel, pLandmarkName, loadGame, background);
}

void ToolkitCore::OnLevelShutdown()
{
    pluginManager.OnLevelShutdown();
}

const char* ToolkitCore::GetAuthor() { return "Michal \"Slynx (˙·٠● S l y n x ●٠·˙)\" Přikryl, AlliedModders LLC."; }
const char* ToolkitCore::GetName() { return "Source2Toolkit"; }
const char* ToolkitCore::GetDescription() { return "Source2Toolkit"; }
const char* ToolkitCore::GetURL() { return "https://www.slynxdev.cz, https://www.alliedmods.net"; }
const char* ToolkitCore::GetLicense() { return "GPLv3"; }
const char* ToolkitCore::GetVersion() { return VERSION_STRING; }
const char* ToolkitCore::GetDate() { return BUILD_TIMESTAMP; }
const char* ToolkitCore::GetLogTag() { return "Source2Toolkit"; }