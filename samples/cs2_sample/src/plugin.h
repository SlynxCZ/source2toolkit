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
#include "source2toolkit/IToolkitMemory.h"
#include "source2toolkit/IToolkitMenus.h"
#include "source2toolkit/IToolkitModule.h"
#include "source2toolkit/IToolkitMySQL.h"
#include "source2toolkit/IToolkitNetworkMessages.h"
#include "source2toolkit/IToolkitScheduler.h"
#include "source2toolkit/IToolkitTrace.h"

#include <igameevents.h>

// Generated from plugin-metadata.json by tools/version_gen.py -- the metadata
// below is not written twice.
#include "version_gen.h"

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
	void Hook_GameFrame(bool simulating, bool bFirstTick, bool bLastTick);
	void Hook_ClientActive(CPlayerSlot slot, bool bLoadGame, const char *pszName, uint64 xuid);
	void Hook_ClientDisconnect(CPlayerSlot slot, ENetworkDisconnectionReason reason, const char *pszName, uint64 xuid, const char *pszNetworkID);
	void Hook_ClientPutInServer(CPlayerSlot slot, char const *pszName, int type, uint64 xuid);
	void Hook_ClientSettingsChanged(CPlayerSlot slot);
	void Hook_OnClientConnected(CPlayerSlot slot, const char *pszName, uint64 xuid, const char *pszNetworkID, const char *pszAddress, bool bFakePlayer);
	bool Hook_ClientConnect(CPlayerSlot slot, const char *pszName, uint64 xuid, const char *pszNetworkID, bool unk1, CBufferString *pRejectReason);
	void Hook_ClientCommand(CPlayerSlot nSlot, const CCommand &cmd);

public:
	const char *GetAuthor() override { return PLUGIN_AUTHOR; }
	const char *GetName() override { return PLUGIN_DISPLAY_NAME; }
	const char *GetDescription() override { return PLUGIN_DESCRIPTION; }
	const char *GetVersion() override { return PLUGIN_FULL_VERSION; }
};

extern SamplePlugin g_Plugin;

TOOLKIT_GLOBALVARS();

#endif //_INCLUDE_SOURCE2TOOLKIT_SAMPLE_PLUGIN_H_
