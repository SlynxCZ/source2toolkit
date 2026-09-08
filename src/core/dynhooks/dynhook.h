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
 * The bridge/post-callback scheme follows DynamicHooks (Robin Gohmert,
 * AlliedModders LLC) and its x86-64 port by Benoist "Kenzzer" André.
 *
 * Project: Source2Toolkit
 */
#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

/// Dynamic hooks: SourceHook for code that does not know the function's
/// signature at compile time.
///
/// SH_DECL_HOOK and SH_DECL_INLINEHOOK generate a typed hook manager per
/// signature from templates, which a script cannot do. This engine takes the
/// signature as data instead -- a Prototype of DataTypes -- detours the
/// function's entry with safetyhook, and runs a small generated bridge that
/// snapshots every register, lets the handlers read and change arguments
/// and the return value through that snapshot, and restores it before
/// continuing into the original (or skipping it). Post handlers run through
/// a swapped return address, the way DynamicHooks does it.
///
/// A virtual function is just a function: hook the address out of the
/// vtable and filter on `this` in the handler, and you have SH_ADD_HOOK;
/// skip the filter and you have SH_ADD_VPHOOK.
///
/// x86-64 only. System V on Linux, Microsoft x64 on Windows.
namespace dynhooks
{
    enum class DataType : uint8_t
    {
        Void,
        Bool,
        Int8,
        Int16,
        Int32,
        Int64,
        Float,
        Double,
        Pointer,
        /// Three floats by value (Vector). Classified SSE on System V, so
        /// it travels in two xmm registers; passed by hidden pointer on
        /// Microsoft x64.
        Vector3,
        /// Any other struct by value; size must be given. Classified
        /// INTEGER on System V (the common case: handles, string_t, small
        /// structs of ints/pointers).
        Object,
    };

    struct DataTypeSized
    {
        DataType type = DataType::Void;
        size_t size = 0; // Only Object needs it; the rest is implied.

        size_t Size() const;
    };

    struct Prototype
    {
        std::vector<DataTypeSized> args;
        DataTypeSized ret;

        bool operator==(const Prototype& other) const;
    };

    /// META_RES, under the name DynamicHooks gave it.
    enum class ReturnAction : int
    {
        Ignored = 0,
        Handled = 1,
        Override = 2,
        Supercede = 3,
    };

    enum class HookType : int
    {
        Pre = 0,
        Post = 1,
    };

    class DynHook;

    /// A handler. Runs with the register snapshot of the call in place:
    /// everything DynHook offers below is valid for the duration.
    using Handler = std::function<ReturnAction(DynHook& hook, HookType type)>;

    /// One hooked function, shared by every handler on that address.
    class DynHook
    {
    public:
        ~DynHook();

        void* Function() const { return m_pFunction; }
        const Prototype& Proto() const { return m_Proto; }
        bool IsValid() const { return m_bValid; }

        /* =========================
        For handlers, during a call
        ========================= */

        size_t ArgCount() const;

        /// Address of argument i as the callee will see it. For a register
        /// argument this is inside the snapshot; for a stack argument it is
        /// the stack itself. Writing through it and calling ArgChanged(i)
        /// changes what the original function receives.
        void* ArgPtr(size_t index);
        void ArgChanged(size_t index);

        template <typename T> T GetArg(size_t index) { return *static_cast<T*>(ArgPtr(index)); }
        template <typename T> void SetArg(size_t index, const T& value)
        {
            *static_cast<T*>(ArgPtr(index)) = value;
            ArgChanged(index);
        }

        /// The `this` of a thiscall: argument 0.
        void* ThisPtr() { return ArgCount() ? GetArg<void*>(0) : nullptr; }

        /// Address of the return value: in a pre handler where the override
        /// goes, in a post handler where the original's result is. Writing
        /// through it and calling ReturnChanged() is the override.
        void* ReturnPtr();
        void ReturnChanged();
        size_t ReturnSize() const { return m_Proto.ret.Size(); }

        template <typename T> T GetReturn() { return *static_cast<T*>(ReturnPtr()); }
        template <typename T> void SetReturn(const T& value)
        {
            *static_cast<T*>(ReturnPtr()) = value;
            ReturnChanged();
        }

        /* =========================
        Handlers
        ========================= */

        /// Adds a handler; the id is unique across every hook and is what
        /// RemoveHandler and RemoveAllForOwner take.
        int AddHandler(HookType type, Handler handler, int owner);
        bool RemoveHandler(int id);
        void RemoveAllForOwner(int owner);
        bool HasHandlers() const;

    private:
        friend class Manager;
        struct Impl;

        DynHook(void* pFunction, const Prototype& proto);

        void* m_pFunction = nullptr;
        Prototype m_Proto;
        bool m_bValid = false;
        std::unique_ptr<Impl> m_pImpl;
    };

    /// All hooks, one per function address.
    class Manager
    {
    public:
        /// The hook for pFunction, created with this prototype the first
        /// time. A second caller must describe the function the same way;
        /// a mismatch returns nullptr and says why in error.
        DynHook* Hook(void* pFunction, const Prototype& proto, std::string* pError = nullptr);

        DynHook* Find(void* pFunction);

        /// Removes the handler with this id; the hook itself goes once its
        /// last handler is gone (the original function is restored).
        bool RemoveHandler(int id);

        /// Drops every handler a plugin owns.
        void RemoveAllForOwner(int owner);

        /// Restores every function. Called on unload.
        void Shutdown();

    private:
        std::vector<std::unique_ptr<DynHook>> m_Hooks;
    };

    extern Manager manager;
}
