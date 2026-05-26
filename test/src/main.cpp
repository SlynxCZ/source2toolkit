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
#include "source2toolkit/utils/scheduler.h"

#include "source2toolkit/schema/schema.h"
#include "source2toolkit/schema/serversideclient.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController.h"

#include "steam/steam_api.h"
#include "steam/steam_gameserver.h"
#include "steam/steam_api_common.h"

#include "isteamgamecoordinator.h"

#include <cstring>
#include <bit>

#include "khook.hpp"
#include "eiface.h"
#include "igameeventsystem.h"
#include "schemasystem.h"
#include "interfaces/interfaces.h"
#include "networksystem/inetworkmessages.h"

TOOLKIT_EXPOSE(source2toolkit_test, g_Plugin);

Plugin g_Plugin;
IGameEventSystem* g_pGameEventSystem = nullptr;
void* g_pExportedSteamApi = nullptr;
CSteamGameServerAPIContext* g_pSteamAPI = nullptr;
ISteamGameCoordinator* g_pSteamGameCoordinator = nullptr;

Plugin::Plugin() :
    m_pGameServerSteamAPIActivated(new KHook::Virtual(&ISource2Server::GameServerSteamAPIActivated, this, &Plugin::CSource2Server_GameServerSteamAPIActivated, nullptr)),
    m_pSendMessage(new KHook::Virtual(&ISteamGameCoordinator::SendMessage, this, &Plugin::ISteamGameCoordinator_SendMessage, nullptr)),
    m_pIsMessageAvailable(new KHook::Virtual(&ISteamGameCoordinator::IsMessageAvailable, this, &Plugin::ISteamGameCoordinator_IsMessageAvailable, nullptr)),
    m_pRetrieveMessage(new KHook::Virtual(&ISteamGameCoordinator::RetrieveMessage, this, &Plugin::ISteamGameCoordinator_RetrieveMessage, nullptr)),
    m_pRunCallbacks(new KHook::Function(this, &Plugin::ISteamGameServer_RunCallbacks, nullptr)),
    m_pRegisterCallback(new KHook::Function(this, &Plugin::ISteamGameServer_RegisterCallback, nullptr)),
    m_pUnregisterCallback(new KHook::Function(this, &Plugin::ISteamGameServer_UnregisterCallback, nullptr))
{
    g_ppGameCoordinatorCallbackCapture = &g_pGameCoordinatorMessageAvailableCallback;
}

