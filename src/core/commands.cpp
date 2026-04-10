//
// Created by Michal Přikryl on 03.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "commands.h"

#include "pluginapi.h"
#include "pluginmanager.h"
#include "raytrace.h"
#include "shared.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerPawn.h"
#include "source2toolkit/IToolkitPlugin.h"
#include "utils/log.h"

#define VERSION_STRING SEMVER " @ " GITHUB_SHA
#define BUILD_TIMESTAMP __DATE__ " " __TIME__

namespace commands {
    static std::vector<std::unique_ptr<ConCommand> > registeredCommands;
    static std::unordered_map<std::string, std::vector<CommandEntry> > consoleListeners;
    static std::unordered_set<std::string> registeredNames;
    static std::unordered_map<std::string, CommandHandler> commandCallbacks;

    CommandsManager commandsManager;

    static void HandleToolkitCommand(const CCommandContext& ctx, const CCommand& args, Mode mode)
    {
        int argc = args.ArgC();

        if (argc < 2)
        {
            FP_INFO("Source2Toolkit commands:");
            FP_INFO("  toolkit list");
            FP_INFO("  toolkit load <name>");
            FP_INFO("  toolkit unload <id>");
            FP_INFO("  toolkit info <id>");
            FP_INFO("  toolkit refresh");
            FP_INFO("  toolkit version");
            return;
        }

        const char* cmd = args.Arg(1);

        if (strcmp(cmd, "list") == 0)
        {
            if (pluginManager.m_plugins.empty())
            {
                FP_INFO("No plugins loaded.");
                return;
            }

            FP_INFO("Listing {} plugin(s):", pluginManager.m_plugins.size());

            for (auto& p : pluginManager.m_plugins)
            {
                auto* api = p->api;

                FP_INFO("  [{}] {} ({})",
                    p->id,
                    api->GetName(),
                    api->GetVersion());
            }
        }

        else if (strcmp(cmd, "load") == 0)
        {
            if (argc < 3)
            {
                FP_ERROR("Usage: toolkit load <name>");
                return;
            }

            char err[256]{};

            if (!pluginManager.LoadPlugin(args.Arg(2), err, sizeof(err)))
            {
                FP_ERROR("Load failed: {}", err);
                return;
            }

            FP_INFO("Plugin '{}' loaded.", args.Arg(2));
        }

        else if (strcmp(cmd, "unload") == 0)
        {
            if (argc < 3)
            {
                FP_ERROR("Usage: toolkit unload <id>");
                return;
            }

            int id = atoi(args.Arg(2));

            if (id <= 0)
            {
                FP_ERROR("Invalid plugin id.");
                return;
            }

            if (!pluginManager.UnloadPlugin(id))
            {
                FP_ERROR("Plugin {} not found or failed to unload.", id);
                return;
            }

            FP_INFO("Plugin {} unloaded.", id);
        }

        else if (strcmp(cmd, "info") == 0)
        {
            if (argc < 3)
            {
                FP_ERROR("Usage: toolkit info <id>");
                return;
            }

            int id = atoi(args.Arg(2));

            for (auto& p : pluginManager.m_plugins)
            {
                if (p->id == id)
                {
                    auto* api = p->api;

                    FP_INFO("Plugin {} info:", id);
                    FP_INFO("  Name: {}", api->GetName());
                    FP_INFO("  Version: {}", api->GetVersion());
                    FP_INFO("  Author: {}", api->GetAuthor());
                    FP_INFO("  Description: {}", api->GetDescription());
                    FP_INFO("  Path: {}", p->path);

                    return;
                }
            }

            FP_ERROR("Plugin {} not found.", id);
        }

        else if (strcmp(cmd, "refresh") == 0)
        {
            FP_INFO("Refreshing plugins...");

            pluginManager.UnloadAll();
            pluginManager.LoadAll();

            FP_INFO("Plugins refreshed.");
        }

        else if (strcmp(cmd, "version") == 0)
        {
            FP_INFO("Source2Toolkit");
            FP_INFO("  Version: {}", VERSION_STRING);
            FP_INFO("  Build: {}", BUILD_TIMESTAMP);
        }

        else
        {
            FP_WARN("Unknown command '{}'", cmd);
        }
    }

