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
#include "dynhook.h"

#include "utils/log.h"

// sourcehook.h first: sh_asm.h wants SH_ASSERT and SH_COMP from it.
#include "sourcehook/sourcehook.h"
#include "sourcehook/sh_pagealloc.h"
#include "sh_asm_x86_64.h"

#include "safetyhook.hpp"

#include <algorithm>
#include <atomic>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <thread>
#include <unordered_map>

#if !defined(_M_X64) && !defined(__x86_64__)
#error "dynhooks: x86-64 only"
#endif

#if defined(_WIN32)
#define DYNHOOKS_MS_ABI 1
#else
#define DYNHOOKS_MS_ABI 0
#endif

namespace dynhooks
{
    using namespace SourceHook::Asm;

    Manager manager;

    /* =========================
    Types
    ========================= */

    size_t DataTypeSized::Size() const
    {
        switch (type)
        {
            case DataType::Void:    return 0;
            case DataType::Bool:    return 1;
            case DataType::Int8:    return 1;
            case DataType::Int16:   return 2;
            case DataType::Int32:   return 4;
            case DataType::Int64:   return 8;
            case DataType::Float:   return 4;
            case DataType::Double:  return 8;
            case DataType::Pointer: return 8;
            case DataType::Vector3: return 12;
            case DataType::Object:  return size;
        }

        return 0;
    }

    bool Prototype::operator==(const Prototype& other) const
    {
        if (ret.type != other.ret.type || ret.Size() != other.ret.Size() || args.size() != other.args.size())
            return false;

        for (size_t i = 0; i < args.size(); ++i)
        {
            if (args[i].type != other.args[i].type || args[i].Size() != other.args[i].Size())
                return false;
        }

        return true;
    }

    namespace
    {
        /* =========================
        Register snapshot
        ========================= */

        // Every register the bridge saves, at fixed addresses the generated
        // code carries as immediates. Indexed by SourceHook::Asm::x8664Reg
        // and x8664FloatReg.
        struct RegisterSnapshot
        {
            uint64_t gp[16];
            alignas(16) uint8_t xmm[16][16];
        };

        constexpr int kSavedXmmCount = 8; // xmm0-7 carry arguments and returns; the rest never do.

        inline size_t Align8(size_t size) { return (size + 7) & ~size_t(7); }
        inline size_t SlotSize(size_t size) { return std::max<size_t>(16, Align8(size)); }

        /* =========================
        Calling convention
        ========================= */

        // Where an argument lives on entry, computed once from the prototype.
        struct ArgLocation
        {
            enum Kind : uint8_t
            {
                GpReg,         // one general-purpose register
                XmmReg,        // one xmm register
                GpPair,        // two general-purpose registers (System V, 9-16 byte object)
                XmmPair,       // two xmm registers (System V Vector3)
                Stack,         // on the stack, at the stack base + offset
                IndirectGp,    // Microsoft x64: pointer to a caller copy, in a gp register
                IndirectStack, // Microsoft x64: pointer to a caller copy, on the stack
            };

            Kind kind = Stack;
            uint8_t reg = 0;
            uint8_t reg2 = 0;
            uint32_t stackOffset = 0;
            size_t size = 0;
        };

        struct ReturnLocation
        {
            enum Kind : uint8_t
            {
                None,
                Gp,      // rax
                GpPair,  // rax:rdx
                Xmm,     // xmm0
                XmmPair, // xmm0:xmm1 (System V Vector3)
                Memory,  // through the hidden pointer argument
            };

            Kind kind = None;
            size_t size = 0;
        };

        class Convention
        {
        public:
            Convention(const Prototype& proto, RegisterSnapshot& snapshot)
                : m_Proto(proto), m_Snapshot(snapshot)
            {
                Layout();
            }

            size_t ArgCount() const { return m_Args.size(); }
            size_t ReturnSize() const { return m_Return.size; }

            // Pre or post: the one thing that differs is where a memory
            // return lives (the hidden argument on the way in, rax on the
            // way out).
            void SetPhase(HookType phase) { m_Phase = phase; }

            // Where the stack arguments begin, given the entry rsp.
            uintptr_t StackBase() const
            {
#if DYNHOOKS_MS_ABI
                return m_Snapshot.gp[RSP] + 8 + 32; // return address + shadow space
#else
                return m_Snapshot.gp[RSP] + 8;      // return address
#endif
            }

