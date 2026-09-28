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
#include "gamehooks.h"

#include <algorithm>
#include <type_traits>

// KHook, via metamod.
#include "ISmmPlugin.h"

#include "dynlibutils/module.hpp"
#include "source2toolkit/IToolkitKHook.h"
#include "shared.h"
#include "tkvprof.h"
#include "utils/log.h"

// The hooked functions take and return pointers to these; nothing here
// looks inside them, so the forward declarations of the SDK header do.

namespace gamehooks
{
    GameHooksManager gameHooksManager;

    namespace
    {
        template <typename CONTEXT>
        struct Listener
        {
            PluginId owner;
            GameHookHandler<CONTEXT> handler;
        };

        // The listeners of one hook, pre and post, and the dispatch over them:
        // Supersede stops the chain, otherwise the strongest answer wins --
        // the same rule as the command listeners.
        template <typename CONTEXT>
        class Listeners
        {
        public:
            void Add(PluginId owner, GameHookHandler<CONTEXT> handler, bool post)
            {
                (post ? m_post : m_pre).push_back({ owner, std::move(handler) });
            }

            void Remove(PluginId owner, bool post)
            {
                auto& list = post ? m_post : m_pre;
                std::erase_if(list, [owner](const Listener<CONTEXT>& l) { return l.owner == owner; });
            }

            bool Empty() const
            {
                return m_pre.empty() && m_post.empty();
            }

            bool Has(bool post) const
            {
                return !(post ? m_post : m_pre).empty();
            }

            Action Dispatch(CONTEXT& ctx, bool post) const
            {
                // A copy: a handler may unhook from inside itself.
                const auto list = post ? m_post : m_pre;
                Action result = Action::Ignore;

                for (const auto& l : list)
                {
                    const Action a = l.handler(ctx, post);

                    if (a == Action::Supersede)
                        return a;

                    if (static_cast<int>(a) > static_cast<int>(result))
                        result = a;
                }

                return result;
            }

        private:
            std::vector<Listener<CONTEXT>> m_pre;
            std::vector<Listener<CONTEXT>> m_post;
        };

        // The context member the return value lives in; nothing for void.
        template <typename CONTEXT, typename RETURN>
        struct ResultMemberOf
        {
            using type = RETURN CONTEXT::*;
        };

        template <typename CONTEXT>
        struct ResultMemberOf<CONTEXT, void>
        {
            using type = std::nullptr_t;
        };

        // What every kind shares: listeners, the "install on first listener,
        // uninstall on the next Tick() after the last one left" rule, and the
        // pre/post dispatch that builds the context and applies its result.
        template <typename CONTEXT, typename RETURN, typename CLASS, typename... ARGS>
        class GameHookBase : public IGameHook
        {
        public:
            using MakeContext = CONTEXT (*)(CLASS*, ARGS...);
            using ResultMember = typename ResultMemberOf<CONTEXT, RETURN>::type;

            GameHookBase(const char* pszName, MakeContext make, ResultMember result)
                : m_pszName(pszName), m_make(make), m_result(result)
            {
            }

            const char* Name() const override { return m_pszName; }

            void Add(PluginId owner, GameHookHandler<CONTEXT> handler, bool post)
            {
                m_listeners.Add(owner, std::move(handler), post);
                Install();
            }

            void Remove(PluginId owner, bool post) override { m_listeners.Remove(owner, post); }

            void RemoveAll(PluginId owner) override
            {
                m_listeners.Remove(owner, false);
                m_listeners.Remove(owner, true);
            }

            bool Empty() const override { return m_listeners.Empty(); }

            bool IsAvailable() override { return Resolve(); }

            KHook::Return<RETURN> Pre(CLASS* pThis, ARGS... args)
            {
                if (!m_listeners.Has(false))
                    return Ignore();

                CONTEXT ctx = m_make(pThis, args...);
                const Action action = m_listeners.Dispatch(ctx, false);

                if constexpr (std::is_void_v<RETURN>)
                {
                    // Nothing to override without a return value; Supersede still skips the original.
                    return { action == Action::Supersede ? KHook::Action::Supersede : KHook::Action::Ignore };
                }
                else
                {
                    if (action == Action::Ignore)
                        return Ignore();

                    return { action, ctx.*m_result };
                }
            }