    void InitCommands()
    {
        commandsManager.RegConCommand("source2toolkit", HandleToolkitCommand);
        commandsManager.RegConCommand("source2t", HandleToolkitCommand);
        commandsManager.RegConCommand("s2toolkit", HandleToolkitCommand);
        commandsManager.RegConCommand("s2t", HandleToolkitCommand);
        commandsManager.RegConCommand("stoolkit", HandleToolkitCommand);
        commandsManager.RegConCommand("st", HandleToolkitCommand);
        commandsManager.RegConCommand("toolkit", HandleToolkitCommand);
    }

    void DestructCommands()
    {
        registeredCommands.clear();
        consoleListeners.clear();
        registeredNames.clear();
        commandCallbacks.clear();
    }

    void ConCommandRouter(const CCommandContext &ctx, const CCommand &args) {
        if (args.ArgC() < 1)
            return;

        std::string name = args.Arg(0);
        auto it = commandCallbacks.find(name);
        if (it == commandCallbacks.end())
            return;

        (void) it->second(ctx, args, Mode::Post);
    }

    Action DispatchConsoleListener(const CCommandContext &ctx, const CCommand &args, Mode mode) {
        std::string name = args.Arg(0);
        std::transform(name.begin(), name.end(), name.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

        auto it = consoleListeners.find(name);
        if (it == consoleListeners.end())
            return Action::Ignore;

        Action result = Action::Ignore;

        for (const auto &entry: it->second) {
            if (entry.mode != mode)
                continue;

            Action thisResult = entry.handler(ctx, args, mode);

            if (thisResult == Action::Supersede)
                return Action::Supersede;

            if (thisResult == Action::Override && mode == Mode::Pre)
                return Action::Override;

            if (static_cast<int>(thisResult) > static_cast<int>(result))
                result = thisResult;
        }

        return result;
    }

    void CommandsManager::RegChatListener(const char* pchName, ChatHandler handler) {
        CommandHandler nativeHandler = WrapVoidHandler(handler);

        RegConListener(pchName, nativeHandler, Mode::Pre);
        RegConListener(std::string("/" + std::string(pchName)).c_str(), nativeHandler, Mode::Pre);
        RegConListener(std::string("!" + std::string(pchName)).c_str(), nativeHandler, Mode::Pre);
    }

    void CommandsManager::RegConCommand(const char* pchName, ChatHandler handler) {
        CommandHandler nativeHandler = WrapVoidHandler(handler);

        if (shared::g_pCVar && shared::g_pCVar->FindConCommand(pchName).IsValidRef()) {
            FP_WARN("Command '{}' exists in engine, registering chat-only alias", pchName);
            RegConListener(pchName, nativeHandler, Mode::Pre);
            RegConListener(std::string("/" + std::string(pchName)).c_str(), nativeHandler, Mode::Pre);
            RegConListener(std::string("!" + std::string(pchName)).c_str(), nativeHandler, Mode::Pre);
            return;
        }

        if (!registeredNames.contains(pchName)) {
            auto cmd = std::make_unique<ConCommand>(pchName, ConCommandRouter, ("Registered command: " + std::string(pchName)).c_str(), FCVAR_NONE);
            registeredCommands.push_back(std::move(cmd));
            registeredNames.insert(pchName);
        }

        RegConListener(pchName, nativeHandler, Mode::Pre);
        RegConListener(std::string("/" + std::string(pchName)).c_str(), nativeHandler, Mode::Pre);
        RegConListener(std::string("!" + std::string(pchName)).c_str(), nativeHandler, Mode::Pre);
    }

    void CommandsManager::RegConListener(const char* pchName, CommandHandler handler, Mode mode) {
        consoleListeners[pchName].push_back({handler, mode});
    }
}
