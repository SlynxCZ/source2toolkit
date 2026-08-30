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
#pragma once
// tier1/convar.h first: iloopmode.h (pulled in by igamesystem.h) uses
// CSplitScreenSlot in IGameSystem::HandleInputEvent without declaring it.
#include "tier1/convar.h"

#include "igameevents.h"
#include "igamesystem.h"
#include "eiface.h"
#include "entitysystem.h"

#include "dynlibutils/memaddr.hpp"

class IEntityInstance; // forward-declare global SDK interface (defined in IEntityInstance.h)

namespace virtualhooks {
    class Virtuals {
    public:
        void InitListeners();
        void DestructListeners();
    public:
        void Hook_GameFrame(bool simulating, bool bFirstTick, bool bLastTick);
        void Hook_StartupServer(const GameSessionConfiguration_t& config, ISource2WorldSession* pWorldSession, const char* pszMapName);
        void Hook_DispatchConCommand(ConCommandRef cmd, const CCommandContext& ctx, const CCommand& args);
        void Hook_ClientCommand(CPlayerSlot slot, const CCommand& args);
        void Hook_ClientSvcUserMessage(CPlayerSlot slot, int nType, uint32 nSize, const void* pBuffer);
        void Hook_GameServerSteamAPIActivated();
        void Hook_GameServerSteamAPIDeactivated();
        void Hook_PostEventAbstract(CSplitScreenSlot nSlot, bool bLocalOnly, int nClientCount, const uint64* clients, INetworkMessageInternal* pEvent, const CNetMessage* pData, unsigned long nSize, NetChannelBufType_t bufType);
        void Hook_OnServerGamePostSimulate(const EventServerGamePostSimulate_t* const pMsg);
        int  Hook_LoadEventsFromFile(const char* filename, bool bSearchAll);
        bool Hook_FireEvent(IGameEvent* event, bool bDontBroadcast);
        bool Hook_FireEventPost(IGameEvent* event, bool bDontBroadcast);
        bool Hook_SendNetMessage(const CNetMessage* pData, NetChannelBufType_t bufType);
    protected:
        int m_iGameFrameHookID = 0;
        int m_iStartupServerHookID = 0;
        int m_iDispatchConCommandHookID = 0;
        int m_iClientCommandHookID = 0;
        int m_iClientSvcUserMessageHookID = 0;
        int m_iSteamAPIActivatedHookID = 0;
        int m_iSteamAPIDeactivatedHookID = 0;
        int m_iPostEventAbstractHookID = 0;
        int m_iOnServerGamePostSimulateHookID = 0;
        int m_iLoadEventsFromFileHookID = 0;
        int m_iFireEventHookID = 0;
        int m_iFireEventPostHookID = 0;
        int m_iSendNetMessageHookID = 0;
    };

    class CEntityListener: public IEntityListener {
    public:
        void OnEntityCreated(CEntityInstance* pEntity) override;
        void OnEntitySpawned(CEntityInstance* pEntity) override;
        void OnEntityDeleted(CEntityInstance* pEntity) override;
        void OnEntityParentChanged(CEntityInstance* pEntity, CEntityInstance* pNewParent) override;
    };

    extern Virtuals virtuals;
    extern CEntityListener entityListener;
}