            KHook::Return<RETURN> Post(CLASS* pThis, ARGS... args)
            {
                if (!m_listeners.Has(true))
                    return Ignore();

                CONTEXT ctx = m_make(pThis, args...);

                if constexpr (!std::is_void_v<RETURN>)
                {
                    if (auto* original = static_cast<RETURN*>(KHook::GetOriginalValuePtr()))
                        ctx.*m_result = *original;
                }

                const Action action = m_listeners.Dispatch(ctx, true);

                if constexpr (std::is_void_v<RETURN>)
                {
                    return { KHook::Action::Ignore };
                }
                else
                {
                    if (action == Action::Ignore)
                        return Ignore();

                    return { KHook::Action::Override, ctx.*m_result };
                }
            }

        protected:
            static KHook::Return<RETURN> Ignore()
            {
                if constexpr (std::is_void_v<RETURN>)
                    return { KHook::Action::Ignore };
                else
                    return { KHook::Action::Ignore, RETURN{} };
            }

            // Finds the function; false, said once, when gamedata has nothing.
            virtual bool Resolve() = 0;
            // Places the detour when it is not in yet and the function is known.
            virtual void Install() = 0;

            const char* m_pszName;
            MakeContext m_make;
            ResultMember m_result;
            Listeners<CONTEXT> m_listeners;
            bool m_bWarned = false;
        };

        // A function found by signature, detoured by address.
        template <typename CONTEXT, typename RETURN, typename CLASS, typename... ARGS>
        class MemberGameHook final : public GameHookBase<CONTEXT, RETURN, CLASS, ARGS...>
        {
            using Base = GameHookBase<CONTEXT, RETURN, CLASS, ARGS...>;
            using Self = MemberGameHook;

        public:
            using Base::Base;

            ~MemberGameHook() override { Uninstall(); }

            void Uninstall() override
            {
                // Synchronous: only from Tick() and Shutdown(), never from a
                // callback of this hook.
                delete m_pHook;
                m_pHook = nullptr;
            }

        protected:
            bool Resolve() override
            {
                if (m_address)
                    return true;

                const IToolkitMemory address = shared::g_pGameConfig ? shared::g_pGameConfig->ResolveSignature(this->m_pszName) : IToolkitMemory();
                if (!address)
                {
                    if (!this->m_bWarned)
                    {
                        this->m_bWarned = true;
                        FP_WARN("Game hook '{}': no signature in gamedata for this platform; its handlers never run", this->m_pszName);
                    }
                    return false;
                }

                m_address = address.GetPtr();
                return true;
            }

            void Install() override
            {
                if (m_pHook || !Resolve())
                    return;

                // Pre/Post are the base's, so the context is the base too.
                m_pHook = new KHook::Member<CLASS, RETURN, ARGS...>(static_cast<Base*>(this), &Base::Pre, &Base::Post);
                m_pHook->Configure(m_address);
            }

        private:
            void* m_address = nullptr;
            KHook::Member<CLASS, RETURN, ARGS...>* m_pHook = nullptr;
        };

        // A virtual function: gamedata offset on the vtable of an RTTI class in
        // libserver, hooked for every object sharing that vtable.
        template <typename CONTEXT, typename RETURN, typename CLASS, typename... ARGS>
        class VirtualGameHook final : public GameHookBase<CONTEXT, RETURN, CLASS, ARGS...>
        {
            using Base = GameHookBase<CONTEXT, RETURN, CLASS, ARGS...>;
            using Self = VirtualGameHook;

        public:
            VirtualGameHook(const char* pszName, const char* pszVTable, typename Base::MakeContext make, typename Base::ResultMember result)
                : Base(pszName, make, result), m_pszVTable(pszVTable)
            {
            }

            ~VirtualGameHook() override { Uninstall(); }

