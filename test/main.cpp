#include "main.h"

#include "source2toolkit/IToolkitApi.h"
#include "source2toolkit/IToolkitCommands.h"
#include "source2toolkit/IToolkitEvents.h"
#include "source2toolkit/IToolkitTypes.h"

#include "source2toolkit/utils/addresses.h"
#include "source2toolkit/utils/commands.h"
#include "source2toolkit/utils/convars.h"
#include "source2toolkit/utils/events.h"

#include "khook.hpp"
#include "eiface.h"
#include "igameeventsystem.h"
#include "schemasystem.h"
#include "interfaces/interfaces.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerPawn.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_MovementServices.h"

Plugin g_Plugin;
TOOLKIT_EXPOSE(source2toolkit_test, g_Plugin);

IGameEventSystem* g_pGameEventSystem = nullptr;

Plugin::Plugin() :
    m_ProcessMovement(this, &Plugin::Hook_ProcessMovementPre, nullptr)
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

    TOOLKIT_LOG(this, "API ptr: %p\n", api);
    TOOLKIT_LOG(this, "Commands ptr: %p\n", api->Commands());
    TOOLKIT_LOG(this, "Events ptr: %p\n", api->Events());
    TOOLKIT_LOG(this, "Scheduler ptr: %p\n", api->Scheduler());

    UTIL_RegConCommand("s2t_test", [](const CCommandContext& ctx, const CCommand& cmd, Mode mode)
    {
        TOOLKIT_LOG(&g_Plugin, "s2t_test command executed!\n");
        CCSPlayerController* player = CCSPlayerController::FromSlot(ctx.GetPlayerSlot());
        if (!player)
            return;

        player->PrintToChat("s2t_test executed");
    });

    UTIL_RegGameEvent("player_connect_full", [](IGameEvent* event, Mode mode, bool& dontBroadcast)
    {
        CCSPlayerController* player = static_cast<CCSPlayerController*>(event->GetPlayerController("userid"));
        if (!player)
            return Action::Ignore;

        TOOLKIT_LOG(&g_Plugin, "player_connect: %s\n", player->GetPlayerName());

        return Action::Ignore;
    }, Mode::Pre);

    uintptr_t pProcessMovement = UTIL_FindPattern(g_pSource2Server, "55 48 89 E5 41 57 41 56 41 55 49 89 F5 41 54 53 48 89 FB 48 83 EC ? 48 8B 7F");
    if (pProcessMovement)
    {
        m_ProcessMovement.Configure(reinterpret_cast<void(*)(CCSPlayer_MovementServices*, void*, void*)>(pProcessMovement));
    }

    TOOLKIT_LOG(this, "Load() done\n");

    return true;
}

static uint16 s_autoIdx = 0;
static uint16 s_enableIdx = 0;

static bool m_WasAutoBhop = false;
static bool m_WasEnableBhop = false;

bool Plugin::Unload(char* error, size_t maxlen)
{
    if (s_autoIdx && m_WasAutoBhop)
        UTIL_SetConVarBool(s_autoIdx, false);

    if (s_enableIdx && m_WasEnableBhop)
        UTIL_SetConVarBool(s_enableIdx, false);

    m_ProcessMovement.~Function();

    TOOLKIT_LOG(this, "Unload() done\n");

    return true;
}

KHook::Return<void> Plugin::Hook_ProcessMovementPre(CCSPlayer_MovementServices* pThis, void*, void*)
{
    if (!pThis)
        return {KHook::Action::Ignore};

    auto* pawn = pThis->GetPlayerPawn();
    if (!pawn)
        return {KHook::Action::Ignore};

    auto* player = pawn->GetController();
    if (!player)
        return {KHook::Action::Ignore};

    if (!s_autoIdx)
        s_autoIdx = UTIL_FindConVar("sv_autobunnyhopping");

    if (!s_enableIdx)
        s_enableIdx = UTIL_FindConVar("sv_enablebunnyhopping");

    if (s_autoIdx)
    {
        if (!UTIL_GetConVarBool(s_autoIdx))
        {
            UTIL_SetConVarBool(s_autoIdx, true);
            m_WasAutoBhop = true;
        }
    }

    if (s_enableIdx)
    {
        if (!UTIL_GetConVarBool(s_enableIdx))
        {
            UTIL_SetConVarBool(s_enableIdx, true);
            m_WasEnableBhop = true;
        }
    }

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