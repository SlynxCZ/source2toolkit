//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "plugin.h"

#include "addresses.h"
#include "commands.h"
#include "gameconfig.h"
#include "virtualhooks.h"
#include "shared.h"

#include "utils/log.h"
#include "utils/paths.h"
#include "utils/scheduler.h"

#include "entitysystem.h"
#include "events.h"
#include "schema/cgameresourceserviceserver.h"

#define VERSION_STRING SEMVER " @ " GITHUB_SHA
#define BUILD_TIMESTAMP __DATE__ " " __TIME__

CS2ToolkitPlugin g_S2ToolkitPlugin;
PLUGIN_EXPOSE(Source2Toolkit, g_S2ToolkitPlugin);

CGameEntitySystem* GameEntitySystem()
{
    return shared::g_pEntitySystem;
}

bool CS2ToolkitPlugin::Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
    PLUGIN_SAVEVARS();

    if (late)
    {
        META_CONPRINTF("Plugin can't be loaded manually.\n");
    }

    GET_V_IFACE_CURRENT(GetEngineFactory, shared::g_pEngine, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
    GET_V_IFACE_CURRENT(GetEngineFactory, shared::g_pCVar, ICvar, CVAR_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetServerFactory, shared::g_pServer, IServerGameDLL, INTERFACEVERSION_SERVERGAMEDLL);
    GET_V_IFACE_ANY(GetServerFactory, shared::g_pGameClients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);
    GET_V_IFACE_ANY(GetEngineFactory, shared::g_pNetworkServerService, INetworkServerService, NETWORKSERVERSERVICE_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetEngineFactory, shared::g_pSchemaSystem, CSchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetEngineFactory, shared::g_pGameEventSystem, IGameEventSystem, GAMEEVENTSYSTEM_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetEngineFactory, shared::g_pNetworkMessages, INetworkMessages, NETWORKMESSAGES_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetServerFactory, shared::g_pGameEntities, ISource2GameEntities, SOURCE2GAMEENTITIES_INTERFACE_VERSION);

    g_pCVar = shared::g_pCVar;
    g_pSource2GameEntities = shared::g_pGameEntities;
    shared::g_pGameResourceServiceServer = (CGameResourceService*)g_pGameResourceServiceServer;
    if (!shared::g_pGameResourceServiceServer)
        return false;

    log::Init();
    scheduler::Init();

    auto gamedata_path = std::string(paths::GetRootDirectory() + "/gamedata.json");
    shared::g_pGameConfig = new CGameConfig(gamedata_path);
    char conf_error[255] = "";

    if (!shared::g_pGameConfig->Init(conf_error, sizeof(conf_error)))
    {
        FP_ERROR("Could not read '{}'. Error: {}", gamedata_path, conf_error);
        return false;
    }

    if (!addresses::Initialize())
    {
        FP_ERROR("Could not initialize addresses.");
        return false;
    }

    g_SMAPI->AddListener(this, this);

    commands::InitCommands();
    virtualhooks::virtuals.InitListeners();

    g_pCVar = shared::g_pCVar;
    ConVar_Register(FCVAR_RELEASE | FCVAR_CLIENT_CAN_EXECUTE | FCVAR_GAMEDLL);

    FP_INFO("Load() success!");
    return true;
}

bool CS2ToolkitPlugin::Unload(char* error, size_t maxlen)
{
    commands::DestructCommands();
    events::DestructEvents();
    virtualhooks::virtuals.DestructListeners();
    scheduler::Shutdown();

    shared::g_pEntitySystem->RemoveListenerEntity(&virtualhooks::entityListener);
    shared::g_bDetoursLoaded = false;

    FP_INFO("Unload() success!");

    log::Close();

    return true;
}

const char* CS2ToolkitPlugin::GetAuthor() { return "Slynx, contributors"; }
const char* CS2ToolkitPlugin::GetName() { return "Source2Toolkit"; }
const char* CS2ToolkitPlugin::GetDescription() { return "Source2Toolkit"; }
const char* CS2ToolkitPlugin::GetURL() { return "https://slynxdev.cz"; }
const char* CS2ToolkitPlugin::GetLicense() { return "GPLv3"; }
const char* CS2ToolkitPlugin::GetVersion() { return VERSION_STRING; }
const char* CS2ToolkitPlugin::GetDate() { return BUILD_TIMESTAMP; }
const char* CS2ToolkitPlugin::GetLogTag() { return "S2Toolkit"; }