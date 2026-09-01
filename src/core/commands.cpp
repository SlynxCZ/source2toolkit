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
#include "commands.h"

#include "menus.h"
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

    static void HandleToolkitCommand(const CCommandContext& ctx, const CCommand& args, bool post)
    {
        int argc = args.ArgC();

        if (argc < 2)
        {
            LOG_INFO("Source2Toolkit commands:");
            LOG_INFO("  toolkit list");
            LOG_INFO("  toolkit load <name>");
            LOG_INFO("  toolkit unload <id>");
            LOG_INFO("  toolkit info <id>");
            LOG_INFO("  toolkit refresh");
            LOG_INFO("  toolkit version");
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

                LOG_INFO("  [%d] %s (%s) by (%s)\n",
                    p->id,
                    api->GetName(),
                    api->GetVersion(),
                    api->GetAuthor());
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
                    LOG_INFO("  Name: %s", api->GetName());
                    LOG_INFO("  Version: %s", api->GetVersion());
                    LOG_INFO("  Author: %s", api->GetAuthor());
                    LOG_INFO("  Description: %s", api->GetDescription());
                    LOG_INFO("  Path: %s", p->path.c_str());
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
            LOG_INFO("  Version: %s", VERSION_STRING);
            LOG_INFO("  Build: %s", BUILD_TIMESTAMP);
        }

        else
        {
            LOG_WARN("Unknown command '%s'", cmd);
        }
    }

    static void HandleMenuCommand(const CCommandContext& ctx, const CCommand& args, bool post)
    {
        CCSPlayerController* player = CCSPlayerController::FromSlot(ctx.GetPlayerSlot().Get());
        if (!player || player->m_iConnected() != PlayerConnectedState::Connected)
            return;

        if (args.ArgC() < 1)
            return;

        const char* cmd = args.Arg(0);

        int key = atoi(cmd);
        if (key < 1 || key > 9)
            return;

        menus::menuManager.OnKeyPress(player, key);
    }

    void InitCommands()
    {
        commandsManager.RegisterConCommand(0, "source2toolkit", HandleToolkitCommand);
        commandsManager.RegisterConCommand(0, "source2t", HandleToolkitCommand);
        commandsManager.RegisterConCommand(0, "s2toolkit", HandleToolkitCommand);
        commandsManager.RegisterConCommand(0, "s2t", HandleToolkitCommand);
        commandsManager.RegisterConCommand(0, "stoolkit", HandleToolkitCommand);
        commandsManager.RegisterConCommand(0, "st", HandleToolkitCommand);
        commandsManager.RegisterConCommand(0, "toolkit", HandleToolkitCommand);

        commandsManager.RegisterConCommand(0, "1", HandleMenuCommand);
        commandsManager.RegisterConCommand(0, "2", HandleMenuCommand);
        commandsManager.RegisterConCommand(0, "3", HandleMenuCommand);
        commandsManager.RegisterConCommand(0, "4", HandleMenuCommand);
        commandsManager.RegisterConCommand(0, "5", HandleMenuCommand);
        commandsManager.RegisterConCommand(0, "6", HandleMenuCommand);
        commandsManager.RegisterConCommand(0, "7", HandleMenuCommand);
        commandsManager.RegisterConCommand(0, "8", HandleMenuCommand);
        commandsManager.RegisterConCommand(0, "9", HandleMenuCommand);
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

        (void) it->second(ctx, args, true);
    }

    META_RES DispatchConsoleListener(const CCommandContext &ctx, const CCommand &args, bool post) {
        std::string name = args.Arg(0);
        std::transform(name.begin(), name.end(), name.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

        auto it = consoleListeners.find(name);
        if (it == consoleListeners.end())
            return MRES_IGNORED;

        META_RES result = MRES_IGNORED;

        for (const auto &entry: it->second) {
            if (entry.post != post)
                continue;

            META_RES thisResult = entry.handler(ctx, args, post);

            if (thisResult == MRES_SUPERCEDE)
                return MRES_SUPERCEDE;

            if (thisResult == MRES_OVERRIDE && !post)
                return MRES_OVERRIDE;

            if (static_cast<int>(thisResult) > static_cast<int>(result))
                result = thisResult;
        }

        return result;
    }

    void CommandsManager::RegisterChatListener(PluginId owner, const char* pchName, ChatHandler handler) {
        CommandHandler nativeHandler = WrapVoidHandler(handler);

        RegisterConListener(owner, pchName, nativeHandler, false);
        RegisterConListener(owner, std::string("/" + std::string(pchName)).c_str(), nativeHandler, false);
        RegisterConListener(owner, std::string("!" + std::string(pchName)).c_str(), nativeHandler, false);
    }

    void CommandsManager::RegisterConCommand(PluginId owner, const char* pchName, ChatHandler handler) {
        CommandHandler nativeHandler = WrapVoidHandler(handler);

        if (g_pCVar && g_pCVar->FindConCommand(pchName).IsValidRef()) {
            FP_WARN("Command '{}' exists in engine, registering chat-only alias", pchName);
            RegisterConListener(owner, pchName, nativeHandler, false);
            RegisterConListener(owner, std::string("/" + std::string(pchName)).c_str(), nativeHandler, false);
            RegisterConListener(owner, std::string("!" + std::string(pchName)).c_str(), nativeHandler, false);
            return;
        }

        if (!registeredNames.contains(pchName)) {
            auto cmd = std::make_unique<ConCommand>(pchName, ConCommandRouter, ("Registered command: " + std::string(pchName)).c_str(), FCVAR_NONE);
            registeredCommands.push_back(std::move(cmd));
            registeredNames.insert(pchName);
        }

        std::string key = pchName;
        std::transform(key.begin(), key.end(), key.begin(), tolower);

        RegisterConListener(owner, pchName, nativeHandler, false);
        RegisterConListener(owner, std::string("/" + std::string(pchName)).c_str(), nativeHandler, false);
        RegisterConListener(owner, std::string("!" + std::string(pchName)).c_str(), nativeHandler, false);
    }

    void CommandsManager::RegisterConListener(PluginId owner, const char* pchName, CommandHandler handler, bool post) {
        consoleListeners[pchName].push_back({owner, handler, post});
    }

    void CommandsManager::UnregisterChatListener(PluginId owner, const char* pchName)
    {
        // RegisterChatListener registers three console listeners: the bare name
        // and the / and ! prefixed aliases. All three go together.
        UnregisterConListener(owner, pchName, false);
        UnregisterConListener(owner, std::string("/" + std::string(pchName)).c_str(), false);
        UnregisterConListener(owner, std::string("!" + std::string(pchName)).c_str(), false);
    }

    void CommandsManager::UnregisterConCommand(PluginId owner, const char* pchName)
    {
        UnregisterChatListener(owner, pchName);
    }

    void CommandsManager::UnregisterConListener(PluginId owner, const char* pchName, bool post)
    {
        auto it = consoleListeners.find(pchName);
        if (it == consoleListeners.end())
            return;

        std::erase_if(it->second, [owner, post](const CommandEntry& e)
        {
            return e.owner == owner && e.post == post;
        });

        if (it->second.empty())
            consoleListeners.erase(it);
    }

    void CommandsManager::RemoveAllForPlugin(PluginId id)
    {
        for (auto it = consoleListeners.begin(); it != consoleListeners.end(); )
        {
            auto& vec = it->second;

            std::erase_if(vec, [id](const CommandEntry& e)
            {
                return e.owner == id;
            });

            if (vec.empty())
                it = consoleListeners.erase(it);
            else
                ++it;
        }
    }

    void CommandsManager::UnlockConCommands()
    {
        if (shared::g_pCoreConfig->UnlockConCommands)
        {
            ConCommandData* data = g_pCVar->GetConCommandData(ConCommandRef());
            for (ConCommandRef ref = ConCommandRef((uint16)0); ref.GetRawData() != data; ref = ConCommandRef(ref.GetAccessIndex() + 1))
            {
                if (!ref.IsFlagSet(FCVAR_HIDDEN | FCVAR_DEVELOPMENTONLY)) continue;
                ref.RemoveFlags(FCVAR_HIDDEN | FCVAR_DEVELOPMENTONLY);
            }
        }
    }
}