            void Uninstall() override
            {
                if (!m_pHook)
                    return;

                m_pHook->RemoveGlobal(reinterpret_cast<CLASS*>(&m_pVTable));
                delete m_pHook;
                m_pHook = nullptr;
            }

        protected:
            bool Resolve() override
            {
                if (m_index >= 0 && m_pVTable)
                    return true;

                m_index = shared::g_pGameConfig ? shared::g_pGameConfig->GetOffset(this->m_pszName) : -1;

                if (m_index >= 0)
                {
                    DynLibUtils::CModule server(g_pSource2Server);
                    m_pVTable = server.GetVirtualTableByName(m_pszVTable).GetPtr();
                }

                if (m_index < 0 || !m_pVTable)
                {
                    if (!this->m_bWarned)
                    {
                        this->m_bWarned = true;
                        FP_WARN("Game hook '{}': {} for this platform; its handlers never run", this->m_pszName,
                                m_index < 0 ? "no offset in gamedata" : "vtable not found");
                    }
                    return false;
                }

                return true;
            }

            void Install() override
            {
                if (m_pHook || !Resolve())
                    return;

                m_pHook = new ToolkitKHook::Virtual<CLASS, RETURN, ARGS...>(static_cast<std::uint32_t>(m_index), static_cast<Base*>(this), &Base::Pre, &Base::Post);
                // AddGlobal reads the first pointer of what it is handed, so a
                // pointer holding the vtable stands in for an object.
                m_pHook->AddGlobal(reinterpret_cast<CLASS*>(&m_pVTable));
            }

        private:
            const char* m_pszVTable;
            int m_index = -1;
            void* m_pVTable = nullptr;
            ToolkitKHook::Virtual<CLASS, RETURN, ARGS...>* m_pHook = nullptr;
        };

        template <typename HOOK>
        HOOK& As(std::unique_ptr<IGameHook>& p)
        {
            return *static_cast<HOOK*>(p.get());
        }

        // The movement functions that take the move data alone share a context.
        using MoveServices = CCSPlayer_MovementServices;
        MovementContext MakeMovement(MoveServices* s, CMoveData* mv) { return MovementContext{ s, mv, false }; }
    }

    // ---- the table: prototypes as IToolkitAddresses.h has them -------------

    using TakeDamageHook = MemberGameHook<TakeDamageContext, std::int64_t, CBaseEntity, CTakeDamageInfo*, CTakeDamageResult*>;
    using CanAcquireHook = MemberGameHook<CanAcquireContext, AcquireResult, CCSPlayer_ItemServices, CEconItemView*, AcquireMethod, void*>;
    using CanMoveHook = MemberGameHook<CanMoveContext, bool, CCSPlayerPawnBase>;
    using CanUseHook = VirtualGameHook<CanUseContext, bool, CCSPlayer_WeaponServices, CBasePlayerWeapon*>;
    using PostThinkHook = MemberGameHook<PostThinkContext, void, CCSPlayerPawnBase>;
    using ProcessUsercmdsHook = MemberGameHook<ProcessUsercmdsContext, void*, CCSPlayerController, void*, int, bool, float>;
    using SimulateUserCommandsHook = MemberGameHook<SimulateUserCommandsContext, void, CBasePlayerController>;
    using RunCommandHook = VirtualGameHook<RunCommandContext, void, MoveServices, void*>;
    using AcceptInputHook = MemberGameHook<AcceptInputContext, bool, CEntityIdentity, CUtlSymbolLarge*, CEntityInstance*, CEntityInstance*, variant_t*, void*, void*>;
    using TouchHook = VirtualGameHook<TouchContext, void, CBaseEntity, CBaseEntity*>;
    using DropWeaponHook = VirtualGameHook<DropWeaponContext, void, CCSPlayer_WeaponServices, CBasePlayerWeapon*, Vector*, Vector*>;
    using MoveVoidHook = MemberGameHook<MovementContext, void, MoveServices, CMoveData*>;
    using MoveBoolHook = MemberGameHook<MovementContext, bool, MoveServices, CMoveData*>;
    using AirAccelerateHook = MemberGameHook<AirAccelerateContext, void, MoveServices, CMoveData*, Vector*, float, float>;
#ifdef _WIN32
    // The wish direction and the frame time swap places between platforms;
    // the context has one order.
    using GroundAccelerateHook = MemberGameHook<GroundAccelerateContext, void, MoveServices, CMoveData*, float, Vector*, float, float>;
#else
    using GroundAccelerateHook = MemberGameHook<GroundAccelerateContext, void, MoveServices, CMoveData*, Vector*, float, float, float>;
#endif
    using CategorizePositionHook = MemberGameHook<CategorizePositionContext, void, MoveServices, CMoveData*, bool>;
    using CheckVelocityHook = MemberGameHook<CheckVelocityContext, void, MoveServices, CMoveData*, void*>;
    using FullWalkMoveHook = MemberGameHook<FullWalkMoveContext, void, MoveServices, CMoveData*, bool>;
    using SetupMoveHook = MemberGameHook<SetupMoveContext, void, MoveServices, CUserCmd*, CMoveData*>;
    using TryPlayerMoveHook = MemberGameHook<TryPlayerMoveContext, void, MoveServices, CMoveData*, Vector*, CGameTrace*, bool*>;
    using LegacyJumpHook = MemberGameHook<LegacyJumpContext, void, CCSPlayerLegacyJump, CMoveData*>;
    using ModernJumpHook = MemberGameHook<ModernJumpContext, void, CCSPlayerModernJump, CMoveData*>;

