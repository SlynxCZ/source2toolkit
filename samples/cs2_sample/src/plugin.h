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

class SamplePlugin final : public IToolkitPlugin, public IToolkitListener
{
public:
	SamplePlugin();

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
	// KHook hooks only come down in their destructor, so they live behind plain
	// pointers: new in the constructor, delete in Unload().
	KHook::Virtual<ISource2Server, void, bool, bool, bool> *m_hGameFrame = nullptr;
	KHook::Virtual<ISource2GameClients, void, CPlayerSlot, bool, const char *, uint64> *m_hClientActive = nullptr;
	KHook::Virtual<ISource2GameClients, void, CPlayerSlot, ENetworkDisconnectionReason, const char *, uint64, const char *> *m_hClientDisconnect = nullptr;
	KHook::Virtual<ISource2GameClients, void, CPlayerSlot, char const *, int, uint64> *m_hClientPutInServer = nullptr;
	KHook::Virtual<ISource2GameClients, void, CPlayerSlot> *m_hClientSettingsChanged = nullptr;
	KHook::Virtual<ISource2GameClients, void, CPlayerSlot, const char *, uint64, const char *, const char *, bool> *m_hOnClientConnected = nullptr;
	KHook::Virtual<ISource2GameClients, bool, CPlayerSlot, const char *, uint64, const char *, bool, CBufferString *> *m_hClientConnect = nullptr;
	KHook::Virtual<ISource2GameClients, void, CPlayerSlot, const CCommand &> *m_hClientCommand = nullptr;
	// Functions found by signature rather than through a vtable.
	KHook::Member<CBaseEntity, int64_t, CTakeDamageInfo *, CTakeDamageResult *> *m_hTakeDamageOld = nullptr;
	KHook::Member<CCSPlayerPawn, void, double, float> *m_hPostThink = nullptr;

public:
	const char *GetAuthor() override { return PLUGIN_AUTHOR; }
	const char *GetName() override { return PLUGIN_DISPLAY_NAME; }
	const char *GetDescription() override { return PLUGIN_DESCRIPTION; }
	const char *GetVersion() override { return PLUGIN_FULL_VERSION; }
};

extern SamplePlugin g_Plugin;

TOOLKIT_GLOBALVARS();

#endif //_INCLUDE_SOURCE2TOOLKIT_SAMPLE_PLUGIN_H_
