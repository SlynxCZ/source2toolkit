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
// CSplitScreenSlot in IGameSystem::HandleInputEvent without declaring it, and
// PostEventAbstract below needs the type too.
#include "tier1/convar.h"

#include "ISmmPlugin.h"
#include "igameevents.h"
#include "engine/igameeventsystem.h"
#include "source2toolkit/schema/serversideclient.h"
#include "igamesystem.h"
#include "eiface.h"
#include "entitysystem.h"

#include "dynlibutils/memaddr.hpp"

class IEntityInstance; // forward-declare global SDK interface (defined in IEntityInstance.h)

namespace virtualhooks {
    class Virtuals {
    public:
        Virtuals();

        void InitListeners();
        void DestructListeners();
    public:
        KHook::Return<void> Hook_GameFrame(IServerGameDLL* pThis, bool simulating, bool bFirstTick, bool bLastTick);
        KHook::Return<void> Hook_StartupServer(INetworkServerService* pThis, const GameSessionConfiguration_t &config, ISource2WorldSession *pWorldSession, const char *);
        KHook::Return<void> Hook_DispatchConCommand(ICvar* pThis, ConCommandRef cmd, const CCommandContext& ctx, const CCommand& args);
        KHook::Return<void> Hook_ClientCommand(IServerGameClients* pThis, CPlayerSlot slot, const CCommand& args);
        KHook::Return<void> Hook_OnServerGamePostSimulate(IGameSystem* pThis, const EventServerGamePostSimulate_t* const pMsg);
        KHook::Return<void> Hook_PostEventAbstract(IGameEventSystem* pThis, CSplitScreenSlot nSlot, bool bLocalOnly, int nClientCount, const uint64* clients, INetworkMessageInternal* pEvent, const CNetMessage* pData, unsigned long nSize, NetChannelBufType_t bufType);
        KHook::Return<bool> Hook_SendNetMessage(CServerSideClientBase* pThis, const CNetMessage* pData, NetChannelBufType_t bufType);
        KHook::Return<int> Hook_LoadEventsFromFile(IGameEventManager2* pThis, const char *filename, bool bSearchAll);
        KHook::Return<bool> Hook_FireEvent(IGameEventManager2* pThis, IGameEvent *event, bool bDontBroadcast);
        KHook::Return<bool> Hook_FireEventPost(IGameEventManager2* pThis, IGameEvent *event, bool bDontBroadcast);
    protected:
        KHook::Virtual<IServerGameDLL, void, bool, bool, bool>* m_pGameFrame;
        KHook::Virtual<ICvar, void, ConCommandRef, const CCommandContext&, const CCommand&>* m_pDispatchConCommand;
        KHook::Virtual<IServerGameClients, void, CPlayerSlot, const CCommand&>* m_pClientCommand;
        KHook::Virtual<INetworkServerService, void, const GameSessionConfiguration_t&, ISource2WorldSession*, const char*>* m_pStartupServer;
        KHook::Virtual<IGameSystem, void, const EventServerGamePostSimulate_t*>* m_pOnServerGamePostSimulate;
        KHook::Virtual<IGameEventManager2, int, const char*, bool>* m_pLoadEventsFromFile;
        KHook::Virtual<IGameEventManager2, bool, IGameEvent*, bool>* m_pFireEvent;
        KHook::Virtual<IGameEventSystem, void, CSplitScreenSlot, bool, int, const uint64*, INetworkMessageInternal*, const CNetMessage*, unsigned long, NetChannelBufType_t>* m_pPostEventAbstract;
        // SendNetMessage is declared on the base, so that is what the member
        // function pointer -- and therefore the hook -- is typed against.
        KHook::Virtual<CServerSideClientBase, bool, const CNetMessage*, NetChannelBufType_t>* m_pSendNetMessage;
    protected:
        IGameSystem* m_pCEntityDebugGameSystemVTable;
        IGameEventManager2* m_pCGameEventManagerVTable;
        CServerSideClientBase* m_pCServerSideClientVTable;
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
