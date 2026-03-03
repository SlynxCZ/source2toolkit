//
// Created by Michal Přikryl on 03.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "KHook/src/detour.hpp"

class CCommand;
class CCommandContext;

namespace commands {
    using ChatHandler = std::function<void(const CCommandContext&, const CCommand&, KHook::Mode)>;
    using CommandHandler = std::function<KHook::Action(const CCommandContext&, const CCommand&, KHook::Mode)>;

    struct CommandEntry
    {
        CommandHandler handler;
        KHook::Mode mode;
    };

    inline CommandHandler WrapVoidHandler(const ChatHandler& fn)
    {
        return [fn](const CCommandContext& ctx, const CCommand& args, KHook::Mode mode) -> KHook::Action
        {
            fn(ctx, args, mode);
            return KHook::Action::Ignore;
        };
    }

    void DestructCommands();

    void ConCommandRouter(const CCommandContext &ctx, const CCommand &args);
    KHook::Action DispatchConsoleListener(const CCommandContext &ctx, const CCommand &args, KHook::Mode mode);

    void RegChatListener(const std::string &name, ChatHandler &handler);
    void RegConCommand(const std::string &name, ChatHandler &handler);
    void RegConListener(const std::string &name, CommandHandler &handler, KHook::Mode mode);
}
