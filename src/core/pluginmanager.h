//
// Created by Michal Přikryl on 10.04.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once

#include <vector>
#include <string>
#include <memory>

#ifdef _WIN32
#include <Windows.h>
using LibHandle = HMODULE;
#else
#include <dlfcn.h>
using LibHandle = void*;
#endif

class IToolkitPlugin;
class IToolkitListener;

struct ToolkitPlugin
{
    int id;
    std::string path;
    LibHandle lib;
    IToolkitPlugin* api;
    std::vector<IToolkitListener*> listeners;
};

class PluginManager
{
public:
    bool IsPluginLoaded(const std::string& fullPath);

    bool LoadPlugin(const char* path, char* error, size_t maxlen);
    bool UnloadPlugin(int id);

    bool LoadMissing();

    bool LoadAll();
    void UnloadAll();

    void SetAllLoaded();
    void FireMetamodLoaded();

    void AddListener(IToolkitPlugin* plugin, IToolkitListener* listener);
public:
    void OnLevelInit(char const* pMapName, char const* pMapEntities, char const* pOldLevel, char const* pLandmarkName, bool loadGame, bool background);
    void OnLevelShutdown();
public:
    std::vector<std::unique_ptr<ToolkitPlugin>> m_plugins;
    int m_nextId = 1;
};

extern PluginManager pluginManager;