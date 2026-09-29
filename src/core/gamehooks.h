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
        virtual bool Remove(GameHookId id) = 0;
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

        GameHookId HookTakeDamage(PluginId owner, GameHookHandler<TakeDamageContext> handler, bool post) override;
        GameHookId HookCanAcquire(PluginId owner, GameHookHandler<CanAcquireContext> handler, bool post) override;
        GameHookId HookCanMove(PluginId owner, GameHookHandler<CanMoveContext> handler, bool post) override;
        GameHookId HookCanUse(PluginId owner, GameHookHandler<CanUseContext> handler, bool post) override;
        GameHookId HookPostThink(PluginId owner, GameHookHandler<PostThinkContext> handler, bool post) override;
        GameHookId HookProcessUsercmds(PluginId owner, GameHookHandler<ProcessUsercmdsContext> handler, bool post) override;
        GameHookId HookSimulateUserCommands(PluginId owner, GameHookHandler<SimulateUserCommandsContext> handler, bool post) override;
        GameHookId HookRunCommand(PluginId owner, GameHookHandler<RunCommandContext> handler, bool post) override;
        GameHookId HookAcceptInput(PluginId owner, GameHookHandler<AcceptInputContext> handler, bool post) override;
        GameHookId HookTouch(PluginId owner, GameHookHandler<TouchContext> handler, bool post) override;
        GameHookId HookDropWeapon(PluginId owner, GameHookHandler<DropWeaponContext> handler, bool post) override;
        GameHookId HookAirAccelerate(PluginId owner, GameHookHandler<AirAccelerateContext> handler, bool post) override;
        GameHookId HookAirMove(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        GameHookId HookCanUnduck(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        GameHookId HookCategorizePosition(PluginId owner, GameHookHandler<CategorizePositionContext> handler, bool post) override;
        GameHookId HookCheckFalling(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        GameHookId HookCheckParameters(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        GameHookId HookCheckVelocity(PluginId owner, GameHookHandler<CheckVelocityContext> handler, bool post) override;
        GameHookId HookCheckWater(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        GameHookId HookDuck(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        GameHookId HookFriction(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        GameHookId HookFullWalkMove(PluginId owner, GameHookHandler<FullWalkMoveContext> handler, bool post) override;
        GameHookId HookGroundAccelerate(PluginId owner, GameHookHandler<GroundAccelerateContext> handler, bool post) override;
        GameHookId HookLadderMove(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        GameHookId HookMoveInit(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        GameHookId HookPlayerMove(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        GameHookId HookProcessMovement(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        GameHookId HookSetupMove(PluginId owner, GameHookHandler<SetupMoveContext> handler, bool post) override;
        GameHookId HookTryPlayerMove(PluginId owner, GameHookHandler<TryPlayerMoveContext> handler, bool post) override;
        GameHookId HookWalkMove(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        GameHookId HookWaterMove(PluginId owner, GameHookHandler<MovementContext> handler, bool post) override;
        GameHookId HookOnJumpLegacy(PluginId owner, GameHookHandler<LegacyJumpContext> handler, bool post) override;
        GameHookId HookOnJumpModern(PluginId owner, GameHookHandler<ModernJumpContext> handler, bool post) override;
        GameHookId HookCheckJumpButtonLegacy(PluginId owner, GameHookHandler<LegacyJumpContext> handler, bool post) override;
        GameHookId HookCheckJumpButtonModern(PluginId owner, GameHookHandler<ModernJumpContext> handler, bool post) override;

        void UnhookTakeDamage(GameHookId id) override;
        void UnhookCanAcquire(GameHookId id) override;
        void UnhookCanMove(GameHookId id) override;
        void UnhookCanUse(GameHookId id) override;
        void UnhookPostThink(GameHookId id) override;
        void UnhookProcessUsercmds(GameHookId id) override;
        void UnhookSimulateUserCommands(GameHookId id) override;
        void UnhookRunCommand(GameHookId id) override;
        void UnhookAcceptInput(GameHookId id) override;
        void UnhookTouch(GameHookId id) override;
        void UnhookDropWeapon(GameHookId id) override;
        void UnhookAirAccelerate(GameHookId id) override;
        void UnhookAirMove(GameHookId id) override;
        void UnhookCanUnduck(GameHookId id) override;
        void UnhookCategorizePosition(GameHookId id) override;
        void UnhookCheckFalling(GameHookId id) override;
        void UnhookCheckParameters(GameHookId id) override;
        void UnhookCheckVelocity(GameHookId id) override;
        void UnhookCheckWater(GameHookId id) override;
        void UnhookDuck(GameHookId id) override;
        void UnhookFriction(GameHookId id) override;
        void UnhookFullWalkMove(GameHookId id) override;
        void UnhookGroundAccelerate(GameHookId id) override;
        void UnhookLadderMove(GameHookId id) override;
        void UnhookMoveInit(GameHookId id) override;
        void UnhookPlayerMove(GameHookId id) override;
        void UnhookProcessMovement(GameHookId id) override;
        void UnhookSetupMove(GameHookId id) override;
        void UnhookTryPlayerMove(GameHookId id) override;
        void UnhookWalkMove(GameHookId id) override;
        void UnhookWaterMove(GameHookId id) override;
        void UnhookOnJumpLegacy(GameHookId id) override;
        void UnhookOnJumpModern(GameHookId id) override;
        void UnhookCheckJumpButtonLegacy(GameHookId id) override;
        void UnhookCheckJumpButtonModern(GameHookId id) override;
        bool IsAvailable(GameHook hook) override;

    private:
        std::vector<std::unique_ptr<IGameHook>> m_hooks; // indexed by GameHook
    };

    extern GameHooksManager gameHooksManager;

    /// "toolkit hookdebug": logs every call of the named game hook ("all" for
    /// every one, "" / "off" to stop) -- each plugin's answer, what the core
    /// made of it and the return value.
    void SetHookDebug(const char* name);
    const char* GetHookDebug();
}
