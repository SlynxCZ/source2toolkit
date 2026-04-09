//
// Created by Michal Přikryl on 03.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "virtualhooks.h"
#include "shared.h"

#include <functional>

class CCommand;
class CCommandContext;

namespace commands {
    using ChatHandler = std::function<void(const CCommandContext&, const CCommand&, Mode)>;
    using CommandHandler = std::function<KHook::Action(const CCommandContext&, const CCommand&, Mode)>;

    struct CommandEntry
    {
        CommandHandler handler;
        Mode mode;
    };

    inline CommandHandler WrapVoidHandler(const ChatHandler& fn)
    {
        return [fn](const CCommandContext& ctx, const CCommand& args, Mode mode) -> KHook::Action
        {
            fn(ctx, args, mode);
            return KHook::Action::Ignore;
        };
    }

    void InitCommands();
    void DestructCommands();

    void ConCommandRouter(const CCommandContext &ctx, const CCommand &args);
    KHook::Action DispatchConsoleListener(const CCommandContext &ctx, const CCommand &args, Mode mode);

    void RegChatListener(const std::string &name, ChatHandler handler);
    void RegConCommand(const std::string &name, ChatHandler handler);
    void RegConListener(const std::string &name, CommandHandler handler, Mode mode);
}
