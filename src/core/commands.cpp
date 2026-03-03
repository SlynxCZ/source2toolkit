//
// Created by Michal Přikryl on 03.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "commands.h"

#include "shared.h"
#include "utils/log.h"

#include "khook.hpp"

namespace commands {
    static std::vector<std::unique_ptr<ConCommand> > registeredCommands;
    static std::unordered_map<std::string, std::vector<CommandEntry> > consoleListeners;
    static std::unordered_set<std::string> registeredNames;
    static std::unordered_map<std::string, CommandHandler> commandCallbacks;

    void ConCommandRouter(const CCommandContext &ctx, const CCommand &args) {
        if (args.ArgC() < 1)
            return;

        std::string name = args.Arg(0);
        auto it = commandCallbacks.find(name);
        if (it == commandCallbacks.end())
            return;

        (void) it->second(ctx, args, KHook::Mode::Post);
    }

    void RegisterChatListener(const std::string &name, ChatHandler &handler) {
        CommandHandler nativeHandler = WrapVoidHandler(handler);

        RegisterConsoleListener(name, nativeHandler, KHook::Mode::Pre);
        RegisterConsoleListener("/" + name, nativeHandler, KHook::Mode::Pre);
        RegisterConsoleListener("!" + name, nativeHandler, KHook::Mode::Pre);
    }

    void RegisterConsoleCommand(const std::string &name, ChatHandler &handler) {
        CommandHandler nativeHandler = WrapVoidHandler(handler);

        if (shared::g_pCVar && shared::g_pCVar->FindConCommand(name.c_str()).IsValidRef()) {
            FP_WARN("Command '{}' exists in engine, registering chat-only alias", name);
            RegisterConsoleListener(name, nativeHandler, KHook::Mode::Pre);
            RegisterConsoleListener("/" + name, nativeHandler, KHook::Mode::Pre);
            RegisterConsoleListener("!" + name, nativeHandler, KHook::Mode::Pre);
            return;
        }

        if (!registeredNames.contains(name)) {
            auto cmd = std::make_unique<ConCommand>(name.c_str(), ConCommandRouter, ("Registered command: " + name).c_str(), FCVAR_NONE);
            registeredCommands.push_back(std::move(cmd));
            registeredNames.insert(name);
        }

        RegisterConsoleListener(name, nativeHandler, KHook::Mode::Pre);
        RegisterConsoleListener("/" + name, nativeHandler, KHook::Mode::Pre);
        RegisterConsoleListener("!" + name, nativeHandler, KHook::Mode::Pre);
    }

    void RegisterConsoleListener(const std::string &name, CommandHandler handler, KHook::Mode mode) {
        consoleListeners[name].push_back({handler, mode});
    }
}
