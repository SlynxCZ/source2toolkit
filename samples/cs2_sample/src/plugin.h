/**
 * vim: set ts=4 sw=4 tw=99 noet :
 * ======================================================
 * Source2Toolkit Sample Plugin
 * ======================================================
 *
 * A port of Metamod:Source's own s2_sample_mm, doing the same things through
 * Source2Toolkit instead: the same hooks, the same convars, the same command,
 * the same level callbacks.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * This sample plugin is public domain.
 */

#ifndef _INCLUDE_SOURCE2TOOLKIT_SAMPLE_PLUGIN_H_
#define _INCLUDE_SOURCE2TOOLKIT_SAMPLE_PLUGIN_H_

#include "source2toolkit/IToolkitPlugin.h"
#include "source2toolkit/IToolkitApi.h"

// TOOLKIT_SAVEVARS() fills one global per subsystem, so every subsystem header
// has to be in scope for its interface name.
#include "source2toolkit/IToolkitAddresses.h"
#include "source2toolkit/IToolkitCommands.h"
#include "source2toolkit/IToolkitConVars.h"
#include "source2toolkit/IToolkitCustomHud.h"
#include "source2toolkit/IToolkitEntities.h"
#include "source2toolkit/IToolkitEvents.h"
#include "source2toolkit/IToolkitGameConfig.h"
#include "source2toolkit/IToolkitGameSystems.h"
#include "source2toolkit/IToolkitHTTP.h"
#include "source2toolkit/IToolkitJSON.h"
#include "source2toolkit/IToolkitMemory.h"
#include "source2toolkit/IToolkitMenus.h"
#include "source2toolkit/IToolkitModule.h"
#include "source2toolkit/IToolkitMySQL.h"
#include "source2toolkit/IToolkitNetworkMessages.h"
#include "source2toolkit/IToolkitScheduler.h"
#include "source2toolkit/IToolkitTrace.h"

#include "source2toolkit/schema/entity/classes/CBaseEntity.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerPawn.h"
#include "source2toolkit/schema/takedamageinfo.h"
#include "source2toolkit/schema/takedamageresult.h"
#include "igameevents.h"
#include "eiface.h"

// Generated from plugin-metadata.json by tools/version_gen.py -- the metadata
// below is not written twice.
#include "version_gen.h"

// Above the class: the hook targets below read g_pSource2Server and
// g_pToolkitAddresses, so the globals have to be declared first.
TOOLKIT_GLOBALVARS();

