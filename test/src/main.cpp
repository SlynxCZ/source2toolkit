#include "main.h"

#include <iserver.h>

#include "source2toolkit/IToolkitApi.h"
#include "source2toolkit/IToolkitCommands.h"
#include "source2toolkit/IToolkitEvents.h"
#include "source2toolkit/IToolkitTypes.h"

#include "source2toolkit/utils/addresses.h"
#include "source2toolkit/utils/commands.h"
#include "source2toolkit/utils/convars.h"
#include "source2toolkit/utils/events.h"
#include "source2toolkit/utils/gameconfig.h"

#include "source2toolkit/schema/schema.h"
#include "source2toolkit/schema/serversideclient.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController.h"

#include "khook.hpp"
#include "eiface.h"
#include "igameeventsystem.h"
#include "schemasystem.h"
#include "interfaces/interfaces.h"
#include "networksystem/inetworkmessages.h"
#include "source2toolkit/utils/scheduler.h"

TOOLKIT_EXPOSE(source2toolkit_test, g_Plugin);

Plugin g_Plugin;
IGameEventSystem* g_pGameEventSystem = nullptr;

bool Plugin::Load(PluginId id, IToolkitAPI* api, char* error, size_t maxlen, bool late)
{
    TOOLKIT_SAVEVARS();

    GET_IFACE_CURRENT(GetEngineFactory, g_pEngineServer, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
    GET_IFACE_CURRENT(GetEngineFactory, g_pCVar, ICvar, CVAR_INTERFACE_VERSION);
    GET_IFACE_CURRENT(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
    GET_IFACE_CURRENT(GetFileSystemFactory, g_pFullFileSystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION);
    GET_IFACE_ANY(GetServerFactory, g_pSource2Server, ISource2Server, INTERFACEVERSION_SERVERGAMEDLL);
    GET_IFACE_ANY(GetServerFactory, g_pSource2GameClients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);
    GET_IFACE_ANY(GetEngineFactory, g_pNetworkServerService, INetworkServerService, NETWORKSERVERSERVICE_INTERFACE_VERSION);
    GET_IFACE_ANY(GetEngineFactory, g_pSchemaSystem, CSchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
    GET_IFACE_ANY(GetEngineFactory, g_pGameEventSystem, IGameEventSystem, GAMEEVENTSYSTEM_INTERFACE_VERSION);
    GET_IFACE_ANY(GetEngineFactory, g_pNetworkMessages, INetworkMessages, NETWORKMESSAGES_INTERFACE_VERSION);
    GET_IFACE_ANY(GetServerFactory, g_pSource2GameEntities, ISource2GameEntities, SOURCE2GAMEENTITIES_INTERFACE_VERSION);

    api->AddListener(this, this);

    TOOLKIT_LOG(this, "Load() done\n");

    return true;
}

bool Plugin::Unload(char* error, size_t maxlen)
{
    TOOLKIT_LOG(this, "Unload() done\n");

    return true;
}

void Plugin::OnPluginLoad(PluginId id)
{
    TOOLKIT_LOG(this, "OnPluginLoad(%d)", id);
}

void Plugin::OnPluginUnload(PluginId id)
{
    TOOLKIT_LOG(this, "OnPluginUnload(%d)", id);
}

void Plugin::OnAllToolkitPluginsLoaded()
{
    TOOLKIT_LOG(this, "OnAllToolkitPluginsLoaded()");
}

void Plugin::OnAllMetamodPluginsLoaded()
{
    TOOLKIT_LOG(this, "OnAllMetamodPluginsLoaded()");
}

void Plugin::OnLevelInit(const char* mapName, const char* mapEntities, const char* oldLevel,
    const char* landmarkName, bool loadGame, bool background)
{
    TOOLKIT_LOG(this,
        "OnLevelInit(map=%s, old=%s, landmark=%s, loadGame=%d, background=%d)",
        mapName ? mapName : "nullptr",
        oldLevel ? oldLevel : "nullptr",
        landmarkName ? landmarkName : "nullptr",
        loadGame,
        background
    );
}

void Plugin::OnLevelShutdown()
{
    TOOLKIT_LOG(this, "OnLevelShutdown()");
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
