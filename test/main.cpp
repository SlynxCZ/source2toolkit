#include "main.h"

#include "source2toolkit/IToolkitApi.h"
#include "source2toolkit/IToolkitCommands.h"
#include "source2toolkit/IToolkitEvents.h"
#include "source2toolkit/IToolkitTypes.h"

#include "khook.hpp"
#include "eiface.h"
#include "igameeventsystem.h"
#include "schemasystem.h"
#include "interfaces/interfaces.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController.h"

Plugin g_Plugin;
TOOLKIT_EXPOSE(source2toolkit_test, g_Plugin);

IGameEventSystem* g_pGameEventSystem = nullptr;

Plugin::Plugin() :
    m_GameFrame(&IServerGameDLL::GameFrame, this, nullptr, &Plugin::Hook_GameFrame)
{
}

bool Plugin::Load(PluginId id, IToolkitAPI* api, char* error, size_t maxlen, bool late)
{
    if (late)
    {
        std::snprintf(error, maxlen, "Late load is not supported");
        return false;
    }

    TOOLKIT_SAVEVARS();

    GET_IFACE_CURRENT(GetEngineFactory, g_pEngineServer, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
    GET_IFACE_CURRENT(GetEngineFactory, g_pCVar, ICvar, CVAR_INTERFACE_VERSION);
    GET_IFACE_CURRENT(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
    GET_IFACE_ANY(GetServerFactory, g_pSource2Server, ISource2Server, INTERFACEVERSION_SERVERGAMEDLL);
    GET_IFACE_ANY(GetServerFactory, g_pSource2GameClients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);
    GET_IFACE_ANY(GetEngineFactory, g_pNetworkServerService, INetworkServerService, NETWORKSERVERSERVICE_INTERFACE_VERSION);
    GET_IFACE_ANY(GetEngineFactory, g_pSchemaSystem, CSchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
    GET_IFACE_ANY(GetEngineFactory, g_pGameEventSystem, IGameEventSystem, GAMEEVENTSYSTEM_INTERFACE_VERSION);
    GET_IFACE_ANY(GetEngineFactory, g_pNetworkMessages, INetworkMessages, NETWORKMESSAGES_INTERFACE_VERSION);
    GET_IFACE_ANY(GetServerFactory, g_pSource2GameEntities, ISource2GameEntities, SOURCE2GAMEENTITIES_INTERFACE_VERSION);

    api->AddListener(this, this);

    TOOLKIT_LOG(&g_Plugin, "API ptr: %p\n", api);
    TOOLKIT_LOG(&g_Plugin, "Commands ptr: %p\n", api->Commands());
    TOOLKIT_LOG(&g_Plugin, "Events ptr: %p\n", api->Events());
    TOOLKIT_LOG(&g_Plugin, "Scheduler ptr: %p\n", api->Scheduler());

    m_GameFrame.Add(GetSource2Server());

    api->Commands()->RegConCommand("s2t_test", [](const CCommandContext& ctx, const CCommand& cmd, Mode mode)
    {
        TOOLKIT_LOG(&g_Plugin, "s2t_test command executed!\n");
        CCSPlayerController* player = CCSPlayerController::FromSlot(ctx.GetPlayerSlot());
        if (!player)
            return;

        player->PrintToChat("s2t_test executed");
    });

    api->Events()->RegGameEvent("player_connect_full", [](IGameEvent* event, Mode mode, bool& dontBroadcast)
    {
        CCSPlayerController* player = static_cast<CCSPlayerController*>(event->GetPlayerController("userid"));
        if (!player)
            return Action::Ignore;

        TOOLKIT_LOG(&g_Plugin, "player_connect: %s\n", player->GetPlayerName());

        return Action::Ignore;
    }, Mode::Pre);

    TOOLKIT_LOG(&g_Plugin, "Load() done\n");

    return true;
}

bool Plugin::Unload(char* error, size_t maxlen)
{
    m_GameFrame.Remove(GetSource2Server());

    TOOLKIT_LOG(&g_Plugin, "Unload() done\n");

    return true;
}

KHook::Return<void> Plugin::Hook_GameFrame(IServerGameDLL* pThis, bool simulating, bool bFirstTick, bool bLastTick)
{
    TOOLKIT_LOG(&g_Plugin, "GameFrame(%p, %b, %b, %b) at %f\n", pThis, simulating, bFirstTick, bLastTick, GetGlobalVars()->curtime);

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