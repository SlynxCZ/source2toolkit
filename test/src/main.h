#ifndef SOURCE2TOOLKIT_TEST_LIBRARY_H
#define SOURCE2TOOLKIT_TEST_LIBRARY_H

#pragma once

#include "source2toolkit/IToolkitPlugin.h"

#include "eiface.h"
#include "khook.hpp"

class Plugin final : public IToolkitPlugin, IToolkitListener
{
public:
    bool Load(PluginId id, IToolkitAPI* api, char* error, size_t maxlen, bool late) override;
    bool Unload(char* error, size_t maxlen) override;
public:
    void OnPluginLoad(PluginId id) override;
    void OnPluginUnload(PluginId id) override;
    void OnAllToolkitPluginsLoaded() override;
    void OnAllMetamodPluginsLoaded() override;
    void OnLevelInit(const char* mapName, const char* mapEntities, const char* oldLevel, const char* landmarkName, bool loadGame, bool background) override;
    void OnLevelShutdown() override;
private:
    const char* GetAuthor() override;
    const char* GetName() override;
    const char* GetDescription() override;
    const char* GetVersion() override;
};

extern Plugin g_Plugin;

#endif //SOURCE2TOOLKIT_TEST_LIBRARY_H