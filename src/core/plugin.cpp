//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "plugin.h"

#include "addresses.h"
#include "commands.h"
#include "events.h"
#include "gameconfig.h"
#include "inlinehooks.h"
#include "pluginmanager.h"
#include "raytrace.h"
#include "shared.h"
#include "virtualhooks.h"

#include "source2toolkit/utils/plat.h"

#include "schema/cgameresourceserviceserver.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController_InGameMoneyServices.h"

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

    auto gamedata_folder = paths::GetGamedataDirectory();
    shared::g_pGameConfig = new CGameConfig(gamedata_folder);
    char conf_error[255] = {};

    if (!shared::g_pGameConfig->InitAll(gamedata_folder, conf_error, sizeof(conf_error)))
    {
        FP_ERROR("Failed to load gamedata folder. Error: {}", conf_error);
        return false;
    }

    if (!addresses::Initialize())
    {
        FP_ERROR("Could not initialize addresses.");
        return false;
    }

    commands::InitCommands();
    inlinehooks::inlines.InitListeners();
    virtualhooks::virtuals.InitListeners();
    raytrace::rayTrace.InitRayTrace();

    {
        uintptr_t addr = DynLibUtils::CModule(shared::g_pServer).FindPattern(shared::g_pGameConfig->GetSignature("SetSchemaHammerUniqueId"));
        if (addr)
        {
            uint8_t patch = (uint8_t)strtoul(shared::g_pGameConfig->GetPatch("SetSchemaHammerUniqueId"), nullptr, 16);
            Plat_WriteMemory((void*)addr, &patch, 1);
            FP_ERROR("Patched SetSchemaHammerUniqueId at {}", fmt::ptr(addr));
        }
    }

    g_SMAPI->AddListener(this, this);
    ConVar_Register(FCVAR_RELEASE | FCVAR_CLIENT_CAN_EXECUTE | FCVAR_GAMEDLL);

    FP_INFO("Load() success!");

    pluginManager.LoadAll();

    return true;
}

bool ToolkitCore::Unload(char* error, size_t maxlen)
{
    pluginManager.UnloadAll();

    commands::DestructCommands();
    events::DestructEvents();
    inlinehooks::inlines.DestructListeners();
    virtualhooks::virtuals.DestructListeners();
    raytrace::rayTrace.DestructRayTrace();
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

const char* ToolkitCore::GetAuthor() { return "Slynx (˙·٠● S l y n x ●٠·˙), AlliedModders and contributors"; }
const char* ToolkitCore::GetName() { return "Source2Toolkit"; }
const char* ToolkitCore::GetDescription() { return "Source2Toolkit"; }
const char* ToolkitCore::GetURL() { return "https://www.slynxdev.cz, https://www.alliedmods.net"; }
const char* ToolkitCore::GetLicense() { return "GPLv3"; }
const char* ToolkitCore::GetVersion() { return VERSION_STRING; }
const char* ToolkitCore::GetDate() { return BUILD_TIMESTAMP; }
const char* ToolkitCore::GetLogTag() { return "Source2Toolkit"; }