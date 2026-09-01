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

#include <cstdarg>

#define VERSION_STRING SEMVER " @ " GITHUB_SHA
#define BUILD_TIMESTAMP __DATE__ " " __TIME__

#define ANSI_RESET  "\033[0m"
#define ANSI_RED    "\033[31m"
#define ANSI_GREEN  "\033[32m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_BLUE   "\033[34m"


// A "toolkit ..." typed in the server console has no player behind it and
// belongs in that console; typed by a client it has to go back to that
// client's console instead, which is what ClientPrintf is for. Colour is
// dropped on that path -- the escapes are a terminal thing and the game
// console would print them literally.
static void ToolkitReply(const CCommandContext& ctx, const char* pszColor, const char* fmt, ...)
{
    char buf[1024];

    va_list ap;
    va_start(ap, fmt);
    V_vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    if (const CPlayerSlot slot = ctx.GetPlayerSlot(); slot.IsValid() && g_pEngineServer)
    {
        char line[1088];
        V_snprintf(line, sizeof(line), "%s\n", buf);
        g_pEngineServer->ClientPrintf(slot, line);
        return;
    }

    ConMsg("%s%s" ANSI_RESET "\n", pszColor, buf);
}

#define REPLY_INFO(fmt, ...)  ToolkitReply(ctx, ANSI_GREEN,  fmt, ##__VA_ARGS__)
#define REPLY_WARN(fmt, ...)  ToolkitReply(ctx, ANSI_YELLOW, fmt, ##__VA_ARGS__)
#define REPLY_ERROR(fmt, ...) ToolkitReply(ctx, ANSI_RED,    fmt, ##__VA_ARGS__)

namespace commands {
    // Keyed by name and carrying the owner, so unloading a plugin can drop
    // the ConCommands it created. ConCommand registers itself with the engine
    // in its constructor and unregisters in its destructor, so erasing the
    // entry is what takes the command back out.
    struct RegisteredCommand
    {
        PluginId owner;
        std::unique_ptr<ConCommand> cmd;
    };

    static std::unordered_map<std::string, RegisteredCommand> registeredCommands;
    static std::unordered_map<std::string, std::vector<CommandEntry> > consoleListeners;

    CommandsManager commandsManager;