    GameHooksManager::GameHooksManager()
    {
        m_hooks.resize(static_cast<size_t>(GameHook::Count));
        auto slot = [this](GameHook h, IGameHook* hook) { m_hooks[static_cast<size_t>(h)].reset(hook); };

        slot(GameHook::TakeDamage, new TakeDamageHook("CBaseEntity::TakeDamageOld",
            [](CBaseEntity* e, CTakeDamageInfo* info, CTakeDamageResult* result) { return TakeDamageContext{ e, info, result, 0 }; },
            &TakeDamageContext::result));
        slot(GameHook::CanAcquire, new CanAcquireHook("CCSPlayer_ItemServices::CanAcquire",
            [](CCSPlayer_ItemServices* s, CEconItemView* item, AcquireMethod method, void* unk) { return CanAcquireContext{ s, item, method, unk, AcquireResult::Allowed }; },
            &CanAcquireContext::result));
        slot(GameHook::CanMove, new CanMoveHook("CCSPlayerPawnBase::CanMove",
            [](CCSPlayerPawnBase* pawn) { return CanMoveContext{ pawn, false }; }, &CanMoveContext::result));
        slot(GameHook::CanUse, new CanUseHook("CCSPlayer_WeaponServices::CanUse", "CCSPlayer_WeaponServices",
            [](CCSPlayer_WeaponServices* s, CBasePlayerWeapon* w) { return CanUseContext{ s, w, false }; }, &CanUseContext::result));
        slot(GameHook::PostThink, new PostThinkHook("CCSPlayerPawn::PostThink",
            [](CCSPlayerPawnBase* pawn) { return PostThinkContext{ pawn }; }, nullptr));
        slot(GameHook::ProcessUsercmds, new ProcessUsercmdsHook("CCSPlayerController::ProcessUserCmd",
            [](CCSPlayerController* c, void* cmds, int count, bool paused, float margin) { return ProcessUsercmdsContext{ c, cmds, count, paused, margin, nullptr }; },
            &ProcessUsercmdsContext::result));
        slot(GameHook::SimulateUserCommands, new SimulateUserCommandsHook("CBasePlayerController::OnSimulateUserCommands",
            [](CBasePlayerController* c) { return SimulateUserCommandsContext{ c }; }, nullptr));
        slot(GameHook::RunCommand, new RunCommandHook("CPlayer_MovementServices::RunCommand", "CCSPlayer_MovementServices",
            [](MoveServices* s, void* cmd) { return RunCommandContext{ s, cmd }; }, nullptr));
        slot(GameHook::AcceptInput, new AcceptInputHook("CEntityIdentity::AcceptInput",
            [](CEntityIdentity* i, CUtlSymbolLarge* name, CEntityInstance* activator, CEntityInstance* caller, variant_t* value, void*, void*) { return AcceptInputContext{ i, name, activator, caller, value, false }; },
            &AcceptInputContext::result));
        slot(GameHook::Touch, new TouchHook("CBaseEntity::Touch", "CBaseEntity",
            [](CBaseEntity* e, CBaseEntity* other) { return TouchContext{ e, other }; }, nullptr));
        slot(GameHook::DropWeapon, new DropWeaponHook("CCSPlayer_WeaponServices::DropWeapon", "CCSPlayer_WeaponServices",
            [](CCSPlayer_WeaponServices* s, CBasePlayerWeapon* w, Vector* target, Vector* velocity) { return DropWeaponContext{ s, w, target, velocity }; }, nullptr));
        slot(GameHook::AirAccelerate, new AirAccelerateHook("CCSPlayer_MovementServices::AirAccelerate",
            [](MoveServices* s, CMoveData* mv, Vector* dir, float speed, float accel) { return AirAccelerateContext{ s, mv, dir, speed, accel }; }, nullptr));
        slot(GameHook::AirMove, new MoveVoidHook("CCSPlayer_MovementServices::AirMove", &MakeMovement, nullptr));
        slot(GameHook::CanUnduck, new MoveBoolHook("CCSPlayer_MovementServices::CanUnduck", &MakeMovement, &MovementContext::result));
        slot(GameHook::CategorizePosition, new CategorizePositionHook("CCSPlayer_MovementServices::CategorizePosition",
            [](MoveServices* s, CMoveData* mv, bool stayOnGround) { return CategorizePositionContext{ s, mv, stayOnGround }; }, nullptr));
        slot(GameHook::CheckFalling, new MoveVoidHook("CCSPlayer_MovementServices::CheckFalling", &MakeMovement, nullptr));
        slot(GameHook::CheckParameters, new MoveVoidHook("CCSPlayer_MovementServices::CheckParameters", &MakeMovement, nullptr));
        slot(GameHook::CheckVelocity, new CheckVelocityHook("CCSPlayer_MovementServices::CheckVelocity",
            [](MoveServices* s, CMoveData* mv, void* unk) { return CheckVelocityContext{ s, mv, unk }; }, nullptr));
        slot(GameHook::CheckWater, new MoveBoolHook("CCSPlayer_MovementServices::CheckWater", &MakeMovement, &MovementContext::result));
        slot(GameHook::Duck, new MoveVoidHook("CCSPlayer_MovementServices::Duck", &MakeMovement, nullptr));
        slot(GameHook::Friction, new MoveVoidHook("CCSPlayer_MovementServices::Friction", &MakeMovement, nullptr));
        slot(GameHook::FullWalkMove, new FullWalkMoveHook("CCSPlayer_MovementServices::FullWalkMove",
            [](MoveServices* s, CMoveData* mv, bool onGround) { return FullWalkMoveContext{ s, mv, onGround }; }, nullptr));
#ifdef _WIN32
        slot(GameHook::GroundAccelerate, new GroundAccelerateHook("CCSPlayer_MovementServices::GroundAccelerate",
            [](MoveServices* s, CMoveData* mv, float frameTime, Vector* dir, float speed, float accel) { return GroundAccelerateContext{ s, mv, dir, frameTime, speed, accel }; }, nullptr));
#else
        slot(GameHook::GroundAccelerate, new GroundAccelerateHook("CCSPlayer_MovementServices::GroundAccelerate",
            [](MoveServices* s, CMoveData* mv, Vector* dir, float frameTime, float speed, float accel) { return GroundAccelerateContext{ s, mv, dir, frameTime, speed, accel }; }, nullptr));
#endif
        slot(GameHook::LadderMove, new MoveBoolHook("CCSPlayer_MovementServices::LadderMove", &MakeMovement, &MovementContext::result));
        slot(GameHook::MoveInit, new MoveBoolHook("CCSPlayer_MovementServices::MoveInit", &MakeMovement, &MovementContext::result));
        slot(GameHook::PlayerMove, new MoveVoidHook("CCSPlayer_MovementServices::PlayerMove", &MakeMovement, nullptr));
        slot(GameHook::ProcessMovement, new MoveVoidHook("CCSPlayer_MovementServices::ProcessMovement", &MakeMovement, nullptr));
        slot(GameHook::SetupMove, new SetupMoveHook("CCSPlayer_MovementServices::SetupMove",
            [](MoveServices* s, CUserCmd* cmd, CMoveData* mv) { return SetupMoveContext{ s, cmd, mv }; }, nullptr));
        slot(GameHook::TryPlayerMove, new TryPlayerMoveHook("CCSPlayer_MovementServices::TryPlayerMove",
            [](MoveServices* s, CMoveData* mv, Vector* dest, CGameTrace* trace, bool* surfing) { return TryPlayerMoveContext{ s, mv, dest, trace, surfing }; }, nullptr));
        slot(GameHook::WalkMove, new MoveVoidHook("CCSPlayer_MovementServices::WalkMove", &MakeMovement, nullptr));
        slot(GameHook::WaterMove, new MoveVoidHook("CCSPlayer_MovementServices::WaterMove", &MakeMovement, nullptr));
        slot(GameHook::OnJumpLegacy, new LegacyJumpHook("CCSPlayerLegacyJump::OnJump",
            [](CCSPlayerLegacyJump* j, CMoveData* mv) { return LegacyJumpContext{ j, mv }; }, nullptr));
        slot(GameHook::OnJumpModern, new ModernJumpHook("CCSPlayerModernJump::OnJump",
            [](CCSPlayerModernJump* j, CMoveData* mv) { return ModernJumpContext{ j, mv }; }, nullptr));
        slot(GameHook::CheckJumpButtonLegacy, new LegacyJumpHook("CCSPlayerLegacyJump::CheckJumpButton",
            [](CCSPlayerLegacyJump* j, CMoveData* mv) { return LegacyJumpContext{ j, mv }; }, nullptr));
        slot(GameHook::CheckJumpButtonModern, new ModernJumpHook("CCSPlayerModernJump::CheckJumpButton",
            [](CCSPlayerModernJump* j, CMoveData* mv) { return ModernJumpContext{ j, mv }; }, nullptr));
    }

