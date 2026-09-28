/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
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
 * As a special exception, Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl and
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
 *   - Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl
 *   - AlliedModders LLC
 *
 * Project: Source2Toolkit
 */
#pragma once

#include <memory>
#include <vector>

#include "source2toolkit/IToolkitGameHooks.h"

namespace gamehooks
{
    // One hooked game function: its listeners and, while it has any, its
    // detour. The concrete kinds are in gamehooks.cpp.
    class IGameHook
    {
    public:
        virtual ~IGameHook() = default;

        virtual const char* Name() const = 0;
        virtual bool IsAvailable() = 0;
        virtual void Remove(PluginId owner, bool post) = 0;
        virtual void RemoveAll(PluginId owner) = 0;
        virtual bool Empty() const = 0;
        virtual void Uninstall() = 0;
    };

    class GameHooksManager final : public IToolkitGameHooks
    {
    public:
        GameHooksManager();
        ~GameHooksManager() override;

        /// Takes every detour out, synchronously. Called from Unload(), where
        /// none of the hooked functions is on the stack.
        void Shutdown();

        /// Once a frame: a hook whose last listener left is taken out here,
        /// never from inside its own dispatch.
        void Tick();

        void RemoveAllForPlugin(PluginId id);

        void HookTakeDamage(PluginId owner, GameHookHandler<TakeDamageContext> handler, bool post) override;
        void HookCanAcquire(PluginId owner, GameHookHandler<CanAcquireContext> handler, bool post) override;
        void HookCanMove(PluginId owner, GameHookHandler<CanMoveContext> handler, bool post) override;
        void HookCanUse(PluginId owner, GameHookHandler<CanUseContext> handler, bool post) override;
        void HookPostThink(PluginId owner, GameHookHandler<PostThinkContext> handler, bool post) override;
        void HookProcessUsercmds(PluginId owner, GameHookHandler<ProcessUsercmdsContext> handler, bool post) override;
        void HookSimulateUserCommands(PluginId owner, GameHookHandler<SimulateUserCommandsContext> handler, bool post) override;
        void HookRunCommand(PluginId owner, GameHookHandler<RunCommandContext> handler, bool post) override;
        void HookAcceptInput(PluginId owner, GameHookHandler<AcceptInputContext> handler, bool post) override;
        void HookTouch(PluginId owner, GameHookHandler<TouchContext> handler, bool post) override;
        void HookDropWeapon(PluginId owner, GameHookHandler<DropWeaponContext> handler, bool post) override;
        void HookAirAccelerate(PluginId owner, GameHookHandler<AirAccelerateContext> handler, bool post) override;
        void HookAirMove(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        void HookCanUnduck(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        void HookCategorizePosition(PluginId owner, GameHookHandler<CategorizePositionContext> handler, bool post) override;
        void HookCheckFalling(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        void HookCheckParameters(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        void HookCheckVelocity(PluginId owner, GameHookHandler<CheckVelocityContext> handler, bool post) override;
        void HookCheckWater(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        void HookDuck(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        void HookFriction(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        void HookFullWalkMove(PluginId owner, GameHookHandler<FullWalkMoveContext> handler, bool post) override;
        void HookGroundAccelerate(PluginId owner, GameHookHandler<GroundAccelerateContext> handler, bool post) override;
        void HookLadderMove(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        void HookMoveInit(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        void HookPlayerMove(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        void HookProcessMovement(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        void HookSetupMove(PluginId owner, GameHookHandler<SetupMoveContext> handler, bool post) override;
        void HookTryPlayerMove(PluginId owner, GameHookHandler<TryPlayerMoveContext> handler, bool post) override;
        void HookWalkMove(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        void HookWaterMove(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        void HookOnJumpLegacy(PluginId owner, GameHookHandler<LegacyJumpContext> handler, bool post) override;
        void HookOnJumpModern(PluginId owner, GameHookHandler<ModernJumpContext> handler, bool post) override;
        void HookCheckJumpButtonLegacy(PluginId owner, GameHookHandler<LegacyJumpContext> handler, bool post) override;
        void HookCheckJumpButtonModern(PluginId owner, GameHookHandler<ModernJumpContext> handler, bool post) override;

        void Unhook(PluginId owner, GameHook hook, bool post) override;
        void UnhookAll(PluginId owner) override;
        bool IsAvailable(GameHook hook) override;

    private:
        std::vector<std::unique_ptr<IGameHook>> m_hooks; // indexed by GameHook
    };

    extern GameHooksManager gameHooksManager;
}
