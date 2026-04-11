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

        const Color colInfo(80, 200, 120, 255);
        const Color colWarn(255, 200, 80, 255);
        const Color colError(255, 80, 80, 255);
        const Color colDefault(200, 200, 200, 255);

        if (argc < 2)
        {
            ConColorMsg(colInfo, "Source2Toolkit commands:\n");
            ConColorMsg(colDefault, "  toolkit list\n");
            ConColorMsg(colDefault, "  toolkit load <name>\n");
            ConColorMsg(colDefault, "  toolkit unload <id>\n");
            ConColorMsg(colDefault, "  toolkit info <id>\n");
            ConColorMsg(colDefault, "  toolkit refresh\n");
            ConColorMsg(colDefault, "  toolkit version\n");
            return;
        }

        const char* cmd = args.Arg(1);

        if (strcmp(cmd, "list") == 0)
        {
            if (pluginManager.m_plugins.empty())
            {
                ConColorMsg(colWarn, "No plugins loaded.\n");
                return;
            }

            ConColorMsg(colInfo, "Listing %zu plugin(s):\n", pluginManager.m_plugins.size());

            for (auto& p : pluginManager.m_plugins)
            {
                auto* api = p->api;

                ConColorMsg(colDefault, "  [%d] %s (%s)\n",
                    p->id,
                    api->GetName(),
                    api->GetVersion());
            }
        }

        else if (strcmp(cmd, "load") == 0)
        {
            if (argc < 3)
            {
                ConColorMsg(colError, "Usage: toolkit load <name>\n");
                return;
            }

            char err[256]{};

            if (!pluginManager.LoadPlugin(args.Arg(2), err, sizeof(err)))
            {
                ConColorMsg(colError, "Load failed: %s\n", err);
                return;
            }

            ConColorMsg(colInfo, "Plugin '%s' loaded.\n", args.Arg(2));
        }

        else if (strcmp(cmd, "unload") == 0)
        {
            if (argc < 3)
            {
                ConColorMsg(colError, "Usage: toolkit unload <id>\n");
                return;
            }

            int id = atoi(args.Arg(2));

            if (id <= 0)
            {
                ConColorMsg(colError, "Invalid plugin id.\n");
                return;
            }

            if (!pluginManager.UnloadPlugin(id))
            {
                ConColorMsg(colError, "Plugin %d not found or failed to unload.\n", id);
                return;
            }

            ConColorMsg(colInfo, "Plugin %d unloaded.\n", id);
        }

        else if (strcmp(cmd, "info") == 0)
        {
            if (argc < 3)
            {
                ConColorMsg(colError, "Usage: toolkit info <id>\n");
                return;
            }

            int id = atoi(args.Arg(2));

            for (auto& p : pluginManager.m_plugins)
            {
                if (p->id == id)
                {
                    auto* api = p->api;

                    ConColorMsg(colInfo, "Plugin %d info:\n", id);
                    ConColorMsg(colDefault, "  Name: %s\n", api->GetName());
                    ConColorMsg(colDefault, "  Version: %s\n", api->GetVersion());
                    ConColorMsg(colDefault, "  Author: %s\n", api->GetAuthor());
                    ConColorMsg(colDefault, "  Description: %s\n", api->GetDescription());
                    ConColorMsg(colDefault, "  Path: %s\n", p->path.c_str());

                    return;
                }
            }

            ConColorMsg(colError, "Plugin %d not found.\n", id);
        }

        else if (strcmp(cmd, "refresh") == 0)
        {
            ConColorMsg(colInfo, "Refreshing plugins...\n");

            pluginManager.UnloadAll();
            pluginManager.LoadAll();

            ConColorMsg(colInfo, "Plugins refreshed.\n");
        }

        else if (strcmp(cmd, "version") == 0)
        {
            ConColorMsg(colInfo, "Source2Toolkit\n");
            ConColorMsg(colDefault, "  Version: %s\n", VERSION_STRING);
            ConColorMsg(colDefault, "  Build: %s\n", BUILD_TIMESTAMP);
        }

        else
        {
            ConColorMsg(colWarn, "Unknown command '%s'\n", cmd);
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