            void* ArgPtr(size_t index)
            {
                if (index >= m_Args.size())
                    return nullptr;

                ArgLocation& loc = m_Args[index];

                switch (loc.kind)
                {
                    case ArgLocation::GpReg:
                        return &m_Snapshot.gp[loc.reg];
                    case ArgLocation::XmmReg:
                        return m_Snapshot.xmm[loc.reg];
                    case ArgLocation::Stack:
                        return reinterpret_cast<void*>(StackBase() + loc.stackOffset);
                    case ArgLocation::IndirectGp:
                        return reinterpret_cast<void*>(m_Snapshot.gp[loc.reg]);
                    case ArgLocation::IndirectStack:
                        return *reinterpret_cast<void**>(StackBase() + loc.stackOffset);
                    case ArgLocation::GpPair:
                    {
                        // Assembled into a contiguous scratch copy; ArgChanged
                        // takes it back apart.
                        uint8_t* pScratch = Scratch(index);
                        memcpy(pScratch, &m_Snapshot.gp[loc.reg], 8);
                        memcpy(pScratch + 8, &m_Snapshot.gp[loc.reg2], 8);
                        return pScratch;
                    }
                    case ArgLocation::XmmPair:
                    {
                        uint8_t* pScratch = Scratch(index);
                        memcpy(pScratch, m_Snapshot.xmm[loc.reg], 8);
                        memcpy(pScratch + 8, m_Snapshot.xmm[loc.reg2], 8);
                        return pScratch;
                    }
                }

                return nullptr;
            }

            void ArgChanged(size_t index)
            {
                if (index >= m_Args.size())
                    return;

                ArgLocation& loc = m_Args[index];
                uint8_t* pScratch = Scratch(index);

                if (loc.kind == ArgLocation::GpPair)
                {
                    memcpy(&m_Snapshot.gp[loc.reg], pScratch, 8);
                    memcpy(&m_Snapshot.gp[loc.reg2], pScratch + 8, 8);
                }
                else if (loc.kind == ArgLocation::XmmPair)
                {
                    memcpy(m_Snapshot.xmm[loc.reg], pScratch, 8);
                    memcpy(m_Snapshot.xmm[loc.reg2], pScratch + 8, 8);
                }
            }

            void* ReturnPtr()
            {
                switch (m_Return.kind)
                {
                    case ReturnLocation::Gp:
                        return &m_Snapshot.gp[RAX];
                    case ReturnLocation::Xmm:
                        return m_Snapshot.xmm[XMM0];
                    case ReturnLocation::GpPair:
                        memcpy(m_ReturnScratch, &m_Snapshot.gp[RAX], 8);
                        memcpy(m_ReturnScratch + 8, &m_Snapshot.gp[RDX], 8);
                        return m_ReturnScratch;
                    case ReturnLocation::XmmPair:
                        memcpy(m_ReturnScratch, m_Snapshot.xmm[XMM0], 8);
                        memcpy(m_ReturnScratch + 8, m_Snapshot.xmm[XMM1], 8);
                        return m_ReturnScratch;
                    case ReturnLocation::Memory:
                        // The caller's buffer: passed in the hidden argument on
                        // the way in, handed back in rax on the way out.
                        if (m_Phase == HookType::Post)
                            return reinterpret_cast<void*>(m_Snapshot.gp[RAX]);
                        return reinterpret_cast<void*>(m_Snapshot.gp[m_HiddenReturnReg]);
                    case ReturnLocation::None:
                        break;
                }

                return nullptr;
            }

            void ReturnChanged()
            {
                if (m_Return.kind == ReturnLocation::GpPair)
                {
                    memcpy(&m_Snapshot.gp[RAX], m_ReturnScratch, 8);
                    memcpy(&m_Snapshot.gp[RDX], m_ReturnScratch + 8, 8);
                }
                else if (m_Return.kind == ReturnLocation::XmmPair)
                {
                    memcpy(m_Snapshot.xmm[XMM0], m_ReturnScratch, 8);
                    memcpy(m_Snapshot.xmm[XMM1], m_ReturnScratch + 8, 8);
                }
                else if (m_Return.kind == ReturnLocation::Memory && m_Phase == HookType::Pre)
                {
                    // rax carries the buffer's address out of the function;
                    // after a Supercede nothing else sets it.
                    m_Snapshot.gp[RAX] = m_Snapshot.gp[m_HiddenReturnReg];
                }
            }