    GameHooksManager::~GameHooksManager() = default;

    void GameHooksManager::Shutdown()
    {
        for (auto& hook : m_hooks)
            hook->Uninstall();
    }

    void GameHooksManager::Tick()
    {
        for (auto& hook : m_hooks)
        {
            if (hook->Empty())
                hook->Uninstall();
        }
    }

    void GameHooksManager::RemoveAllForPlugin(PluginId id)
    {
        // The detour itself waits for Tick(): this can run from inside a
        // console command, and a plugin may be unloading from a handler.
        for (auto& hook : m_hooks)
            hook->RemoveAll(id);
    }

#define GAMEHOOK_ADD(Method, HookType, Ctx, Which) \
    void GameHooksManager::Method(PluginId owner, GameHookHandler<Ctx> handler, bool post) \
    { \
        As<HookType>(m_hooks[static_cast<size_t>(GameHook::Which)]).Add(owner, std::move(handler), post); \
    }

    GAMEHOOK_ADD(HookTakeDamage, TakeDamageHook, TakeDamageContext, TakeDamage)
    GAMEHOOK_ADD(HookCanAcquire, CanAcquireHook, CanAcquireContext, CanAcquire)
    GAMEHOOK_ADD(HookCanMove, CanMoveHook, CanMoveContext, CanMove)
    GAMEHOOK_ADD(HookCanUse, CanUseHook, CanUseContext, CanUse)
    GAMEHOOK_ADD(HookPostThink, PostThinkHook, PostThinkContext, PostThink)
    GAMEHOOK_ADD(HookProcessUsercmds, ProcessUsercmdsHook, ProcessUsercmdsContext, ProcessUsercmds)
    GAMEHOOK_ADD(HookSimulateUserCommands, SimulateUserCommandsHook, SimulateUserCommandsContext, SimulateUserCommands)
    GAMEHOOK_ADD(HookRunCommand, RunCommandHook, RunCommandContext, RunCommand)
    GAMEHOOK_ADD(HookAcceptInput, AcceptInputHook, AcceptInputContext, AcceptInput)
    GAMEHOOK_ADD(HookTouch, TouchHook, TouchContext, Touch)
    GAMEHOOK_ADD(HookDropWeapon, DropWeaponHook, DropWeaponContext, DropWeapon)
    GAMEHOOK_ADD(HookAirAccelerate, AirAccelerateHook, AirAccelerateContext, AirAccelerate)
    GAMEHOOK_ADD(HookAirMove, MoveVoidHook, MovementContext, AirMove)
    GAMEHOOK_ADD(HookCanUnduck, MoveBoolHook, MovementContext, CanUnduck)
    GAMEHOOK_ADD(HookCategorizePosition, CategorizePositionHook, CategorizePositionContext, CategorizePosition)
    GAMEHOOK_ADD(HookCheckFalling, MoveVoidHook, MovementContext, CheckFalling)
    GAMEHOOK_ADD(HookCheckParameters, MoveVoidHook, MovementContext, CheckParameters)
    GAMEHOOK_ADD(HookCheckVelocity, CheckVelocityHook, CheckVelocityContext, CheckVelocity)
    GAMEHOOK_ADD(HookCheckWater, MoveBoolHook, MovementContext, CheckWater)
    GAMEHOOK_ADD(HookDuck, MoveVoidHook, MovementContext, Duck)
    GAMEHOOK_ADD(HookFriction, MoveVoidHook, MovementContext, Friction)
    GAMEHOOK_ADD(HookFullWalkMove, FullWalkMoveHook, FullWalkMoveContext, FullWalkMove)
    GAMEHOOK_ADD(HookGroundAccelerate, GroundAccelerateHook, GroundAccelerateContext, GroundAccelerate)
    GAMEHOOK_ADD(HookLadderMove, MoveBoolHook, MovementContext, LadderMove)
    GAMEHOOK_ADD(HookMoveInit, MoveBoolHook, MovementContext, MoveInit)
    GAMEHOOK_ADD(HookPlayerMove, MoveVoidHook, MovementContext, PlayerMove)
    GAMEHOOK_ADD(HookProcessMovement, MoveVoidHook, MovementContext, ProcessMovement)
    GAMEHOOK_ADD(HookSetupMove, SetupMoveHook, SetupMoveContext, SetupMove)
    GAMEHOOK_ADD(HookTryPlayerMove, TryPlayerMoveHook, TryPlayerMoveContext, TryPlayerMove)
    GAMEHOOK_ADD(HookWalkMove, MoveVoidHook, MovementContext, WalkMove)
    GAMEHOOK_ADD(HookWaterMove, MoveVoidHook, MovementContext, WaterMove)
    GAMEHOOK_ADD(HookOnJumpLegacy, LegacyJumpHook, LegacyJumpContext, OnJumpLegacy)
    GAMEHOOK_ADD(HookOnJumpModern, ModernJumpHook, ModernJumpContext, OnJumpModern)
    GAMEHOOK_ADD(HookCheckJumpButtonLegacy, LegacyJumpHook, LegacyJumpContext, CheckJumpButtonLegacy)
    GAMEHOOK_ADD(HookCheckJumpButtonModern, ModernJumpHook, ModernJumpContext, CheckJumpButtonModern)

#undef GAMEHOOK_ADD

    void GameHooksManager::Unhook(PluginId owner, GameHook hook, bool post)
    {
        if (hook < GameHook::Count)
            m_hooks[static_cast<size_t>(hook)]->Remove(owner, post);
    }

    void GameHooksManager::UnhookAll(PluginId owner)
    {
        RemoveAllForPlugin(owner);
    }

    bool GameHooksManager::IsAvailable(GameHook hook)
    {
        return hook < GameHook::Count && m_hooks[static_cast<size_t>(hook)]->IsAvailable();
    }
}
