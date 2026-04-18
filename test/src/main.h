#ifndef SOURCE2TOOLKIT_TEST_LIBRARY_H
#define SOURCE2TOOLKIT_TEST_LIBRARY_H

#pragma once

#include "source2toolkit/IToolkitPlugin.h"

#include "eiface.h"
#include "khook.hpp"

class IGameEventManager2;
class CLCMsg_ListenEvents;
class CSource1LegacyGameEventGameSystem;

class Plugin final : public IToolkitPlugin, IToolkitListener
{
public:
    Plugin();
public:
    bool Load(PluginId id, IToolkitAPI* api, char* error, size_t maxlen, bool late) override;
    bool Unload(char* error, size_t maxlen) override;
public:
    KHook::Return<bool> Hook_ListenBitsReceived(CSource1LegacyGameEventGameSystem* pThis, CLCMsg_ListenEvents* pMsg);
protected:
    KHook::Function<bool, CSource1LegacyGameEventGameSystem*, CLCMsg_ListenEvents*> m_hListenBitsReceived;
protected:
    uintptr_t m_pListenBitsReceived;
public:
    void LoadBlacklist(const char* pchPath, const char* pchKVName);
    void LoadEventsFromFile(const char* pchPath, const char* pchKVName, int& iCurrentId);
private:
    const char* GetAuthor() override;
    const char* GetName() override;
    const char* GetDescription() override;
    const char* GetVersion() override;
};

extern Plugin g_Plugin;

#endif //SOURCE2TOOLKIT_TEST_LIBRARY_H