            // Post handlers want the arguments the call was made with, but by
            // then the callee has clobbered every argument register and may
            // have reused its incoming stack slots. Saved on the way in,
            // written back into the snapshot (and the dead stack slots) on
            // the way out.
            std::vector<uint8_t> SaveArgs()
            {
                std::vector<uint8_t> saved(m_ArgsSavedSize);
                for (size_t i = 0; i < m_Args.size(); ++i)
                {
                    if (void* pArg = ArgPtr(i))
                        memcpy(saved.data() + m_ArgSaveOffset[i], pArg, m_Args[i].size);
                }
                return saved;
            }

            void RestoreArgs(const std::vector<uint8_t>& saved)
            {
                if (saved.size() < m_ArgsSavedSize)
                    return;

                for (size_t i = 0; i < m_Args.size(); ++i)
                {
                    void* pArg = ArgPtr(i);
                    if (!pArg)
                        continue;

                    memcpy(pArg, saved.data() + m_ArgSaveOffset[i], m_Args[i].size);
                    ArgChanged(i);
                }
            }

            std::vector<uint8_t> SaveReturn()
            {
                std::vector<uint8_t> saved(SlotSize(m_Return.size), 0);
                if (void* pRet = ReturnPtr())
                    memcpy(saved.data(), pRet, m_Return.size);
                return saved;
            }

            void RestoreReturn(const std::vector<uint8_t>& saved)
            {
                void* pRet = ReturnPtr();
                if (!pRet || saved.size() < m_Return.size)
                    return;

                memcpy(pRet, saved.data(), m_Return.size);
                ReturnChanged();
            }

        private:
            uint8_t* Scratch(size_t index)
            {
                if (m_Scratch.size() < (index + 1) * 16)
                    m_Scratch.resize((index + 1) * 16);
                return m_Scratch.data() + index * 16;
            }

            static bool IsFloating(DataType type) { return type == DataType::Float || type == DataType::Double; }

