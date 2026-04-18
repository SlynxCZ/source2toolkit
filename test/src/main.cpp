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

#include "sdk/CLCMsg_ListenEvents.h"
#include "sdk/CServerSideClient_GameEventLegacyProxy.h"
#include "sdk/CSource1LegacyGameEventGameSystem.h"

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
static std::unordered_map<int, std::string> g_EventIdToName;
static std::unordered_set<int> g_BlacklistIds;
static std::unordered_set<std::string> g_Blacklist;

Plugin::Plugin() :
    m_hListenBitsReceived(this, nullptr, &Plugin::Hook_ListenBitsReceived)
{
}

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

    {
        m_pListenBitsReceived = UTIL_FindPattern(g_pSource2Server, UTIL_GetSignature("CSource1LegacyGameEventGameSystem_ListenBitsReceived"));
        if (m_pListenBitsReceived)
            m_hListenBitsReceived.Configure(reinterpret_cast<bool(*)(CSource1LegacyGameEventGameSystem*, CLCMsg_ListenEvents*)>(m_pListenBitsReceived));
    }

    // Load configuration file
    {
        int currentId = 0;

        char basePath[256];
        V_strncpy(basePath, UTIL_GetModulePath(this), sizeof(basePath));
        V_StripFilename(basePath);
        V_AppendSlash(basePath, sizeof(basePath));
        V_strncat(basePath, "source2toolkit_test/", sizeof(basePath));

        char path[512];

        // blacklist.gameevents
        V_snprintf(path, sizeof(path), "%sblacklist.gameevents", basePath);
        LoadBlacklist(path, "blacklist");

        // resource/core.gameevents
        V_snprintf(path, sizeof(path), "%sresource/core.gameevents", basePath);
        LoadEventsFromFile("resource/core.gameevents", "core game events", currentId);

        // resource/game.gameevents
        V_snprintf(path, sizeof(path), "%sresource/game.gameevents", basePath);
        LoadEventsFromFile("resource/core.gameevents", "gameevents", currentId);

        // resource/mod.gameevents
        V_snprintf(path, sizeof(path), "%sresource/mod.gameevents", basePath);
        LoadEventsFromFile("resource/core.gameevents", "cstrikeevents", currentId);

        TOOLKIT_LOG(this, "Loaded %d events total\n", currentId);
    }

    TOOLKIT_LOG(this, "Load() done\n");

    return true;
}

bool Plugin::Unload(char* error, size_t maxlen)
{
    {
        m_hListenBitsReceived.~Function();
    }

    TOOLKIT_LOG(this, "Unload() done\n");

    return true;
}

KHook::Return<bool> Plugin::Hook_ListenBitsReceived(CSource1LegacyGameEventGameSystem* pThis, CLCMsg_ListenEvents* pMsg)
{
    // TOOLKIT_LOG(this, "Hook_ListenBitsReceived( %p %p )\n", pThis, pMsg);

    auto mgr = GetGameEventManager();
    if (!mgr)
        return { KHook::Action::Ignore, false };

    CPlayerSlot slot = pMsg->GetPlayerSlot();
    int iSlot = slot.Get();

    auto player = CCSPlayerController::FromSlot(slot);
    if (!player || player->IsBot())
        return { KHook::Action::Ignore, false };

    auto* proxy = pThis->GetLegacyGameEventListener(iSlot);
    if (!proxy)
        return { KHook::Action::Ignore, false };

    const char* playerName = player->GetPlayerName();

    bool bDetected = false;

    for (const auto& [eventId, name] : g_EventIdToName)
    {
        if (mgr->FindListener(proxy, name.c_str()))
        {
            // TOOLKIT_LOG(this, "[ListenBits] %s listens to: %s (%d)\n", playerName, name.c_str(), eventId);

            if (g_BlacklistIds.contains(eventId))
            {
                // TOOLKIT_LOG(this, "BLACKLIST HIT: %s (%d)\n", name.c_str(), eventId);

                bDetected = true;
            }
        }
    }

    if (bDetected)
    {
        TOOLKIT_LOG(this, "Player %s detected for using event %s\n", playerName);
        g_pEngineServer->DisconnectClient(player->GetPlayerSlot(), NETWORK_DISCONNECT_KICKED_UNTRUSTEDACCOUNT);
    }

    return { KHook::Action::Ignore, false };
}

void Plugin::LoadBlacklist(const char* pchPath, const char* pchKVName)
{
    if (!Plat_FileExists(pchPath, 0))
    {
        TOOLKIT_LOG(this, "File does not exist: %s\n", pchPath);
        return;
    }

    KeyValues::AutoDelete kv(pchKVName);

    if (!kv->LoadFromFile(g_pFullFileSystem, pchPath))
    {
        TOOLKIT_LOG(this, "Failed to load: %s\n", pchPath);
        return;
    }

    int count = 0;

    for (KeyValues* pEvent = kv->GetFirstSubKey(); pEvent; pEvent = pEvent->GetNextKey())
    {
        const char* eventName = pEvent->GetName();

        if (!eventName || !*eventName)
            continue;

        g_Blacklist.insert(eventName);
        count++;
    }

    TOOLKIT_LOG(this, "Loaded %d blacklist entries\n", count);
}

void Plugin::LoadEventsFromFile(const char* pchPath, const char* pchKVName, int& iCurrentId)
{
    KeyValues::AutoDelete kv(pchKVName);

    if (!kv->LoadFromFile(g_pFullFileSystem, pchPath, "GAME"))
    {
        TOOLKIT_LOG(this, "Failed to load: %s\n", pchPath);
        return;
    }

    for (KeyValues* pEvent = kv->GetFirstSubKey(); pEvent; pEvent = pEvent->GetNextKey())
    {
        const char* eventName = pEvent->GetName();

        if (!eventName || !*eventName)
            continue;

        g_EventIdToName[iCurrentId] = eventName;

        if (g_Blacklist.contains(eventName))
            g_BlacklistIds.insert(iCurrentId);

        // TOOLKIT_LOG(this, " %d -> %s\n", iCurrentId, eventName);

        iCurrentId++;
    }
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
