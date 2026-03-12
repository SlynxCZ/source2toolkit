//
// Created by Michal Přikryl on 12.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "CCSPlayerController.h"

#include "CCSPlayerPawn.h"
#include "core/addresses.h"
#include "core/shared.h"

#include "schema/entity.h"

#include "networksystem/inetworkmessages.h"
#include "usermessages.pb.h"

#include <netinet/in.h>

enum class HudDestination
{
    Notify = 1,
    Console = 2,
    Chat = 3,
    Center = 4,
    Alert = 6
};

static void ClientPrint(int slot, int hudDestination, const char* message)
{
    INetworkMessageInternal* pNetMsg = shared::g_pNetworkMessages->FindNetworkMessagePartial("TextMsg");
    auto data = pNetMsg->AllocateMessage()->ToPB<CUserMessageTextMsg>();

    data->set_dest(hudDestination);
    data->add_param(message);

    CPlayerBitVec recipients;
    recipients.Set(slot);

    shared::g_pGameEventSystem->PostEventAbstract(CSplitScreenSlot(-1), false, ABSOLUTE_PLAYER_LIMIT,
                                                reinterpret_cast<const uint64*>(recipients.Base()), pNetMsg, data, 0,
                                                NetChannelBufType_t::BUF_RELIABLE);

    delete data;
}

void CCSPlayerController::PrintToConsole(const char* pszMessage)
{
    std::string pszSanitizedMessage = fmt::format("{}\n\0", pszMessage);
    ClientPrint(GetSlot(), (int)HudDestination::Console, pszSanitizedMessage.c_str());
}

void CCSPlayerController::PrintToChat(const char* pszMessage)
{
    ClientPrint(GetSlot(), (int)HudDestination::Chat, pszMessage);
}

void CCSPlayerController::PrintToCenter(const char* pszMessage)
{
    ClientPrint(GetSlot(), (int)HudDestination::Center, pszMessage);
}

void CCSPlayerController::PrintToCenterAlert(const char* pszMessage)
{
    ClientPrint(GetSlot(), (int)HudDestination::Alert, pszMessage);
}

void CCSPlayerController::PrintToCenterHtml(const char* pszMessage, int iDuration)
{
    IGameEvent *event = shared::g_pGameEventManager->CreateEvent("show_survival_respawn_status", true);
    event->SetString("loc_token", pszMessage);
    event->SetInt("duration", iDuration);
    event->SetPlayer("userid", GetPlayerSlot());
    FireEventToClient(event);
}

void CCSPlayerController::Respawn()
{
    if (!m_hPlayerPawn()) return;

    // The Call To Arms update appears to have invalidated the need for CCSPlayerPawn_Respawn.
    SetPawn(m_hPlayerPawn());
    CALL_VIRTUAL(void, shared::g_pGameConfig->GetOffset("CCSPlayerController_Respawn"), this);
}

void CCSPlayerController::SwitchTeam(int nTeam)
{
    addresses::CCSPlayerController_SwitchTeam(this, static_cast<unsigned char>(nTeam));
}

void CCSPlayerController::ChangeTeam(int nTeam)
{
    CALL_VIRTUAL(void, shared::g_pGameConfig->GetOffset("CCSPlayerController_ChangeTeam"), this, nTeam);
}

int CCSPlayerController::GetUserID()
{
    return shared::g_pEngine->GetPlayerUserId(GetPlayerSlot()).Get();
}

CPlayerUserId CCSPlayerController::GetPlayerUserID()
{
    return shared::g_pEngine->GetPlayerUserId(GetPlayerSlot());
}

bool CCSPlayerController::IsBot()
{
    return (m_fFlags & FL_FAKECLIENT) != 0;
}

void CCSPlayerController::Disconnect(ENetworkDisconnectionReason eReason)
{
    shared::g_pEngine->DisconnectClient(GetSlot(), eReason);
}

void CCSPlayerController::ExecuteClientCommand(const char* pszCommand)
{
    shared::g_pEngine->ClientCommand(GetPlayerSlot(), pszCommand);
}

void CCSPlayerController::ExecuteClientCommandFromServer(const char* pszCommand)
{
    CCommand args;
    args.Tokenize(pszCommand);

    auto handle = shared::g_pCVar->FindConCommand(args.Arg(0));
    if (!handle.IsValidRef()) return;

    CCommandContext context(CommandTarget_t::CT_NO_TARGET, GetPlayerSlot());

    shared::g_pCVar->DispatchConCommand(handle, context, args);
}

int CCSPlayerController::GetSlot()
{
    return GetEntityIndex().Get() - 1;
}

CPlayerSlot CCSPlayerController::GetPlayerSlot()
{
    return CPlayerSlot(GetSlot());
}

const char* CCSPlayerController::GetIpAddress()
{
    static char buffer[64];

    if (const auto* netInfo = shared::g_pEngine->GetPlayerNetInfo(GetPlayerSlot()))
    {
        uint32_t ip = netInfo->GetRemoteAddress().GetIP();

        ip = ntohl(ip);

        std::snprintf(
            buffer,
            sizeof(buffer),
            "%u.%u.%u.%u",
            (ip >> 24) & 0xFF,
            (ip >> 16) & 0xFF,
            (ip >> 8) & 0xFF,
            (ip) & 0xFF
        );

        if (char* colon = std::strchr(buffer, ':'))
            *colon = '\0';

        return buffer;
    }

    return nullptr;
}

void CCSPlayerController::ReplicateConVar(const char* pszConVar, const char* pszValue)
{
    INetworkMessageInternal* pNetMsg = shared::g_pNetworkMessages->FindNetworkMessagePartial("SetConVar");
    auto msg = pNetMsg->AllocateMessage()->ToPB<CNETMsg_SetConVar>();

    CMsg_CVars_CVar* cvarMsg = msg->mutable_convars()->add_cvars();
    cvarMsg->set_name(pszConVar);
    cvarMsg->set_value(pszValue);

    CPlayerBitVec recipients;
    recipients.Set(GetSlot());

    shared::g_pGameEventSystem->PostEventAbstract(CSplitScreenSlot(-1), false, ABSOLUTE_PLAYER_LIMIT,
                                                reinterpret_cast<const uint64*>(recipients.Base()), pNetMsg, msg, 0,
                                                NetChannelBufType_t::BUF_RELIABLE);

    delete msg;
}

void CCSPlayerController::FireEventToClient(IGameEvent* pEvent)
{
    if (!pEvent) return;

    IGameEventListener2* pListener = addresses::CCSPlayerController_LegacyGameEventListener(GetPlayerSlot());
    if (!pListener) return;

    pListener->FireGameEvent(pEvent);
}