            void Layout()
            {
                m_Return.size = m_Proto.ret.Size();

#if DYNHOOKS_MS_ABI
                LayoutMicrosoft();
#else
                LayoutSystemV();
#endif

                m_ArgSaveOffset.resize(m_Args.size());
                size_t offset = 0;
                for (size_t i = 0; i < m_Args.size(); ++i)
                {
                    m_ArgSaveOffset[i] = offset;
                    offset += SlotSize(m_Args[i].size);
                }
                m_ArgsSavedSize = offset;
            }

#if DYNHOOKS_MS_ABI
            void LayoutMicrosoft()
            {
                static const x8664Reg kGp[4] = { RCX, RDX, R8, R9 };
                static const x8664FloatReg kXmm[4] = { XMM0, XMM1, XMM2, XMM3 };

                const DataTypeSized& ret = m_Proto.ret;
                unsigned slot = 0;
                uint32_t stackOffset = 0;

                // A struct that is not 1, 2, 4 or 8 bytes is returned through
                // a hidden pointer that takes the first slot.
                auto isSmallPow2 = [](size_t size) { return size == 1 || size == 2 || size == 4 || size == 8; };

                if (ret.type == DataType::Void)
                    m_Return.kind = ReturnLocation::None;
                else if (IsFloating(ret.type))
                    m_Return.kind = ReturnLocation::Xmm;
                else if ((ret.type == DataType::Object || ret.type == DataType::Vector3) && !isSmallPow2(m_Return.size))
                {
                    m_Return.kind = ReturnLocation::Memory;
                    m_HiddenReturnReg = kGp[slot++];
                }
                else
                    m_Return.kind = ReturnLocation::Gp;

                for (const DataTypeSized& arg : m_Proto.args)
                {
                    ArgLocation loc;
                    loc.size = arg.Size();

                    const bool bByPointer = (arg.type == DataType::Object || arg.type == DataType::Vector3) && !isSmallPow2(loc.size);

                    if (slot < 4)
                    {
                        if (bByPointer)
                        {
                            loc.kind = ArgLocation::IndirectGp;
                            loc.reg = kGp[slot];
                        }
                        else if (IsFloating(arg.type))
                        {
                            loc.kind = ArgLocation::XmmReg;
                            loc.reg = kXmm[slot];
                        }
                        else
                        {
                            loc.kind = ArgLocation::GpReg;
                            loc.reg = kGp[slot];
                        }
                        ++slot;
                    }
                    else
                    {
                        loc.kind = bByPointer ? ArgLocation::IndirectStack : ArgLocation::Stack;
                        loc.stackOffset = stackOffset;
                        stackOffset += 8;
                    }

                    m_Args.push_back(loc);
                }
            }
#else
            void LayoutSystemV()
            {
                static const x8664Reg kGp[6] = { RDI, RSI, RDX, RCX, R8, R9 };
                static const x8664FloatReg kXmm[8] = { XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7 };

                const DataTypeSized& ret = m_Proto.ret;
                unsigned gp = 0;
                unsigned xmm = 0;
                uint32_t stackOffset = 0;

                if (ret.type == DataType::Void)
                    m_Return.kind = ReturnLocation::None;
                else if (IsFloating(ret.type))
                    m_Return.kind = ReturnLocation::Xmm;
                else if (ret.type == DataType::Vector3)
                    m_Return.kind = ReturnLocation::XmmPair;
                else if (ret.type == DataType::Object && m_Return.size > 16)
                {
                    // MEMORY class: the caller passes the buffer in rdi.
                    m_Return.kind = ReturnLocation::Memory;
                    m_HiddenReturnReg = kGp[gp++];
                }
                else if (ret.type == DataType::Object && m_Return.size > 8)
                    m_Return.kind = ReturnLocation::GpPair;
                else
                    m_Return.kind = ReturnLocation::Gp;

                for (const DataTypeSized& arg : m_Proto.args)
                {
                    ArgLocation loc;
                    loc.size = arg.Size();

                    auto onStack = [&]()
                    {
                        loc.kind = ArgLocation::Stack;
                        loc.stackOffset = stackOffset;
                        stackOffset += static_cast<uint32_t>(Align8(loc.size ? loc.size : 8));
                    };

                    if (IsFloating(arg.type))
                    {
                        if (xmm < 8)
                        {
                            loc.kind = ArgLocation::XmmReg;
                            loc.reg = kXmm[xmm++];
                        }
                        else
                            onStack();
                    }
                    else if (arg.type == DataType::Vector3)
                    {
                        // Two SSE eightbytes: (x, y) and (z). Both registers or
                        // the whole thing on the stack.
                        if (xmm + 2 <= 8)
                        {
                            loc.kind = ArgLocation::XmmPair;
                            loc.reg = kXmm[xmm++];
                            loc.reg2 = kXmm[xmm++];
                        }
                        else
                            onStack();
                    }
                    else if (arg.type == DataType::Object && loc.size > 16)
                        onStack();
                    else if (arg.type == DataType::Object && loc.size > 8)
                    {
                        if (gp + 2 <= 6)
                        {
                            loc.kind = ArgLocation::GpPair;
                            loc.reg = kGp[gp++];
                            loc.reg2 = kGp[gp++];
                        }
                        else
                            onStack();
                    }
                    else
                    {
                        if (gp < 6)
                        {
                            loc.kind = ArgLocation::GpReg;
                            loc.reg = kGp[gp++];
                        }
                        else
                            onStack();
                    }

                    m_Args.push_back(loc);
                }
            }
#endif

            const Prototype& m_Proto;
            RegisterSnapshot& m_Snapshot;
            std::vector<ArgLocation> m_Args;
            std::vector<size_t> m_ArgSaveOffset;
            size_t m_ArgsSavedSize = 0;
            ReturnLocation m_Return;
            x8664Reg m_HiddenReturnReg = RDI;
            HookType m_Phase = HookType::Pre;
            std::vector<uint8_t> m_Scratch;
            alignas(16) uint8_t m_ReturnScratch[16] = {};
        };

        /* =========================
        JIT memory
        ========================= */

        SourceHook::CPageAlloc& PageAllocator()
        {
            static SourceHook::CPageAlloc s_Alloc(16);
            return s_Alloc;
        }