class SamplePlugin final : public IToolkitPlugin, public IToolkitListener
{
public:
	bool Load(PluginId id, IToolkitAPI *api, char *error, size_t maxlen, bool late) override;
	bool Unload(char *error, size_t maxlen) override;

public: // listener
	void OnAllToolkitPluginsLoaded() override;
	void OnLevelInit(const char *pMapName, const char *pMapEntities, const char *pOldLevel, const char *pLandmarkName, bool loadGame, bool background) override;
	void OnLevelShutdown() override;

public: // hooks
	KHook::Return<void> Hook_GameFrame(ISource2Server *pThis, bool simulating, bool bFirstTick, bool bLastTick);
	KHook::Return<void> Hook_ClientActive(ISource2GameClients *pThis, CPlayerSlot slot, bool bLoadGame, const char *pszName, uint64 xuid);
	KHook::Return<void> Hook_ClientDisconnect(ISource2GameClients *pThis, CPlayerSlot slot, ENetworkDisconnectionReason reason, const char *pszName, uint64 xuid, const char *pszNetworkID);
	KHook::Return<void> Hook_ClientPutInServer(ISource2GameClients *pThis, CPlayerSlot slot, char const *pszName, int type, uint64 xuid);
	KHook::Return<void> Hook_ClientSettingsChanged(ISource2GameClients *pThis, CPlayerSlot slot);
	KHook::Return<void> Hook_OnClientConnected(ISource2GameClients *pThis, CPlayerSlot slot, const char *pszName, uint64 xuid, const char *pszNetworkID, const char *pszAddress, bool bFakePlayer);
	KHook::Return<bool> Hook_ClientConnect(ISource2GameClients *pThis, CPlayerSlot slot, const char *pszName, uint64 xuid, const char *pszNetworkID, bool unk1, CBufferString *pRejectReason);
	KHook::Return<void> Hook_ClientCommand(ISource2GameClients *pThis, CPlayerSlot nSlot, const CCommand &cmd);
	KHook::Return<int64_t> Hook_TakeDamageOld(CBaseEntity *pThis, CTakeDamageInfo *pInfo, CTakeDamageResult *pResult);
	KHook::Return<void> Hook_PostThink(CCSPlayerPawn *pThis, double flFrameTime, float flUnknown);

private:
	// The hooks are KHook objects -- metamod's detour library, on the one engine
	// the toolkit shares with metamod (TOOLKIT_SAVEVARS() fetched it), so they
	// land next to every other plugin's hooks and can call through their
	// originals. Each holds the function it hooks, the context (this) and the
	// Pre/Post callbacks (Pre runs before the original, Post after; nullptr
	// leaves a side empty).
	//
	// One line each: the macro takes the hook's type from the handler it names
	// (which is why the handlers above come first), KHOOK_INIT() in Load()
	// resolves the target and installs it, KHOOK_DESTRUCT() in Unload() takes it
	// down. A handler that needs the real original from the middle of its body
	// calls m_hXxx->CallOriginal(pThis, ...).
	//
	// Virtual hooks go onto the engine's own interface instances. The pointer is
	// read at KHOOK_INIT(), not here -- it is still null when this object is
	// constructed.
	KHOOK_VIRTUAL(m_hGameFrame, &ISource2Server::GameFrame, &g_pSource2Server, nullptr, &SamplePlugin::Hook_GameFrame);
	KHOOK_VIRTUAL(m_hClientActive, &ISource2GameClients::ClientActive, &g_pSource2GameClients, nullptr, &SamplePlugin::Hook_ClientActive);
	KHOOK_VIRTUAL(m_hClientDisconnect, &ISource2GameClients::ClientDisconnect, &g_pSource2GameClients, nullptr, &SamplePlugin::Hook_ClientDisconnect);
	KHOOK_VIRTUAL(m_hClientPutInServer, &ISource2GameClients::ClientPutInServer, &g_pSource2GameClients, nullptr, &SamplePlugin::Hook_ClientPutInServer);
	KHOOK_VIRTUAL(m_hClientSettingsChanged, &ISource2GameClients::ClientSettingsChanged, &g_pSource2GameClients, &SamplePlugin::Hook_ClientSettingsChanged, nullptr);
	KHOOK_VIRTUAL(m_hOnClientConnected, &ISource2GameClients::OnClientConnected, &g_pSource2GameClients, &SamplePlugin::Hook_OnClientConnected, nullptr);
	KHOOK_VIRTUAL(m_hClientConnect, &ISource2GameClients::ClientConnect, &g_pSource2GameClients, &SamplePlugin::Hook_ClientConnect, nullptr);
	KHOOK_VIRTUAL(m_hClientCommand, &ISource2GameClients::ClientCommand, &g_pSource2GameClients, &SamplePlugin::Hook_ClientCommand, nullptr);

	// Functions found by signature rather than through a vtable, each showing a
	// different way to get the address.
	//
	// First: the toolkit already resolved this one, so just ask for it. Every
	// entry in IToolkitAddresses works this way and costs no scan of your own.
	// The lambda runs at KHOOK_INIT(), once the toolkit's interfaces are there.
	KHOOK_MEMBER(m_hTakeDamageOld, [] { return ADDR_TAKE_DAMAGE_OLD(); }, &SamplePlugin::Hook_TakeDamageOld, nullptr);
	// Second: anything in the shared gamedata, whether or not the toolkit has a
	// typed getter for it. The entry's library is read, then it is found by
	// exported symbol or by pattern -- you do not care which.
	KHOOK_MEMBER(m_hPostThink, "CCSPlayerPawn::PostThink", &SamplePlugin::Hook_PostThink, nullptr);

public:
	const char *GetAuthor() override { return PLUGIN_AUTHOR; }
	const char *GetName() override { return PLUGIN_DISPLAY_NAME; }
	const char *GetDescription() override { return PLUGIN_DESCRIPTION; }
	const char *GetVersion() override { return PLUGIN_FULL_VERSION; }
};

extern SamplePlugin g_Plugin;

#endif //_INCLUDE_SOURCE2TOOLKIT_SAMPLE_PLUGIN_H_