    static void HandleToolkitCommand(const CCommandContext& ctx, const CCommand& args, bool post)
    {
        int argc = args.ArgC();

        if (argc < 2)
        {
            REPLY_INFO("Source2Toolkit commands:");
            REPLY_INFO("  toolkit list");
            REPLY_INFO("  toolkit load <name>");
            REPLY_INFO("  toolkit unload <id>");
            REPLY_INFO("  toolkit info <id>");
            REPLY_INFO("  toolkit refresh");
            REPLY_INFO("  toolkit version");
            return;
        }

        const char* cmd = args.Arg(1);

        if (strcmp(cmd, "list") == 0)
        {
            if (pluginManager.m_plugins.empty())
            {
                REPLY_WARN("No plugins loaded.");
                return;
            }

            REPLY_INFO("Listing %zu plugin(s):", pluginManager.m_plugins.size());

            for (auto& p : pluginManager.m_plugins)
            {
                auto* api = p->api;

                REPLY_INFO("  [%d] %s (%s) by (%s)",
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
                REPLY_ERROR("Usage: toolkit load <name>");
                return;
            }

            char err[256]{};

            if (!pluginManager.LoadPlugin(args.Arg(2), err, sizeof(err)))
            {
                REPLY_ERROR("Load failed: %s", err);
                return;
            }

            REPLY_INFO("Plugin '%s' loaded.", args.Arg(2));
        }

        else if (strcmp(cmd, "unload") == 0)
        {
            if (argc < 3)
            {
                REPLY_ERROR("Usage: toolkit unload <id>");
                return;
            }

            int id = atoi(args.Arg(2));

            if (id <= 0)
            {
                REPLY_ERROR("Invalid plugin id.");
                return;
            }

            if (!pluginManager.UnloadPlugin(id))
            {
                REPLY_ERROR("Plugin %d not found or failed to unload.", id);
                return;
            }

            REPLY_INFO("Plugin %d unloaded.", id);
        }

        else if (strcmp(cmd, "info") == 0)
        {
            if (argc < 3)
            {
                REPLY_ERROR("Usage: toolkit info <id>");
                return;
            }

            int id = atoi(args.Arg(2));

            for (auto& p : pluginManager.m_plugins)
            {
                if (p->id == id)
                {
                    auto* api = p->api;

                    REPLY_INFO("Plugin %d info:", id);
                    REPLY_INFO("  Name: %s", api->GetName());
                    REPLY_INFO("  Version: %s", api->GetVersion());
                    REPLY_INFO("  Author: %s", api->GetAuthor());
                    REPLY_INFO("  Description: %s", api->GetDescription());
                    REPLY_INFO("  Path: %s", p->path.c_str());
                    return;
                }
            }

            REPLY_ERROR("Plugin %d not found.", id);
        }

        else if (strcmp(cmd, "refresh") == 0)
        {
            REPLY_INFO("Loading missing plugins...");

            pluginManager.LoadMissing();

            REPLY_INFO("Done.");
        }

        else if (strcmp(cmd, "version") == 0)
        {
            REPLY_INFO("Source2Toolkit");
            REPLY_INFO("  Version: %s", VERSION_STRING);
            REPLY_INFO("  Build: %s", BUILD_TIMESTAMP);
        }

        else
        {
            REPLY_WARN("Unknown command '%s'", cmd);
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
    }

    // The ConCommand exists so the engine knows the name; the handler is not
    // reached from here. Every console command, registered or not, goes
    // through DispatchConsoleListener off the DispatchConCommand and
    // ClientCommand hooks (virtualhooks.cpp), which is where a plugin's
    // handler is called. Dispatching here as well would run it twice.
    void ConCommandRouter(const CCommandContext &ctx, const CCommand &args) {
        (void) ctx;
        (void) args;
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


    // Takes a command name back out of the engine.
    //
    // ICvar offers no way to do this -- RegisterConCommand and
    // UnregisterConCommandCallbacks and nothing else -- so it goes through
    // CCvar's own layout, which hl2sdk carries reverse engineered in
    // public/icvar.h. FindConCommand() resolves a name through
    // m_ConCommandHashes (a name hash -> access index table), so dropping the
    // entry there frees the name; the ConCommandData in m_ConCommandList stays
    // behind, which is the class's own habit anyway -- it allocates those from
    // a bump buffer it never frees.
    //
    // The layout is reverse engineered, so it is checked against the public
    // API before anything is written: look the name up both ways and only
    // touch the table if the two agree on the access index. A mismatch means
    // this build's CCvar is not the one described here, and the caller falls
    // back to parking the command instead.
    static bool ReleaseConCommandName(const char* pchName)
    {
        if (!g_pCVar || !pchName || !*pchName)
            return false;

        const ConCommandRef ref = g_pCVar->FindConCommand(pchName, true);
        if (!ref.IsValidRef())
            return false;

        auto* pCvar = static_cast<CCvar*>(g_pCVar);
        auto& hashes = pCvar->m_ConCommandHashes;

        // The token is itself the hash the table is keyed by, so it is passed
        // explicitly -- CUtlHashtable's default functor has no overload for
        // CUtlStringToken.
        const CUtlStringToken token(pchName);
        const auto handle = hashes.Find(token, token.GetHashCode());

        if (handle == hashes.InvalidHandle())
        {
            FP_WARN("Could not release '{}': CCvar's command table does not look the way this build expects", pchName);
            return false;
        }

        if (hashes.Element(handle) != ref.GetAccessIndex())
        {
            FP_WARN("Could not release '{}': CCvar's command table disagrees with FindConCommand", pchName);
            return false;
        }

        return hashes.Remove(token, token.GetHashCode());
    }

    void CommandsManager::RegisterConCommand(PluginId owner, const char* pchName, ChatHandler handler) {
        CommandHandler nativeHandler = WrapVoidHandler(handler);

        // Already ours: the ConCommand is the toolkit's claim on the name and
        // outlives the plugin that asked for it. Unloading parks it (see
        // RemoveAllForPlugin); registering again brings the same one back
        // rather than fighting the engine for a name it will not give up.
        if (auto it = registeredCommands.find(pchName); it != registeredCommands.end())
        {
            if (it->second.cmd)
                it->second.cmd->RemoveFlags(FCVAR_DEFENSIVE | FCVAR_HIDDEN);

            it->second.owner = owner;
        }
        else
        {
            if (g_pCVar && g_pCVar->FindConCommand(pchName).IsValidRef())
            {
                // Somebody else's -- the engine's own, or another plugin's. The
                // name cannot be taken over, so the handler is reached through
                // the console listener instead.
                FP_WARN("Command '{}' already exists in the engine, registering a chat alias for it instead", pchName);
            }
            else
            {
                auto cmd = std::make_unique<ConCommand>(pchName, ConCommandRouter, ("Registered command: " + std::string(pchName)).c_str(), FCVAR_NONE);
                registeredCommands.emplace(pchName, RegisteredCommand{ owner, std::move(cmd) });
            }
        }

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
        // Give the names back, so another plugin -- or this one with a
        // ConCommand of its own -- can take them afterwards.
        std::erase_if(registeredCommands, [id](auto& kv)
        {
            if (kv.second.owner != id)
                return false;

            if (ReleaseConCommandName(kv.first.c_str()))
                return true;

            // The table did not look the way we expect, so the name cannot be
            // released on this build. Park the command instead: FCVAR_DEFENSIVE
            // is what FindConCommand() skips unless asked for it explicitly and
            // FCVAR_HIDDEN keeps it out of find and autocomplete, so it is gone
            // from everything except a fresh registration of the same name.
            // Keep the entry, so registering again revives it.
            if (kv.second.cmd)
                kv.second.cmd->AddFlags(FCVAR_DEFENSIVE | FCVAR_HIDDEN);

            return false;
        });

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