        struct HandlerEntry
        {
            int id;
            int owner;
            HookType type;
            Handler fn;
        };

        // What a pre pass leaves for the post pass of the same call. A stack,
        // since the hooked function can recurse.
        struct CallFrame
        {
            ReturnAction preAction;
            std::vector<uint8_t> args;
            std::vector<uint8_t> ret;
        };

        std::atomic<int> s_NextHandlerId{ 1 };
        const std::thread::id s_MainThread = std::this_thread::get_id();
    }

    /* =========================
    DynHook
    ========================= */

    struct DynHook::Impl
    {
        explicit Impl(const Prototype& proto)
            : convention(proto, snapshot), bridge(&PageAllocator()), postCallback(&PageAllocator())
        {
        }

        RegisterSnapshot snapshot{};
        Convention convention;

        x64JitWriter bridge;
        x64JitWriter postCallback;
        void* pBridge = nullptr;
        void* pPostCallback = nullptr;
        void* pTrampoline = nullptr;
        SafetyHookInline detour{};

        std::vector<HandlerEntry> handlers;
        std::vector<CallFrame> frames;
        std::unordered_map<void*, std::vector<void*>> returnAddresses;

        /* ---- what the generated code calls back into ---- */

        static ReturnAction Dispatch(DynHook* pHook, int type);
        static void StoreReturnAddress(DynHook* pHook, void* pReturnAddress, void* pKey);
        static void* TakeReturnAddress(DynHook* pHook, void* pKey);

        /* ---- code generation ---- */

        void EmitSaveRegisters(x64JitWriter& jit);
        void EmitRestoreRegisters(x64JitWriter& jit);
        void EmitCall(x64JitWriter& jit, uint64_t function, uint64_t arg0, uint64_t arg1);
        void EmitBridge(DynHook* pHook);
        void EmitPostCallback(DynHook* pHook);
    };

    DynHook::DynHook(void* pFunction, const Prototype& proto)
        : m_pFunction(pFunction), m_Proto(proto), m_pImpl(std::make_unique<Impl>(m_Proto))
    {
        m_pImpl->EmitPostCallback(this);
        m_pImpl->EmitBridge(this);

        if (!m_pImpl->pBridge || !m_pImpl->pPostCallback)
        {
            FP_ERROR("dynhooks: could not generate the bridge for {}", pFunction);
            return;
        }

        auto result = safetyhook::InlineHook::create(pFunction, m_pImpl->pBridge, safetyhook::InlineHook::Flags::StartDisabled);
        if (!result)
        {
            FP_ERROR("dynhooks: could not detour {} (safetyhook error {})", pFunction, static_cast<int>(result.error().type));
            return;
        }

        m_pImpl->detour = std::move(result.value());
        m_pImpl->pTrampoline = m_pImpl->detour.original<void*>();
        m_pImpl->detour.enable();
        m_bValid = true;
    }

    DynHook::~DynHook()
    {
        if (m_pImpl->detour.enabled())
            m_pImpl->detour.disable();
    }

    size_t DynHook::ArgCount() const { return m_pImpl->convention.ArgCount(); }
    void* DynHook::ArgPtr(size_t index) { return m_pImpl->convention.ArgPtr(index); }
    void DynHook::ArgChanged(size_t index) { m_pImpl->convention.ArgChanged(index); }
    void* DynHook::ReturnPtr() { return m_pImpl->convention.ReturnPtr(); }
    void DynHook::ReturnChanged() { m_pImpl->convention.ReturnChanged(); }

    int DynHook::AddHandler(HookType type, Handler handler, int owner)
    {
        const int id = s_NextHandlerId++;
        m_pImpl->handlers.push_back({ id, owner, type, std::move(handler) });
        return id;
    }

    bool DynHook::RemoveHandler(int id)
    {
        auto& handlers = m_pImpl->handlers;
        const size_t before = handlers.size();
        std::erase_if(handlers, [id](const HandlerEntry& entry) { return entry.id == id; });
        return handlers.size() != before;
    }

    void DynHook::RemoveAllForOwner(int owner)
    {
        std::erase_if(m_pImpl->handlers, [owner](const HandlerEntry& entry) { return entry.owner == owner; });
    }

