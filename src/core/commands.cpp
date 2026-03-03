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

    void InitCommands()
    {
        // Todo: shared API vtable
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

        (void) it->second(ctx, args, KHook::Mode::Post);
    }

    KHook::Action DispatchConsoleListener(const CCommandContext &ctx, const CCommand &args, KHook::Mode mode) {
        std::string name = args.Arg(0);
        std::transform(name.begin(), name.end(), name.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

        auto it = consoleListeners.find(name);
        if (it == consoleListeners.end())
            return KHook::Action::Ignore;

        KHook::Action result = KHook::Action::Ignore;

        for (const auto &entry: it->second) {
            if (entry.mode != mode)
                continue;

            KHook::Action thisResult = entry.handler(ctx, args, mode);

            if (thisResult == KHook::Action::Supersede)
                return KHook::Action::Supersede;

            if (thisResult == KHook::Action::Override && mode == KHook::Mode::Pre)
                return KHook::Action::Override;

            if (static_cast<int>(thisResult) > static_cast<int>(result))
                result = thisResult;
        }

        return result;
    }

    void RegChatListener(const std::string &name, ChatHandler &handler) {
        CommandHandler nativeHandler = WrapVoidHandler(handler);

        RegConListener(name, nativeHandler, KHook::Mode::Pre);
        RegConListener("/" + name, nativeHandler, KHook::Mode::Pre);
        RegConListener("!" + name, nativeHandler, KHook::Mode::Pre);
    }

    void RegConCommand(const std::string &name, ChatHandler &handler) {
        CommandHandler nativeHandler = WrapVoidHandler(handler);

        if (shared::g_pCVar && shared::g_pCVar->FindConCommand(name.c_str()).IsValidRef()) {
            FP_WARN("Command '{}' exists in engine, registering chat-only alias", name);
            RegConListener(name, nativeHandler, KHook::Mode::Pre);
            RegConListener("/" + name, nativeHandler, KHook::Mode::Pre);
            RegConListener("!" + name, nativeHandler, KHook::Mode::Pre);
            return;
        }

        if (!registeredNames.contains(name)) {
            auto cmd = std::make_unique<ConCommand>(name.c_str(), ConCommandRouter, ("Registered command: " + name).c_str(), FCVAR_NONE);
            registeredCommands.push_back(std::move(cmd));
            registeredNames.insert(name);
        }

        RegConListener(name, nativeHandler, KHook::Mode::Pre);
        RegConListener("/" + name, nativeHandler, KHook::Mode::Pre);
        RegConListener("!" + name, nativeHandler, KHook::Mode::Pre);
    }

    void RegConListener(const std::string &name, CommandHandler handler, KHook::Mode mode) {
        consoleListeners[name].push_back({handler, mode});
    }
}
