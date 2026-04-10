//
// Created by Michal Přikryl on 10.04.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
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
    IToolkitEntityIO* EntityIO() override;
    IToolkitEvents* Events() override;
    IToolkitGameConfig* GameConfig() override;
    IToolkitScheduler* Scheduler() override;
    IToolkitTrace* Trace() override;

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