    bool DynHook::HasHandlers() const
    {
        return !m_pImpl->handlers.empty();
    }

    /* =========================
    Dispatch
    ========================= */

    ReturnAction DynHook::Impl::Dispatch(DynHook* pHook, int typeValue)
    {
        Impl& impl = *pHook->m_pImpl;
        const auto type = static_cast<HookType>(typeValue);

        // The snapshot is one per hook; a call from another thread would
        // trample the one in flight. Same rule DHooks has.
        if (std::this_thread::get_id() != s_MainThread)
            return ReturnAction::Ignored;

        impl.convention.SetPhase(type);

        if (type == HookType::Post)
        {
            if (impl.frames.empty())
                return ReturnAction::Ignored;

            CallFrame frame = std::move(impl.frames.back());
            impl.frames.pop_back();

            // What the pre pass decided the return value is, back where the
            // handlers -- and then the caller -- see it.
            if (frame.preAction >= ReturnAction::Override)
                impl.convention.RestoreReturn(frame.ret);

            impl.convention.RestoreArgs(frame.args);
        }

        ReturnAction action = ReturnAction::Ignored;

        // Over a copy: a handler can remove itself or add another.
        const std::vector<HandlerEntry> handlers = impl.handlers;
        for (const HandlerEntry& entry : handlers)
        {
            if (entry.type != type)
                continue;

            const ReturnAction result = entry.fn(*pHook, type);
            if (result > action)
                action = result;
        }

        if (type == HookType::Pre)
        {
            CallFrame frame;
            frame.preAction = action;
            frame.args = impl.convention.SaveArgs();
            if (action >= ReturnAction::Override)
                frame.ret = impl.convention.SaveReturn();
            impl.frames.push_back(std::move(frame));
        }

        return action;
    }

    void DynHook::Impl::StoreReturnAddress(DynHook* pHook, void* pReturnAddress, void* pKey)
    {
        pHook->m_pImpl->returnAddresses[pKey].push_back(pReturnAddress);
    }

    void* DynHook::Impl::TakeReturnAddress(DynHook* pHook, void* pKey)
    {
        auto& map = pHook->m_pImpl->returnAddresses;
        auto it = map.find(pKey);
        if (it == map.end() || it->second.empty())
        {
            // Only reachable when the prototype misdescribes the function
            // and the stack is not where it should be. Nothing sane to do.
            FP_CRITICAL("dynhooks: lost the return address of {} -- the prototype does not match the function", pHook->m_pFunction);
            std::abort();
        }

        void* pReturnAddress = it->second.back();
        it->second.pop_back();
        if (it->second.empty())
            map.erase(it);

        return pReturnAddress;
    }

    /* =========================
    Code generation
    ========================= */

    // Snapshots every register into `snapshot`. rax and r8 are the scratch
    // registers and go last, from copies pushed on entry. rsp is recorded
    // as it was before anything was pushed: the entry rsp, whose slot holds
    // the return address. Flags are left alone.
    void DynHook::Impl::EmitSaveRegisters(x64JitWriter& jit)
    {
        static const x86_64_Reg kGp[] = { rcx, rdx, rbx, rbp, rsi, rdi, r9, r10, r11, r12, r13, r14, r15 };
        static const x8664Reg kGpIndex[] = { RCX, RDX, RBX, RBP, RSI, RDI, R9, R10, R11, R12, R13, R14, R15 };
        static const x86_64_FloatReg kXmm[] = { xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7 };

        jit.push(rax);
        jit.push(r8);

        for (size_t i = 0; i < std::size(kGp); ++i)
        {
            jit.mov(rax, reinterpret_cast<uint64_t>(&snapshot.gp[kGpIndex[i]]));
            jit.mov(rax(), kGp[i]);
        }

        for (int i = 0; i < kSavedXmmCount; ++i)
        {
            jit.mov(rax, reinterpret_cast<uint64_t>(snapshot.xmm[i]));
            jit.movsd(rax(), kXmm[i]);
        }

        // rsp: two pushes above, so the entry value is rsp + 16.
        jit.lea(r8, rsp(16));
        jit.mov(rax, reinterpret_cast<uint64_t>(&snapshot.gp[RSP]));
        jit.mov(rax(), r8);

        // r8 and rax themselves, from the pushed copies.
        jit.mov(rax, reinterpret_cast<uint64_t>(&snapshot.gp[R8]));
        jit.mov(r8, rsp());
        jit.mov(rax(), r8);

        jit.mov(rax, reinterpret_cast<uint64_t>(&snapshot.gp[RAX]));
        jit.mov(r8, rsp(8));
        jit.mov(rax(), r8);

        jit.pop(r8);
        jit.pop(rax);
    }

