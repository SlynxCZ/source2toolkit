//
// Created by Michal Přikryl on 03.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "virtualhooks.h"
#include "shared.h"

#include <functional>

#include "source2toolkit/IToolkitCommands.h"
#include "source2toolkit/IToolkitPlugin.h"

class CCommand;
class CCommandContext;

namespace commands {
    struct CommandEntry
    {
        PluginId owner;
        CommandHandler handler;
        Mode mode;
    };

    inline CommandHandler WrapVoidHandler(const ChatHandler& fn)
    {
        return [fn](const CCommandContext& ctx, const CCommand& args, Mode mode) -> Action
        {
            fn(ctx, args, mode);
            return Action::Ignore;
        };
    }

    void InitCommands();
    void DestructCommands();

    void ConCommandRouter(const CCommandContext &ctx, const CCommand &args);
    Action DispatchConsoleListener(const CCommandContext &ctx, const CCommand &args, Mode mode);

    class CommandsManager : public IToolkitCommands
    {
    public:
        void RegChatListener(PluginId owner, const char* pchName, ChatHandler handler) override;
        void RegConCommand(PluginId owner, const char* pchName, ChatHandler handler) override;
        void RegConListener(PluginId owner, const char* pchName, CommandHandler handler, Mode mode) override;
    public:
        void RemoveAllForPlugin(PluginId id);
    };

    extern CommandsManager commandsManager;
}
