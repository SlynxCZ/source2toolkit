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
#include "customhud.h"
#include "events.h"
#include "gameconfig.h"
#include "gamesystems.h"
#include "http.h"
#include "networkmessages.h"
#include "inlinehooks.h"
#include "patches.h"
#include "pluginmanager.h"
#include "raytrace.h"
#include "shared.h"
#include "virtualhooks.h"

#include "source2toolkit/utils/plat.h"

#include "utils/log.h"
#include "utils/paths.h"
#include "core/scheduler.h"
#include "core/paths.h"

#define VERSION_STRING SEMVER " @ " GITHUB_SHA
#define BUILD_TIMESTAMP __DATE__ " " __TIME__

ToolkitCore g_ToolkitCore;
PLUGIN_EXPOSE(Source2Toolkit, g_ToolkitCore);

bool ToolkitCore::Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
    PLUGIN_SAVEVARS();
    // The toolkit owns the private SourceHook engine; every S2Toolkit plugin
    // binds onto this same instance through TOOLKIT_SOURCEHOOK_INTERFACE, so
    // SH_CALL and SH_GET_INLINEHOOK_ORIGINAL can see across plugin boundaries.
    SH_METAMOD_OVERRIDE_SAVEVARS(id);

    if (late)
    {
        META_CONPRINTF("Plugin can't be loaded manually.\n");
        return false;
    }

    GET_V_IFACE_CURRENT(GetServerFactory, g_pSource2Server, ISource2Server, SOURCE2SERVER_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetServerFactory, g_pSource2ServerConfig, ISource2ServerConfig, SOURCE2SERVERCONFIG_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetServerFactory, g_pSource2GameClients, ISource2GameClients, SOURCE2GAMECLIENTS_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetServerFactory, g_pSource2GameEntities, ISource2GameEntities, SOURCE2GAMEENTITIES_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, g_pEngineServer, IVEngineServer2, SOURCE2ENGINETOSERVER_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, g_pCVar, ICvar, CVAR_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, g_pSchemaSystem, ISchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, g_pNetworkServerService, INetworkServerService, NETWORKSERVERSERVICE_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, g_pNetworkSystem, INetworkSystem, NETWORKSYSTEM_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, g_pNetworkMessages, INetworkMessages, NETWORKMESSAGES_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, g_pNetworkStringTableServer, INetworkStringTableContainer, SOURCE2ENGINETOSERVERSTRINGTABLE_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, g_pEngineServiceMgr, IEngineServiceMgr, ENGINESERVICEMGR_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, g_pHostStateMgr, IHostStateMgr, HOSTSTATEMGR_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetEngineFactory, g_pLocalize, ILocalize, LOCALIZE_INTERFACE_VERSION);
    GET_V_IFACE_CURRENT(GetFileSystemFactory, g_pFullFileSystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION);

    // IGameEventSystem has no global in interfaces.h at all. The schema system
    // and game resource service do, but as the interface type -- the toolkit
    // needs the concrete classes' methods, so it downcasts once here.
    GET_V_IFACE_CURRENT(GetEngineFactory, shared::g_pGameEventSystem, IGameEventSystem, GAMEEVENTSYSTEM_INTERFACE_VERSION);

    shared::g_pSchemaSystem = static_cast<CSchemaSystem*>(g_pSchemaSystem);

    log::Init();
    scheduler::Init();

    // Before anything below goes looking for one of them.
    paths::EnsureLayout();

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

    // Not fatal: a failed scan only means plugins cannot register game
    // systems, which most do not. IToolkitGameSystems::IsAvailable() says so.
    gamesystems::gameSystemsManager.Init();

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

    pluginManager.StartFileWatcher();

    return true;
}

bool ToolkitCore::Unload(char* error, size_t maxlen)
{
    pluginManager.StopFileWatcher();
    pluginManager.UnloadAll();

    commands::DestructCommands();
    events::DestructEvents();
    inlinehooks::inlines.DestructListeners();
    virtualhooks::virtuals.DestructListeners();
    scheduler::Shutdown();
    // Takes the engine-level change callback back out with it.
    convars::convarsManager.Shutdown();
    // Callbacks are std::functions holding code inside plugin libraries.
    http::httpManager.Shutdown();

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

// These two are IMetamodListener's, so the id is a Metamod plugin's -- they go
// to the toolkit's own OnMetamodPluginLoad/Unload, not to the callbacks that
// report .stx plugins coming and going.
void ToolkitCore::OnPluginLoad(PluginId id)
{
    pluginManager.FireMetamodPluginLoaded(id);
}

void ToolkitCore::OnPluginUnload(PluginId id)
{
    pluginManager.FireMetamodPluginUnloaded(id);
}

void ToolkitCore::OnLevelInit(char const* pMapName, char const* pMapEntities, char const* pOldLevel,
                              char const* pLandmarkName, bool loadGame, bool background)
{
    pluginManager.OnLevelInit(pMapName, pMapEntities, pOldLevel, pLandmarkName, loadGame, background);
}

void* ToolkitCore::OnMetamodQuery(const char* iface, int* ret)
{
    // Only what a toolkit plugin chose to expose through OnMetamodQuery, which
    // answers like OnToolkitQuery unless the plugin says otherwise. The
    // toolkit's own interfaces are deliberately not offered here: they are for
    // toolkit plugins, and SourceHook in particular must not be handed to a
    // plugin that did not load through the toolkit -- it would be binding to
    // an engine it does not own.
    for (auto& p : pluginManager.m_plugins)
    {
        for (auto* l : p->listeners)
        {
            if (void* res = l->OnMetamodQuery(iface, ret))
            {
                if (ret) *ret = META_IFACE_OK;
                return res;
            }
        }
    }

    if (ret) *ret = META_IFACE_FAILED;
    return nullptr;
}

void ToolkitCore::OnLevelShutdown()
{
    pluginManager.OnLevelShutdown();

    // The layouts these point at do not survive the level change.
    customhud::customHudManager.Clear();
}

const char* ToolkitCore::GetAuthor() { return "Michal \"Slynx (˙·٠● S l y n x ●٠·˙)\" Přikryl, AlliedModders LLC."; }
const char* ToolkitCore::GetName() { return "Source2Toolkit"; }
const char* ToolkitCore::GetDescription() { return "Source2Toolkit"; }
const char* ToolkitCore::GetURL() { return "https://www.slynxdev.cz, https://www.alliedmods.net"; }
const char* ToolkitCore::GetLicense() { return "Source2Toolkit (GPLv3 with exceptions)"; }
const char* ToolkitCore::GetVersion() { return VERSION_STRING; }
const char* ToolkitCore::GetDate() { return BUILD_TIMESTAMP; }
const char* ToolkitCore::GetLogTag() { return "Source2Toolkit"; }
