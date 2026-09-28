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
#include "pluginkhook.h"

// The engine itself, as metamod handed it to the toolkit.
static KHook::IKHook* Engine()
{
    return KHook::__exported__khook;
}

KHook::HookID_t PluginKHook::SetupHook(void* function, void* context, void* removed_function, void* pre, void* post, void* make_return, void* make_call_original, unsigned int stack_size, bool async)
{
    const auto id = Engine()->SetupHook(function, context, removed_function, pre, post, make_return, make_call_original, stack_size, async);

    if (id != KHook::INVALID_HOOK)
    {
        std::lock_guard guard(m_mutex);
        m_live.insert(id);
    }

    return id;
}

KHook::HookID_t PluginKHook::SetupVirtualHook(void** vtable, int index, void* context, void* removed_function, void* pre, void* post, void* make_return, void* make_call_original, unsigned int stack_size, bool async)
{
    const auto id = Engine()->SetupVirtualHook(vtable, index, context, removed_function, pre, post, make_return, make_call_original, stack_size, async);

    if (id != KHook::INVALID_HOOK)
    {
        std::lock_guard guard(m_mutex);
        m_live.insert(id);
    }

    return id;
}

void PluginKHook::RemoveHook(KHook::HookID_t id, bool async, void (*hook_removal_fn)(KHook::HookID_t, void*), void* context)
{
    {
        std::lock_guard guard(m_mutex);
        m_live.erase(id);
    }

    if (!async)
    {
        // Done by the time this returns, callback included.
        Engine()->RemoveHook(id, false, hook_removal_fn, context);
        return;
    }

    // Completes on KHook's worker thread, where the plugin's callback -- code
    // in its library -- runs as well. Counted, so the library stays mapped
    // until it has.
    auto* removal = new Removal{ this, hook_removal_fn, context };

    {
        std::lock_guard guard(m_mutex);
        ++m_nInFlight;
    }

    Engine()->RemoveHook(id, true, &PluginKHook::OnRemoved, removal);
}

void PluginKHook::OnRemoved(KHook::HookID_t id, void* context)
{
    auto* removal = static_cast<Removal*>(context);

    if (removal->fn)
        removal->fn(id, removal->context);

    PluginKHook* self = removal->self;
    delete removal;

    // Last: once the count is down Tick() may delete this object.
    std::lock_guard guard(self->m_mutex);
    --self->m_nInFlight;
}

void PluginKHook::BeginClose()
{
    std::vector<KHook::HookID_t> leftover;

    {
        std::lock_guard guard(m_mutex);
        m_bClosing = true;
        m_closeStart = std::chrono::steady_clock::now();
        leftover.assign(m_live.begin(), m_live.end());
    }

    for (const KHook::HookID_t id : leftover)
        RemoveHook(id, true, nullptr, nullptr);
}

bool PluginKHook::IsIdle() const
{
    std::lock_guard guard(m_mutex);
    return m_bClosing && m_nInFlight == 0 && m_live.empty();
}

std::chrono::steady_clock::duration PluginKHook::Waiting() const
{
    std::lock_guard guard(m_mutex);
    return std::chrono::steady_clock::now() - m_closeStart;
}

void* PluginKHook::GetContextPtr() { return Engine()->GetContextPtr(); }
void* PluginKHook::GetOriginalFunction() { return Engine()->GetOriginalFunction(); }
void* PluginKHook::GetOriginalValuePtr() { return Engine()->GetOriginalValuePtr(); }
void* PluginKHook::GetOverrideValuePtr() { return Engine()->GetOverrideValuePtr(); }
void* PluginKHook::GetCurrentValuePtr(bool pop) { return Engine()->GetCurrentValuePtr(pop); }
void PluginKHook::DestroyReturnValue() { Engine()->DestroyReturnValue(); }
void* PluginKHook::FindOriginal(void* function) { return Engine()->FindOriginal(function); }
void* PluginKHook::FindOriginalVirtual(void** vtable, int index) { return Engine()->FindOriginalVirtual(vtable, index); }
void* PluginKHook::DoRecall(KHook::Action action, void* ptr_to_return, std::size_t return_size, void* init_op, void* deinit_op) { return Engine()->DoRecall(action, ptr_to_return, return_size, init_op, deinit_op); }
void PluginKHook::SaveReturnValue(KHook::Action action, void* ptr_to_return, std::size_t return_size, void* init_op, void* deinit_op, bool original) { Engine()->SaveReturnValue(action, ptr_to_return, return_size, init_op, deinit_op, original); }
void* PluginKHook::LookupSignature(void* start, std::size_t size, const char* signature) { return Engine()->LookupSignature(start, size, signature); }
bool PluginKHook::WasOriginalFunctionSkipped() { return Engine()->WasOriginalFunctionSkipped(); }