    // The reverse; rsp is left alone. Flags are not touched, so a compare
    // made before this survives it.
    void DynHook::Impl::EmitRestoreRegisters(x64JitWriter& jit)
    {
        static const x86_64_Reg kGp[] = { rcx, rdx, rbx, rbp, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15 };
        static const x8664Reg kGpIndex[] = { RCX, RDX, RBX, RBP, RSI, RDI, R8, R9, R10, R11, R12, R13, R14, R15 };
        static const x86_64_FloatReg kXmm[] = { xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7 };

        for (size_t i = 0; i < std::size(kGp); ++i)
        {
            jit.mov(rax, reinterpret_cast<uint64_t>(&snapshot.gp[kGpIndex[i]]));
            jit.mov(kGp[i], rax());
        }

        for (int i = 0; i < kSavedXmmCount; ++i)
        {
            jit.mov(rax, reinterpret_cast<uint64_t>(snapshot.xmm[i]));
            jit.movsd(kXmm[i], rax());
        }

        jit.mov(rax, reinterpret_cast<uint64_t>(&snapshot.gp[RAX]));
        jit.mov(rax, rax());
    }

    // Calls a C++ function with two integer arguments from a point where
    // rsp is the entry rsp (8 off a 16-byte boundary, the return address
    // having been pushed), realigning around the call. Result in rax.
    void DynHook::Impl::EmitCall(x64JitWriter& jit, uint64_t function, uint64_t arg0, uint64_t arg1)
    {
#if DYNHOOKS_MS_ABI
        jit.sub(rsp, 40); // 32 bytes of shadow space, 8 to realign
        jit.mov(rcx, arg0);
        jit.mov(rdx, arg1);
#else
        jit.sub(rsp, 8);
        jit.mov(rdi, arg0);
        jit.mov(rsi, arg1);
#endif
        jit.mov(rax, function);
        jit.call(rax);
#if DYNHOOKS_MS_ABI
        jit.add(rsp, 40);
#else
        jit.add(rsp, 8);
#endif
    }

    void DynHook::Impl::EmitBridge(DynHook* pHook)
    {
        x64JitWriter& jit = bridge;

        // On entry: rsp -> the return address into the caller (the key for
        // this call), registers as the caller loaded them.
        EmitSaveRegisters(jit);

        // Swap the return address for the post callback, remembering the
        // real one under the entry rsp. Same shape as EmitCall, with the
        // third argument; the entry rsp is read past the realignment.
#if DYNHOOKS_MS_ABI
        jit.sub(rsp, 40);
        jit.mov(rcx, reinterpret_cast<uint64_t>(pHook));
        jit.mov(rdx, rsp(40));
        jit.lea(r8, rsp(40));
#else
        jit.sub(rsp, 8);
        jit.mov(rdi, reinterpret_cast<uint64_t>(pHook));
        jit.mov(rsi, rsp(8));
        jit.lea(rdx, rsp(8));
#endif
        jit.mov(rax, reinterpret_cast<uint64_t>(&Impl::StoreReturnAddress));
        jit.call(rax);
#if DYNHOOKS_MS_ABI
        jit.add(rsp, 40);
#else
        jit.add(rsp, 8);
#endif

        jit.mov(rax, reinterpret_cast<uint64_t>(pPostCallback));
        jit.mov(rsp(), rax);

        // Pre handlers. The compare has to happen before the registers come
        // back, since that clobbers rax; the flags survive the restore.
        EmitCall(jit, reinterpret_cast<uint64_t>(&Impl::Dispatch), reinterpret_cast<uint64_t>(pHook), static_cast<uint64_t>(HookType::Pre));
        jit.cmp(rax, static_cast<int32_t>(ReturnAction::Supercede));
        EmitRestoreRegisters(jit);

        jit.je(0);
        const uint32_t jumpOffset = jit.get_outputpos();

        // Not superseded: into the original through the trampoline, by a
        // `ret` so no register is disturbed. The slot made below holds the
        // trampoline address; the original then returns to the post
        // callback swapped in above.
        jit.sub(rsp, 8);
        jit.push(rax);
        jit.mov(rax, reinterpret_cast<uint64_t>(&pTrampoline));
        jit.mov(rax, rax());
        jit.mov(rsp(8), rax);
        jit.pop(rax);
        jit.retn();

        // Superseded: skip the original. This `ret` pops the swapped
        // address, so the post handlers still run and then the caller gets
        // the value the pre handler put in the return register.
        jit.rewrite<int32_t>(jumpOffset - sizeof(int32_t), static_cast<int32_t>(jit.get_outputpos() - jumpOffset));
        jit.retn();

        pBridge = jit.GetData();
        jit.SetRE();
    }

