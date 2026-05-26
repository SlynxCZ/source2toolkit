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

#include <vector>
#include <string>
#include <memory>

#include "source2toolkit/IToolkitApi.h"

class PluginApi : public IToolkitAPI
{
public:
    void Log(IToolkitPlugin *plugin, const char* msg, ...) override;
    void ConPrint(const char* msg) override;
    void ConPrintf(const char* fmt, ...) override;

    void AddListener(IToolkitPlugin *plugin, IToolkitListener *pListener) override;

    void* QueryInterface(CreateInterfaceFn fn, const char *iface, int min) override;
    void* InterfaceSearch(CreateInterfaceFn fn, const char *iface, int max, int *ret) override;
    int FormatIface(char iface[], size_t maxlength) override;

    CreateInterfaceFn GetEngineFactory(bool syn=true) override;
    CreateInterfaceFn GetPhysicsFactory(bool syn=true) override;
    CreateInterfaceFn GetFileSystemFactory(bool syn=true) override;
    CreateInterfaceFn GetServerFactory(bool syn=true) override;

    void* ToolkitFactory(const char *iface, int *ret, PluginId *id) override;
    void* MetaFactory(const char *iface, int *ret, PluginId *id) override;

    IToolkitAddresses* Addresses() override;
    IToolkitCommands* Commands() override;
    IToolkitConVars* ConVars() override;
    IToolkitEntities* Entities() override;
    IToolkitEvents* Events() override;
    IToolkitGameConfig* GameConfig() override;
    IToolkitMenus* Menus() override;
    IToolkitMySQL* MySQL() override;
    IToolkitScheduler* Scheduler() override;
    IToolkitTrace* Trace() override;

    IToolkitModule* LoadModule(const char* name) override;
    void FreeModule(IToolkitModule* module) override;

    IGameEventManager2* GetGameEventManager() override;
    CGlobalVars* GetGlobalVars() override;
    ICvar* GetCVar() override;
    ISource2Server* GetSource2Server() override;
    IVEngineServer* GetEngineServer() override;
    IGameEventSystem* GetGameEventSystem() override;
    INetworkMessages* GetNetworkMessages() override;
    INetworkServerService* GetNetworkServerService() override;
    CGameEntitySystem* GetEntitySystem() override;
    CSchemaSystem* GetSchemaSystem() override;
    const char* GetBaseDir() override;

    size_t Format(char *buffer, size_t maxlength, const char *format, ...) override;
    size_t FormatArgs(char *buffer, size_t maxlength, const char *format, va_list ap) override;
};

extern PluginApi pluginApi;