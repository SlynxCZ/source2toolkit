//====== Copyright Valve Corporation, All rights reserved. ====================
//
// Purpose:
//
//=============================================================================

#include "isteamgamecoordinator.h"

ISteamGameCoordinator *SteamGameCoordinator();

CCallbackBase* g_pGameCoordinatorMessageAvailableCallback = nullptr;
CCallbackBase** g_ppGCCallbackCapture = nullptr;
std::vector<std::pair<uint32_t, std::string>> g_vecGameCoordinatorPending;

std::optional<std::pair<uint32_t, std::string>> CreateGCSendProto(uint32_t type, google::protobuf::Message &msg, CMsgProtoBufHeader &header)
{
    // Type + HeaderLength + Header + Body
    std::string s(sizeof(uint32_t) + sizeof(uint32_t) + header.ByteSizeLong() + msg.ByteSizeLong(), '\0');
    *reinterpret_cast<uint32_t *>(s.data())                    = ForceEndian(type | k_EMsgProtoBufFlag, std::endian::little);
    *reinterpret_cast<uint32_t *>(s.data() + sizeof(uint32_t)) = header.ByteSizeLong();
    if (!header.SerializeToArray(s.data() + sizeof(uint32_t) + sizeof(uint32_t), header.ByteSizeLong()))
        return std::nullopt;
    if (!msg.SerializeToArray(s.data() + sizeof(uint32_t) + sizeof(uint32_t) + header.ByteSizeLong(), msg.ByteSizeLong()))
        return std::nullopt;
    return std::make_pair(type | k_EMsgProtoBufFlag, s);
}

std::optional<std::pair<uint32_t, std::string>> CreateGCSendProto(uint32_t type, google::protobuf::Message &msg)
{
    CMsgProtoBufHeader header;
    return CreateGCSendProto(type, msg, header);
}