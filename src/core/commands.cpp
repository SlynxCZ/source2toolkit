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

#define ANSI_RESET  "\033[0m"
#define ANSI_RED    "\033[31m"
#define ANSI_GREEN  "\033[32m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_BLUE   "\033[34m"

#define LOG_INFO(fmt, ...) \
ConMsg(ANSI_GREEN fmt ANSI_RESET "\n", ##__VA_ARGS__)

#define LOG_WARN(fmt, ...) \
ConMsg(ANSI_YELLOW fmt ANSI_RESET "\n", ##__VA_ARGS__)

#define LOG_ERROR(fmt, ...) \
ConMsg(ANSI_RED fmt ANSI_RESET "\n", ##__VA_ARGS__)

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
            LOG_INFO("Source2Toolkit commands:");
            LOG_INFO("  toolkit list\n");
            LOG_INFO("  toolkit load <name>\n");
            LOG_INFO("  toolkit unload <id>\n");
            LOG_INFO("  toolkit info <id>\n");
            LOG_INFO("  toolkit refresh\n");
            LOG_INFO("  toolkit version\n");
            return;
        }

        const char* cmd = args.Arg(1);

        if (strcmp(cmd, "list") == 0)
        {
            if (pluginManager.m_plugins.empty())
            {
                LOG_WARN("No plugins loaded.");
                return;
            }

            LOG_INFO("Listing %zu plugin(s):", pluginManager.m_plugins.size());

            for (auto& p : pluginManager.m_plugins)
            {
                auto* api = p->api;

                LOG_INFO("  [%d] %s (%s)\n",
                    p->id,
                    api->GetName(),
                    api->GetVersion());
            }
        }

        else if (strcmp(cmd, "load") == 0)
        {
            if (argc < 3)
            {
                LOG_ERROR("Usage: toolkit load <name>");
                return;
            }

            char err[256]{};

            if (!pluginManager.LoadPlugin(args.Arg(2), err, sizeof(err)))
            {
                LOG_ERROR("Load failed: %s", err);
                return;
            }

            LOG_INFO("Plugin '%s' loaded.", args.Arg(2));
        }

        else if (strcmp(cmd, "unload") == 0)
        {
            if (argc < 3)
            {
                LOG_ERROR("Usage: toolkit unload <id>");
                return;
            }

            int id = atoi(args.Arg(2));

            if (id <= 0)
            {
                LOG_ERROR("Invalid plugin id.");
                return;
            }

            if (!pluginManager.UnloadPlugin(id))
            {
                LOG_ERROR("Plugin %d not found or failed to unload.", id);
                return;
            }

            LOG_INFO("Plugin %d unloaded.", id);
        }

        else if (strcmp(cmd, "info") == 0)
        {
            if (argc < 3)
            {
                LOG_ERROR("Usage: toolkit info <id>");
                return;
            }

            int id = atoi(args.Arg(2));

            for (auto& p : pluginManager.m_plugins)
            {
                if (p->id == id)
                {
                    auto* api = p->api;

                    LOG_INFO("Plugin %d info:", id);
                    LOG_INFO("  Name: %s\n", api->GetName());
                    LOG_INFO("  Version: %s\n", api->GetVersion());
                    LOG_INFO("  Author: %s\n", api->GetAuthor());
                    LOG_INFO("  Description: %s\n", api->GetDescription());
                    LOG_INFO("  Path: %s\n", p->path.c_str());
                    return;
                }
            }

            LOG_ERROR("Plugin %d not found.", id);
        }

        else if (strcmp(cmd, "refresh") == 0)
        {
            LOG_INFO("Loading missing plugins...");

            pluginManager.LoadMissing();

            LOG_INFO("Done.");
        }

        else if (strcmp(cmd, "version") == 0)
        {
            LOG_INFO("Source2Toolkit");
            LOG_INFO("  Version: %s\n", VERSION_STRING);
            LOG_INFO("  Build: %s\n", BUILD_TIMESTAMP);
        }

        else
        {
            LOG_WARN("Unknown command '%s'", cmd);
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
