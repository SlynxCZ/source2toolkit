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

#include <chrono>
#include <cstddef>
#include <mutex>
#include <set>
#include <vector>

// KHook, via metamod.
#include "ISmmPlugin.h"

/// KHook as one .stx plugin sees it. Every call goes on to the engine's, and
/// on the way through the ids the plugin set up and has not taken down are
/// kept, together with a count of the removals it asked for that have not
/// completed yet. When the plugin is unloaded, BeginClose() takes whatever it
/// left hooked out asynchronously, and PluginManager::Tick() closes the
/// library only once IsIdle() -- until then KHook's worker thread still runs
/// code that lives in it (a removal callback, at the least).
///
/// Why per plugin rather than the engine's own: metamod does the same for its
/// plugins (its Unloader), but it only sees the toolkit as one plugin, so the
/// hooks of the .stx plugins all land in the toolkit's set there.
class PluginKHook final : public KHook::IKHook
{
public:
    KHook::HookID_t SetupHook(void* function, void* context, void* removed_function, void* pre, void* post, void* make_return, void* make_call_original, unsigned int stack_size, bool async) override;
    KHook::HookID_t SetupVirtualHook(void** vtable, int index, void* context, void* removed_function, void* pre, void* post, void* make_return, void* make_call_original, unsigned int stack_size, bool async) override;
    void RemoveHook(KHook::HookID_t id, bool async, void (*hook_removal_fn)(KHook::HookID_t, void*), void* context) override;

    void* GetContextPtr() override;
    void* GetOriginalFunction() override;
    void* GetOriginalValuePtr() override;
    void* GetOverrideValuePtr() override;
    void* GetCurrentValuePtr(bool pop) override;
    void DestroyReturnValue() override;
    void* FindOriginal(void* function) override;
    void* FindOriginalVirtual(void** vtable, int index) override;
    void* DoRecall(KHook::Action action, void* ptr_to_return, std::size_t return_size, void* init_op, void* deinit_op) override;
    void SaveReturnValue(KHook::Action action, void* ptr_to_return, std::size_t return_size, void* init_op, void* deinit_op, bool original) override;
    void* LookupSignature(void* start, std::size_t size, const char* signature) override;
    bool WasOriginalFunctionSkipped() override;

    /// The plugin's Unload() has run: whatever it left hooked comes out now,
    /// asynchronously, counted like a removal the plugin asked for itself.
    void BeginClose();

    /// True once BeginClose() was called and nothing the plugin hooked is
    /// still hooked or still on its way out.
    bool IsIdle() const;

    /// How long the close has been waiting; for the log line when a removal
    /// KHook never reports (it does not, for an id it no longer knows).
    std::chrono::steady_clock::duration Waiting() const;

private:
    struct Removal
    {
        PluginKHook* self;
        void (*fn)(KHook::HookID_t, void*);
        void* context;
    };

    // On KHook's worker thread.
    static void OnRemoved(KHook::HookID_t id, void* context);

    mutable std::mutex m_mutex;
    std::set<KHook::HookID_t> m_live;
    std::size_t m_nInFlight = 0;
    bool m_bClosing = false;
    std::chrono::steady_clock::time_point m_closeStart{};
};