    void DynHook::Impl::EmitPostCallback(DynHook* pHook)
    {
        x64JitWriter& jit = postCallback;

        // The original's `ret` popped the swapped address, so rsp is the
        // entry rsp + 8. Back to the entry rsp: the snapshot and the return
        // address key then agree with the pre pass.
        jit.sub(rsp, 8);

        EmitSaveRegisters(jit);
        EmitCall(jit, reinterpret_cast<uint64_t>(&Impl::Dispatch), reinterpret_cast<uint64_t>(pHook), static_cast<uint64_t>(HookType::Post));
        EmitRestoreRegisters(jit);

        // rax is the return value now and has to survive the lookup of the
        // real return address, keyed by the entry rsp. It sits on the stack
        // for the call; the address found goes into the entry slot, which
        // the final `ret` pops -- leaving rsp at entry + 8, exactly what the
        // original's own `ret` would have left.
        jit.push(rax);
#if DYNHOOKS_MS_ABI
        jit.sub(rsp, 32);
        jit.mov(rcx, reinterpret_cast<uint64_t>(pHook));
        jit.lea(rdx, rsp(40));
#else
        jit.mov(rdi, reinterpret_cast<uint64_t>(pHook));
        jit.lea(rsi, rsp(8));
#endif
        jit.mov(rax, reinterpret_cast<uint64_t>(&Impl::TakeReturnAddress));
        jit.call(rax);
#if DYNHOOKS_MS_ABI
        jit.add(rsp, 32);
#endif
        jit.mov(rsp(8), rax);
        jit.pop(rax);
        jit.retn();

        pPostCallback = jit.GetData();
        jit.SetRE();
    }

    /* =========================
    Manager
    ========================= */

    DynHook* Manager::Hook(void* pFunction, const Prototype& proto, std::string* pError)
    {
        if (!pFunction)
        {
            if (pError) *pError = "null function address";
            return nullptr;
        }

        if (DynHook* pExisting = Find(pFunction))
        {
            if (!(pExisting->Proto() == proto))
            {
                if (pError) *pError = "the function is already hooked with a different prototype";
                return nullptr;
            }

            return pExisting;
        }

        std::unique_ptr<DynHook> pHook(new DynHook(pFunction, proto));
        if (!pHook->IsValid())
        {
            if (pError) *pError = "could not detour the function";
            return nullptr;
        }

        m_Hooks.push_back(std::move(pHook));
        return m_Hooks.back().get();
    }

    DynHook* Manager::Find(void* pFunction)
    {
        for (auto& pHook : m_Hooks)
        {
            if (pHook->Function() == pFunction)
                return pHook.get();
        }

        return nullptr;
    }

    bool Manager::RemoveHandler(int id)
    {
        for (auto it = m_Hooks.begin(); it != m_Hooks.end(); ++it)
        {
            if (!(*it)->RemoveHandler(id))
                continue;

            if (!(*it)->HasHandlers())
                m_Hooks.erase(it);

            return true;
        }

        return false;
    }

    void Manager::RemoveAllForOwner(int owner)
    {
        for (auto& pHook : m_Hooks)
            pHook->RemoveAllForOwner(owner);

        std::erase_if(m_Hooks, [](const std::unique_ptr<DynHook>& pHook) { return !pHook->HasHandlers(); });
    }

    void Manager::Shutdown()
    {
        m_Hooks.clear();
    }
}