bool Plugin::Load(PluginId id, IToolkitAPI* api, char* error, size_t maxlen, bool late)
{
    TOOLKIT_SAVEVARS();

    GET_VALVE_IFACE_CURRENT(GetEngineFactory, g_pEngineServer, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
    GET_VALVE_IFACE_CURRENT(GetEngineFactory, g_pCVar, ICvar, CVAR_INTERFACE_VERSION);
    GET_VALVE_IFACE_CURRENT(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
    GET_VALVE_IFACE_CURRENT(GetFileSystemFactory, g_pFullFileSystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION);
    GET_VALVE_IFACE_ANY(GetServerFactory, g_pSource2Server, ISource2Server, INTERFACEVERSION_SERVERGAMEDLL);
    GET_VALVE_IFACE_ANY(GetServerFactory, g_pSource2GameClients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);
    GET_VALVE_IFACE_ANY(GetEngineFactory, g_pNetworkServerService, INetworkServerService, NETWORKSERVERSERVICE_INTERFACE_VERSION);
    GET_VALVE_IFACE_ANY(GetEngineFactory, g_pSchemaSystem, CSchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
    GET_VALVE_IFACE_ANY(GetEngineFactory, g_pGameEventSystem, IGameEventSystem, GAMEEVENTSYSTEM_INTERFACE_VERSION);
    GET_VALVE_IFACE_ANY(GetEngineFactory, g_pNetworkMessages, INetworkMessages, NETWORKMESSAGES_INTERFACE_VERSION);
    GET_VALVE_IFACE_ANY(GetServerFactory, g_pSource2GameEntities, ISource2GameEntities, SOURCE2GAMEENTITIES_INTERFACE_VERSION);

    api->AddListener(this, this);

    // Function hooks
    {
    	m_pGameServerSteamAPIActivated->Add(g_pSource2Server);

    	TOOLKIT_LOG(this, "pTier0=%p, pPlatDebugStringBuffered=%p\n", UTIL_GetModulePtr("tier0"), (void*)UTIL_GetFunctionByName(UTIL_GetModulePtr("tier0"), "Plat_DebugString_Buffered"));

    	g_pExportedSteamApi = UTIL_GetModulePtr("steam_api");
    	if (g_pExportedSteamApi)
    	{
    		auto pRunCallbacks = (void*)UTIL_GetFunctionByName(g_pExportedSteamApi, "SteamGameServer_RunCallbacks");
    		auto pRegisterCallback = (void*)UTIL_GetFunctionByName(g_pExportedSteamApi, "SteamAPI_RegisterCallback");
    		auto pUnregisterCallback = (void*)UTIL_GetFunctionByName(g_pExportedSteamApi, "SteamAPI_UnregisterCallback");
    		TOOLKIT_LOG(this, "pRunCallbacks=%p, pRegisterCallback=%p, pUnregisterCallback=%p\n", pRunCallbacks, pRegisterCallback, pUnregisterCallback);
    		m_pRunCallbacks->Configure(reinterpret_cast<void (*)()>(pRunCallbacks));
    		m_pRegisterCallback->Configure(reinterpret_cast<void (*)(CCallbackBase*, int)>(pRegisterCallback));
    		m_pUnregisterCallback->Configure(reinterpret_cast<void (*)(CCallbackBase*)>(pUnregisterCallback));
    	}

    	if (late)
    	{
    		g_pSteamGameCoordinator = SteamGameCoordinator();
    		if (g_pSteamGameCoordinator)
    		{
    			m_pSendMessage->Add(g_pSteamGameCoordinator);
    			m_pIsMessageAvailable->Add(g_pSteamGameCoordinator);
    			m_pRetrieveMessage->Add(g_pSteamGameCoordinator);
    		}
    	}
    }

    UTIL_RegConCommand("test", [this](const CCommandContext& ctx, const CCommand& cmd, Mode mode)
    {
        if (!g_pSteamGameCoordinator)
        {
            TOOLKIT_LOG(this, "test: GC není připraven\n");
            return;
        }

        // Testovací CMsgGCCStrike15_v2_MatchmakingGC2ClientReserve
        // Sem dej reálné hodnoty — toto je jen proof-of-concept
        CMsgGCCStrike15_v2_MatchmakingGC2ClientReserve body;
        body.set_serverid(0xDEADBEEFDEADBEEFULL);      // Steam ID serveru 2
        body.set_direct_udp_ip(0x7F000001);              // 127.0.0.1 jako uint32 BE
        body.set_direct_udp_port(27015);
        body.set_reservationid(12345678ULL);
        body.set_server_address("127.0.0.1:27015");

        CMsgProtoBufHeader hdr;
        // hdr.set_client_steam_id(targetSteamId); // SteamID klienta co chceme přesměrovat

        QueueGCMessage(k_EMsgGCCStrike15_v2_MatchmakingGC2ClientReserve, body, &hdr);
        TOOLKIT_LOG(this, "gc_test_redirect: zpráva zařazena do fronty (pending=%zu)\n", g_vecGameCoordinatorPending.size());
    });

    TOOLKIT_LOG(this, "Load( id=%d, api=%p, late=%d ) done\n", id, api, late);

    return true;
}

bool Plugin::Unload(char* error, size_t maxlen)
{
    m_pGameServerSteamAPIActivated->Remove(g_pSource2Server);
	m_pSendMessage->Remove(g_pSteamGameCoordinator);
	m_pIsMessageAvailable->Remove(g_pSteamGameCoordinator);
	m_pRetrieveMessage->Remove(g_pSteamGameCoordinator);

	delete m_pRunCallbacks;
	delete m_pRegisterCallback;
	delete m_pUnregisterCallback;

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
    TOOLKIT_LOG(this, "OnLevelInit( map=%s, old=%s, landmark=%s, loadGame=%d, background=%d )\n", mapName ? mapName : "nullptr", oldLevel ? oldLevel : "nullptr",landmarkName ? landmarkName : "nullptr", loadGame, background);
}

void Plugin::OnLevelShutdown()
{
    TOOLKIT_LOG(this, "OnLevelShutdown()\n");
}

std::optional<std::pair<uint32_t, std::string>> Plugin::CreateGCSendProto(uint32_t type, google::protobuf::Message& msg, CMsgProtoBufHeader* pHeader)
{
	CMsgProtoBufHeader defaultHdr;
	CMsgProtoBufHeader& hdr = pHeader ? *pHeader : defaultHdr;

	size_t hdrSize  = hdr.ByteSizeLong();
	size_t bodySize = msg.ByteSizeLong();
	std::string s(sizeof(uint32_t) * 2 + hdrSize + bodySize, '\0');

	*reinterpret_cast<uint32_t*>(s.data())                    = type | 0x80000000u;
	*reinterpret_cast<uint32_t*>(s.data() + sizeof(uint32_t)) = static_cast<uint32_t>(hdrSize);

	if (!hdr.SerializeToArray(s.data() + sizeof(uint32_t) * 2, static_cast<int>(hdrSize)))
		return std::nullopt;
	if (!msg.SerializeToArray(s.data() + sizeof(uint32_t) * 2 + hdrSize, static_cast<int>(bodySize)))
		return std::nullopt;

	return std::make_pair(type | 0x80000000u, std::move(s));
}

void Plugin::QueueGCMessage(uint32_t type, google::protobuf::Message& msg, CMsgProtoBufHeader* pHeader)
{
	if (auto send = CreateGCSendProto(type, msg, pHeader))
	{
		g_vecGameCoordinatorPending.push_back(std::move(send.value()));
		TriggerGCCallback();
	}
}

void Plugin::TriggerGCCallback()
{
	if (!g_pGameCoordinatorMessageAvailableCallback || g_vecGameCoordinatorPending.empty())
		return;

	GCMessageAvailable_t msg;
	msg.m_nMessageSize = static_cast<uint32>(g_vecGameCoordinatorPending.front().second.size());
	g_pGameCoordinatorMessageAvailableCallback->Run(&msg);
}

KHook::Return<void> Plugin::CSource2Server_GameServerSteamAPIActivated(ISource2Server* pThis)
{
    TOOLKIT_LOG(this, "CSource2Server_GameServerSteamAPIActivated( pThis=%p )\n", pThis);

    g_pSteamAPI = new CSteamGameServerAPIContext();
    g_pSteamAPI->Init();

	g_pSteamGameCoordinator = SteamGameCoordinator();
	TOOLKIT_LOG(this, "CSource2Server_GameServerSteamAPIActivated: g_pSteamAPI=%p, g_pExportedSteamApi=%p, g_pSteamGameCoordinator=%p\n", g_pSteamAPI, g_pExportedSteamApi, g_pSteamGameCoordinator);

	if (g_pSteamGameCoordinator)
	{
		m_pSendMessage->Add(g_pSteamGameCoordinator);
		m_pIsMessageAvailable->Add(g_pSteamGameCoordinator);
		m_pRetrieveMessage->Add(g_pSteamGameCoordinator);
	}

    return { KHook::Action::Ignore };
}

KHook::Return<void> Plugin::ISteamGameServer_RunCallbacks()
{
    TOOLKIT_LOG(this, "ISteamGameServer_RunCallbacks()\n");

    if (!g_vecGameCoordinatorPending.empty())
        TriggerGCCallback();

    return { KHook::Action::Ignore };
}

KHook::Return<void> Plugin::ISteamGameServer_RegisterCallback(CCallbackBase* pCallback, int iCallback)
{
	TOOLKIT_LOG(this, "ISteamGameServer_RegisterCallback( pCallback=%p, iCallback=%d )\n", pCallback, iCallback);

	if (iCallback == GCMessageAvailable_t::k_iCallback && g_ppGameCoordinatorCallbackCapture)
		*g_ppGameCoordinatorCallbackCapture = pCallback;

	return { KHook::Action::Ignore };
}

KHook::Return<void> Plugin::ISteamGameServer_UnregisterCallback(CCallbackBase* pCallback)
{
	TOOLKIT_LOG(this, "ISteamGameServer_UnregisterCallback( pCallback=%p )\n", pCallback);

	if (pCallback == *g_ppGameCoordinatorCallbackCapture)
		*g_ppGameCoordinatorCallbackCapture = nullptr;

	return { KHook::Action::Supersede };
}

KHook::Return<EGCResults> Plugin::ISteamGameCoordinator_SendMessage(ISteamGameCoordinator* pThis, uint32 unMsgType, const void* pubData, uint32 cubData)
{
    uint32 realType = unMsgType & ~0x80000000u;
    bool isProto    = (unMsgType & 0x80000000u) != 0;
    TOOLKIT_LOG(this, "ISteamGameCoordinator_SendMessage( type=%u (0x%X), proto=%d, size=%u )\n", realType, realType, isProto, cubData);

 //    CMsgProtoBufHeader header;
	// if (auto msg = CheckProtoAndRemoveHeader<k_EMsgServerToGCEnterMatchmaking, CMsgServerToGCEnterMatchmaking>(unMsgType, pubData, cubData, header))
	// {
	// 	Msg("CMsgServerToGCEnterMatchmaking (Header)\n{}\n(Body)\n{}", header.Utf8DebugString(), msg->Utf8DebugString());
 //
	// 	if (object_cache.sent_lobby)
	// 	{
	// 		for (int i = 0; i < 5; i++)
	// 			Msg("Received k_EMsgServerToGCEnterMatchmaking but lobby already sent prior");
	// 		return k_EGCResultOK;
	// 	}
	// 	object_cache.sent_lobby = true;
 //
	// 	if (!ParseMatchInformation())
	// 	{
	// 		// Already logged
	// 		return k_EGCResultOK;
	// 	}
 //
	// 	// Create an object cache on the server with our data
	// 	{
	// 		CMsgSOSingleObject msg;
	// 		msg.set_type_id(ObjectCache::Lobby);
	// 		msg.set_object_data(object_cache.lobby.SerializeAsString());
	// 		msg.set_version(GetRandom(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max()));
	// 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
	// 		{
	// 			owner->set_type(1);
	// 			owner->set_id(GetServerSteamID());
	// 		}
	// 		if (auto send = CreateGCSendProto(k_ESOMsg_Create, msg))
	// 			gc_custom_pending.push_back(send.value());
	// 	}
 //
	// 	{
	// 		CMsgSOSingleObject msg;
	// 		msg.set_type_id(ObjectCache::ServerStaticLobby);
	// 		msg.set_object_data(object_cache.static_lobby.SerializeAsString());
	// 		msg.set_version(GetRandom(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max()));
	// 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
	// 		{
	// 			owner->set_type(1);
	// 			owner->set_id(GetServerSteamID());
	// 		}
	// 		if (auto send = CreateGCSendProto(k_ESOMsg_Create, msg))
	// 			gc_custom_pending.push_back(send.value());
	// 	}
 //
	// 	{
	// 		CMsgSOSingleObject msg;
	// 		msg.set_type_id(ObjectCache::ServerDynamicLobby);
	// 		msg.set_object_data(object_cache.dynamic_lobby.SerializeAsString());
	// 		msg.set_version(GetRandom(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max()));
	// 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
	// 		{
	// 			owner->set_type(1);
	// 			owner->set_id(GetServerSteamID());
	// 		}
	// 		if (auto send = CreateGCSendProto(k_ESOMsg_Create, msg))
	// 			gc_custom_pending.push_back(send.value());
	// 	}
 //
	// 	return k_EGCResultOK;
	// }
	// else if (auto msg = CheckProtoAndRemoveHeader<k_EMsgServerToGCUpdateLobbyServerState, CMsgServerToGCUpdateLobbyServerState>(unMsgType, pubData, cubData, header))
	// {
	// 	MsgIf(wantsProtobufDebugLog, "CMsgServerToGCUpdateLobbyServerState (Header)\n{}\n(Body)\n{}", header.Utf8DebugString(), msg->Utf8DebugString());
 //
	// 	bool didUpdate = false;
	// 	if (msg->lobby_id() == object_cache.lobby.lobby_id())
	// 	{
	// 		if (msg->has_server_state())
	// 		{
	// 			object_cache.lobby.set_server_state(msg->server_state());
	// 			didUpdate = true;
	// 		}
	// 		if (msg->has_safe_to_abandon())
	// 		{
	// 			object_cache.lobby.set_safe_to_abandon(msg->safe_to_abandon());
	// 			didUpdate = true;
	// 		}
	// 	}
 //
	// 	// Update the cache
	// 	if (didUpdate)
	// 	{
	// 		CMsgSOSingleObject msg;
	// 		msg.set_type_id(ObjectCache::Lobby);
	// 		msg.set_object_data(object_cache.lobby.SerializeAsString());
	// 		msg.set_version(GetRandom(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max()));
	// 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
	// 		{
	// 			owner->set_type(1);
	// 			owner->set_id(GetServerSteamID());
	// 		}
	// 		if (auto send = CreateGCSendProto(k_ESOMsg_Update, msg))
	// 			gc_custom_pending.push_back(send.value());
	// 	}
 //
	// 	return k_EGCResultOK;
	// }
	// else if (auto msg = CheckProtoAndRemoveHeader<k_EMsgServerToGCMatchSignoutPermission, CMsgServerToGCMatchSignoutPermission>(unMsgType, pubData, cubData, header))
	// {
	// 	MsgIf(wantsProtobufDebugLog, "CMsgServerToGCMatchSignoutPermission (Header)\n{}\n(Body)\n{}", header.Utf8DebugString(), msg->Utf8DebugString());
 //
	// 	uint64_t jobid = header.job_id_source();
 //
	// 	// We just always say yes and request all data
	// 	{
	// 		CMsgProtoBufHeader header;
	// 		header.set_job_id_target(jobid);
 //
	// 		CMsgServerToGCMatchSignoutPermissionResponse msg;
	// 		msg.set_can_sign_out(true);
	// 		msg.add_requested_data(k_EServerSignoutData_Disconnections);
	// 		msg.add_requested_data(k_EServerSignoutData_AccountStatChanges);
	// 		msg.add_requested_data(k_EServerSignoutData_DetailedStats);
	// 		msg.add_requested_data(k_EServerSignoutData_ServerPerfStats);
	// 		msg.add_requested_data(k_EServerSignoutData_PerfData);
	// 		msg.add_requested_data(k_EServerSignoutData_PlayerChat);
	// 		msg.add_requested_data(k_EServerSignoutData_BookRewards);
	// 		msg.add_requested_data(k_EServerSignoutData_PenalizedPlayers);
	// 		if (auto send = CreateGCSendProto(k_EMsgServerToGCMatchSignoutPermissionResponse, msg, header))
	// 			gc_custom_pending.push_back(send.value());
	// 	}
 //
	// 	return k_EGCResultOK;
	// }
	// else if (auto msg = CheckProtoAndRemoveHeader<k_EMsgServerToGCMatchSignout, CMsgServerToGCMatchSignout>(unMsgType, pubData, cubData, header))
	// {
	// 	MsgIf(wantsProtobufDebugLog, "CMsgServerToGCMatchSignout (Header)\n{}\n(Body)\n{}", header.Utf8DebugString(), msg->Utf8DebugString());
 //
	// 	try
	// 	{
	// 		if (std::optional<nlohmann::json> json = MatchSignoutToFullJson(msg.value()))
	// 		{
	// 			std::ofstream f(GetMatchDirectory() / "result.json");
	// 			f << std::setw(4) << json.value();
	// 		}
	// 	}
	// 	catch (const std::exception &ex)
	// 	{
	// 		Msg("Failed to serialize convert 'CMsgServerToGCMatchSignout' to JSON and dump to file: {}, no match stats will be saved", ex.what());
	// 	}
	// 	catch (...)
	// 	{
	// 		Msg("Failed to serialize convert 'CMsgServerToGCMatchSignout' to JSON and dump to file, no match stats will be saved");
	// 	}
 //
	// 	uint64_t jobid = header.job_id_source();
 //
	// 	// Destroy the caches
	// 	{
	// 		CMsgSOSingleObject msg;
	// 		msg.set_type_id(ObjectCache::Lobby);
	// 		msg.set_object_data(object_cache.lobby.SerializeAsString());
	// 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
	// 		{
	// 			owner->set_type(1);
	// 			owner->set_id(GetServerSteamID());
	// 		}
	// 		if (auto send = CreateGCSendProto(k_ESOMsg_Destroy, msg))
	// 			gc_custom_pending.push_back(send.value());
	// 	}
 //
	// 	{
	// 		CMsgSOSingleObject msg;
	// 		msg.set_type_id(ObjectCache::ServerStaticLobby);
	// 		msg.set_object_data(object_cache.static_lobby.SerializeAsString());
	// 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
	// 		{
	// 			owner->set_type(1);
	// 			owner->set_id(GetServerSteamID());
	// 		}
	// 		if (auto send = CreateGCSendProto(k_ESOMsg_Destroy, msg))
	// 			gc_custom_pending.push_back(send.value());
	// 	}
 //
	// 	{
	// 		CMsgSOSingleObject msg;
	// 		msg.set_type_id(ObjectCache::ServerDynamicLobby);
	// 		msg.set_object_data(object_cache.dynamic_lobby.SerializeAsString());
	// 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
	// 		{
	// 			owner->set_type(1);
	// 			owner->set_id(GetServerSteamID());
	// 		}
	// 		if (auto send = CreateGCSendProto(k_ESOMsg_Destroy, msg))
	// 			gc_custom_pending.push_back(send.value());
	// 	}
 //
	// 	{
	// 		CMsgProtoBufHeader header;
	// 		header.set_job_id_target(jobid);
 //
	// 		CMsgServerToGCMatchSignoutResponse msg;
	// 		msg.set_result(CMsgServerToGCMatchSignoutResponse_ESignoutResult_k_ESignout_Success);
	// 		if (auto send = CreateGCSendProto(k_EMsgServerToGCMatchSignoutResponse, msg, header))
	// 			gc_custom_pending.push_back(send.value());
	// 	}
	// 	return k_EGCResultOK;
	// }
	// else if (auto msg = CheckProtoAndRemoveHeader<k_EMsgServerToGCAbandonMatch, CMsgServerToGCAbandonMatch>(unMsgType, pubData, cubData, header))
	// {
	// 	MsgIf(wantsProtobufDebugLog, "CMsgServerToGCAbandonMatch (Header)\n{}\n(Body)\n{}", header.Utf8DebugString(), msg->Utf8DebugString());
 //
	// 	uint64_t jobid = header.job_id_source();
 //
	// 	// Destroy the caches
	// 	{
	// 		CMsgSOSingleObject msg;
	// 		msg.set_type_id(ObjectCache::Lobby);
	// 		msg.set_object_data(object_cache.lobby.SerializeAsString());
	// 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
	// 		{
	// 			owner->set_type(1);
	// 			owner->set_id(GetServerSteamID());
	// 		}
	// 		if (auto send = CreateGCSendProto(k_ESOMsg_Destroy, msg))
	// 			gc_custom_pending.push_back(send.value());
	// 	}
 //
	// 	{
	// 		CMsgSOSingleObject msg;
	// 		msg.set_type_id(ObjectCache::ServerStaticLobby);
	// 		msg.set_object_data(object_cache.static_lobby.SerializeAsString());
	// 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
	// 		{
	// 			owner->set_type(1);
	// 			owner->set_id(GetServerSteamID());
	// 		}
	// 		if (auto send = CreateGCSendProto(k_ESOMsg_Destroy, msg))
	// 			gc_custom_pending.push_back(send.value());
	// 	}
 //
	// 	{
	// 		CMsgSOSingleObject msg;
	// 		msg.set_type_id(ObjectCache::ServerDynamicLobby);
	// 		msg.set_object_data(object_cache.dynamic_lobby.SerializeAsString());
	// 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
	// 		{
	// 			owner->set_type(1);
	// 			owner->set_id(GetServerSteamID());
	// 		}
	// 		if (auto send = CreateGCSendProto(k_ESOMsg_Destroy, msg))
	// 			gc_custom_pending.push_back(send.value());
	// 	}
 //
	// 	{
	// 		CMsgProtoBufHeader header;
	// 		header.set_job_id_target(jobid);
 //
	// 		CMsgServerToGCAbandonMatchResponse msg;
	// 		if (auto send = CreateGCSendProto(k_EMsgServerToGCAbandonMatchResponse, msg, header))
	// 			gc_custom_pending.push_back(send.value());
	// 	}
 //
	// 	return k_EGCResultOK;
	// }
	// else if (auto msg = CheckProtoAndRemoveHeader<k_EMsgServerToGCTestConnection, CMsgServerToGCTestConnection>(unMsgType, pubData, cubData, header))
	// {
	// 	MsgIf(wantsProtobufDebugLog, "CMsgServerToGCTestConnection (Header)\n{}\n(Body)\n{}", header.Utf8DebugString(), msg->Utf8DebugString());
 //
	// 	uint64_t jobid = header.job_id_source();
 //
	// 	{
	// 		CMsgProtoBufHeader header;
	// 		header.set_job_id_target(jobid);
 //
	// 		CMsgServerToGCTestConnectionResponse msg;
	// 		msg.set_state(object_cache.lobby.server_state());
	// 		msg.set_state(object_cache.lobby.lobby_id());
	// 		if (auto send = CreateGCSendProto(k_EMsgServerToGCTestConnectionResponse, msg, header))
	// 			gc_custom_pending.push_back(send.value());
	// 	}
 //
	// 	return k_EGCResultOK;
	// }
	// else if (auto msg = CheckProtoAndRemoveHeader<k_EMsgServerToGCUpdateMatchInfo, CMsgServerToGCUpdateMatchInfo>(unMsgType, pubData, cubData, header))
	// {
	// 	MsgIf(wantsProtobufDebugLog, "CMsgServerToGCUpdateMatchInfo (Header)\n{}\n(Body)\n{}", header.Utf8DebugString(), msg->Utf8DebugString());
	// 	return k_EGCResultOK;
	// }

	return { KHook::Action::Ignore, k_EGCResultOK };
}

KHook::Return<bool> Plugin::ISteamGameCoordinator_IsMessageAvailable(ISteamGameCoordinator* pThis, uint32* pcubMsgSize)
{
    TOOLKIT_LOG(this, "ISteamGameCoordinator_IsMessageAvailable( pThis=%p, pcubMsgSize=%p )\n", pThis, pcubMsgSize);

    if (!g_vecGameCoordinatorPending.empty())
    {
        if (pcubMsgSize)
            *pcubMsgSize = g_vecGameCoordinatorPending[0].second.size();
        return { KHook::Action::Override, true };
    }

    return { KHook::Action::Ignore, true };
}

KHook::Return<EGCResults> Plugin::ISteamGameCoordinator_RetrieveMessage(ISteamGameCoordinator* pThis, uint32* punMsgType, void* pubDest, uint32 cubDest, uint32* pcubMsgSize)
{
    TOOLKIT_LOG(this, "ISteamGameCoordinator_RetrieveMessage( pThis=%p, punMsgType=%p, pubDest=%p, cubDest=%d, pcubMsgSize=%p )\n", pThis, punMsgType, pubDest, cubDest, pcubMsgSize);

    if (!g_vecGameCoordinatorPending.empty())
    {
        if (punMsgType)
            *punMsgType = g_vecGameCoordinatorPending[0].first;
        if (pcubMsgSize)
            *pcubMsgSize = g_vecGameCoordinatorPending[0].second.size();
        if (cubDest < g_vecGameCoordinatorPending[0].second.size())
            return { KHook::Action::Override, k_EGCResultBufferTooSmall };

        std::memcpy(pubDest, g_vecGameCoordinatorPending[0].second.data(), g_vecGameCoordinatorPending[0].second.size());
        g_vecGameCoordinatorPending.erase(g_vecGameCoordinatorPending.begin());

        return { KHook::Action::Override, k_EGCResultOK };
    }

    return { KHook::Action::Ignore, k_EGCResultOK };
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
