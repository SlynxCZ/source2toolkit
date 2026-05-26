#ifndef ISTEAMGAMECOORDINATOR_H
#define ISTEAMGAMECOORDINATOR_H
#ifdef _WIN32
#pragma once
#endif

#include "steam/steam_api_common.h"

#include "base_gcmessages.pb.h"
#include "cstrike15_gcmessages.pb.h"
#include "econ_gcmessages.pb.h"
#include "engine_gcmessages.pb.h"
#include "gcsdk_gcmessages.pb.h"
#include "gcsystemmsgs.pb.h"

#include "json.hpp"

#include <dbg.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <optional>
#include <string>
#include <vector>

#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)
#define VALVE_CALLBACK_PACK_SMALL
#else
#define VALVE_CALLBACK_PACK_LARGE
#endif

const uint32_t k_EMsgProtoBufFlag = 0x80000000;

enum EGCResults
{
	k_EGCResultOK             = 0,
	k_EGCResultNoMessage      = 1,
	k_EGCResultBufferTooSmall = 2,
	k_EGCResultNotLoggedOn    = 3,
	k_EGCResultInvalidMessage = 4,
};

#if defined(VALVE_CALLBACK_PACK_SMALL)
#pragma pack(push, 4)
#elif defined(VALVE_CALLBACK_PACK_LARGE)
#pragma pack(push, 8)
#else
#error "Unknown VALVE_CALLBACK_PACK
#endif

struct GCMessageAvailable_t
{
	enum
	{
		k_iCallback = k_iSteamGameCoordinatorCallbacks + 1
	};
	uint32_t m_nMessageSize;
};

#pragma pack(pop)

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
class ISteamGameCoordinator
{
public:
	virtual EGCResults SendMessage(uint32_t unMsgType, const void *pubData, uint32_t cubData)                        = 0;
	virtual bool       IsMessageAvailable(uint32_t *pcubMsgSize)                                                     = 0;
	virtual EGCResults RetrieveMessage(uint32_t *punMsgType, void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize) = 0;
};

#define STEAMGAMECOORDINATOR_INTERFACE_VERSION "SteamGameCoordinator001"

// Global interface accessor
extern ISteamGameCoordinator *SteamGameCoordinator();
STEAM_DEFINE_GAMESERVER_INTERFACE_ACCESSOR( ISteamGameCoordinator *, SteamGameCoordinator, STEAMGAMECOORDINATOR_INTERFACE_VERSION );

extern CCallbackBase* g_pGameCoordinatorMessageAvailableCallback;
extern CCallbackBase** g_ppGCCallbackCapture;
extern std::vector<std::pair<uint32_t, std::string>> g_vecGameCoordinatorPending;

template<typename T>
constexpr T byteswap(T value)
{
	static_assert(std::is_integral_v<T>);

	if constexpr (sizeof(T) == 1)
		return value;
	else if constexpr (sizeof(T) == 2)
		return static_cast<T>(__builtin_bswap16(value));
	else if constexpr (sizeof(T) == 4)
		return static_cast<T>(__builtin_bswap32(value));
	else if constexpr (sizeof(T) == 8)
		return static_cast<T>(__builtin_bswap64(value));
}

template<typename T>
inline T ForceEndian(T value, std::endian expected)
{
	if (expected == std::endian::native)
		return value;
	return byteswap(value);
}

template<uint32_t type, class proto>
inline std::optional<proto> CheckProtoAndRemoveHeader(uint32_t unMsgType, const void *pubData, uint32_t cubData, CMsgProtoBufHeader &headerMsg)
{
	if (!(unMsgType & k_EMsgProtoBufFlag))
		return std::nullopt;

	if ((unMsgType & ~k_EMsgProtoBufFlag) != type)
		return std::nullopt;

	// First 4 bytes are just unMsgType again
	const char *data         = reinterpret_cast<const char *>(pubData);
	uint32_t    headerLength = ForceEndian(*reinterpret_cast<const uint32_t *>((data + sizeof(uint32_t))), std::endian::little);
	const char *header       = data + sizeof(uint32_t) + sizeof(uint32_t);
	if (!headerMsg.ParseFromArray(header, headerLength))
		return std::nullopt;

	const char *body = data + sizeof(uint32_t) + sizeof(uint32_t) + headerLength;
	proto       msg;
	if (!msg.ParseFromArray(body, cubData - sizeof(uint32_t) - sizeof(uint32_t) - headerLength))
		return std::nullopt;
	return msg;
}

std::optional<std::pair<uint32_t, std::string>> CreateGCSendProto(uint32_t type, google::protobuf::Message &msg, CMsgProtoBufHeader &header);

std::optional<std::pair<uint32_t, std::string>> CreateGCSendProto(uint32_t type, google::protobuf::Message &msg);

#endif // ISTEAMGAMECOORDINATOR_H
