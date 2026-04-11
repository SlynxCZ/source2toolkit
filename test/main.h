#ifndef SOURCE2TOOLKIT_TEST_LIBRARY_H
#define SOURCE2TOOLKIT_TEST_LIBRARY_H

#pragma once

#include "source2toolkit/IToolkitPlugin.h"

#include "eiface.h"
#include "khook.hpp"

class Plugin final : public IToolkitPlugin, IToolkitListener
{
public:
    Plugin();
public:
    bool Load(PluginId id, IToolkitAPI* api, char* error, size_t maxlen, bool late) override;
    bool Unload(char* error, size_t maxlen) override;
public:
    KHook::Return<void> Hook_GameFrame(IServerGameDLL* pThis, bool simulating, bool bFirstTick, bool bLastTick);
private:
    KHook::Virtual<IServerGameDLL, void, bool, bool, bool> m_GameFrame;
private:
    const char* GetAuthor() override;
    const char* GetName() override;
    const char* GetDescription() override;
    const char* GetVersion() override;
};

#endif //SOURCE2TOOLKIT_TEST_LIBRARY_H