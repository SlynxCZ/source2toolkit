//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "plugin.h"

#include "gameconfig.h"
#include "listeners.h"
#include "shared.h"

#include "utils/log.h"
#include "utils/paths.h"
#include "utils/tasks.h"

#include "entitysystem.h"
#include "schema/cgameresourceserviceserver.h"

#define VERSION_STRING SEMVER " @ " GITHUB_SHA
#define BUILD_TIMESTAMP __DATE__ " " __TIME__

PLUGIN_EXPOSE(Source2Toolkit, g_iPlugin);

CGameEntitySystem* GameEntitySystem()
{
    return *reinterpret_cast<CGameEntitySystem**>((uintptr_t)(g_pGameResourceServiceServer) + shared::g_pGameConfig->GetOffset("GameEntitySystem"));
}

IPlugin g_iPlugin;

bool IPlugin::Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
    PLUGIN_SAVEVARS();

    GET_V_IFACE_CURRENT(GetEngineFactory, shared::g_pCVar, ICvar, CVAR_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetServerFactory, shared::g_pServer, IServerGameDLL, INTERFACEVERSION_SERVERGAMEDLL);
    GET_V_IFACE_CURRENT(GetEngineFactory, shared::g_pEngine, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
    GET_V_IFACE_ANY(GetEngineFactory, shared::g_pSchemaSystem, CSchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetEngineFactory, shared::g_pGameEventSystem, IGameEventSystem, GAMEEVENTSYSTEM_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetServerFactory, shared::g_pGameEntities, ISource2GameEntities, SOURCE2GAMEENTITIES_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetServerFactory, shared::g_pGameClients, IServerGameClients, SOURCE2GAMECLIENTS_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetEngineFactory, shared::g_pNetworkMessages, INetworkMessages, NETWORKMESSAGES_INTERFACE_VERSION);
    GET_V_IFACE_ANY(GetEngineFactory, shared::g_pNetworkServerService, INetworkServerService, NETWORKSERVERSERVICE_INTERFACE_VERSION);

    g_pCVar = shared::g_pCVar;
    g_pSource2GameEntities = shared::g_pGameEntities;
    shared::g_pGameResourceServiceServer = (CGameResourceService*)g_pGameResourceServiceServer;
    if (!shared::g_pGameResourceServiceServer)
        return false;

    log::Init();
    tasks::Init();

    auto gamedata_path = std::string(paths::GetRootDirectory() + "/gamedata.json");
    shared::g_pGameConfig = new CGameConfig(gamedata_path);
    char conf_error[255] = "";

    if (!shared::g_pGameConfig->Init(conf_error, sizeof(conf_error)))
    {
        FP_ERROR("Could not read '{}'. Error: {}", gamedata_path, conf_error);
        return false;
    }

    g_SMAPI->AddListener(this, this);
    listeners::InitListeners();

    g_pCVar = shared::g_pCVar;
    ConVar_Register(FCVAR_RELEASE | FCVAR_CLIENT_CAN_EXECUTE | FCVAR_GAMEDLL);

    if (late)
    {
        shared::g_pEntitySystem = GameEntitySystem();
        shared::g_bDetoursLoaded = true;
    }

    FP_INFO("Load() success!");
    return true;
}

bool IPlugin::Unload(char* error, size_t maxlen)
{
    listeners::DestructListeners();
    tasks::Shutdown();

    FP_INFO("Unload() success!");

    log::Close();

    return true;
}

const char* IPlugin::GetAuthor() { return "Slynx, contributors"; }
const char* IPlugin::GetName() { return "Source2Toolkit"; }
const char* IPlugin::GetDescription() { return "Source2Toolkit"; }
const char* IPlugin::GetURL() { return "https://slynxdev.cz"; }
const char* IPlugin::GetLicense() { return "GPLv3"; }
const char* IPlugin::GetVersion() { return VERSION_STRING; }
const char* IPlugin::GetDate() { return BUILD_TIMESTAMP; }
const char* IPlugin::GetLogTag() { return "S2Toolkit"; }