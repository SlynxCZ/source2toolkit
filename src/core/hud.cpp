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
#include "hud.h"

#include "coreconfig.h"
#include "customhud.h"
#include "menus.h"
#include "shared.h"
#include "tkvprof.h"
#include "utils/log.h"

#include "source2toolkit/schema/entity/classes/CCSCustomHudLayout.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController.h"

#include <algorithm>
#include <cmath>

namespace hud
{
    HudManager hudManager;

    namespace
    {
        // The id contract of IToolkitHud.h, in HudSlot order.
        constexpr const char* kSlotPanel[] = {
            "hud_top", "hud_topleft", "hud_topright", "hud_left", "hud_right", "hud_center", "hud_bottom", "hud_panel",
        };
        static_assert(sizeof(kSlotPanel) / sizeof(kSlotPanel[0]) == static_cast<size_t>(HudSlot::Count));

        constexpr const char* kSlotLabel[] = {
            "hud_top_text", "hud_topleft_text", "hud_topright_text", "hud_left_text", "hud_right_text", "hud_center_text",
            "hud_bottom_text", "hud_panel_text",
        };

        constexpr const char* kColorClass[] = {
            "c-white", "c-red", "c-green", "c-blue", "c-yellow", "c-orange", "c-purple", "c-cyan", "c-grey",
        };
        static_assert(sizeof(kColorClass) / sizeof(kColorClass[0]) == static_cast<size_t>(HudColor::Count));

        constexpr const char* kSizeClass[] = { "s-small", "s-normal", "s-large", "s-huge" };
        static_assert(sizeof(kSizeClass) / sizeof(kSizeClass[0]) == static_cast<size_t>(HudSize::Count));

        // w0 .. w20: the bar's fill in 5 % steps, one class each (clip in the
        // stylesheet, which does not restart like a width transition would).
        constexpr const char* kBarClass[] = {
            "w0", "w1", "w2", "w3", "w4", "w5", "w6", "w7", "w8", "w9", "w10",
            "w11", "w12", "w13", "w14", "w15", "w16", "w17", "w18", "w19", "w20",
        };
        static_assert(sizeof(kBarClass) / sizeof(kBarClass[0]) == HudManager::kBarSteps + 1);

        constexpr const char* kShow = "show";

        float Now()
        {
            CGlobalVars* globals = shared::getGlobalVars();
            return globals ? globals->curtime : 0.0f;
        }

        int SlotOf(CCSPlayerController* player)
        {
            if (!player)
                return -1;

            const int slot = player->GetPlayerSlot().Get();
            return slot >= 0 && slot < HudManager::kMaxPlayers ? slot : -1;
        }
    }

    // ---- setup ---------------------------------------------------------------

    void HudManager::Init()
    {
        m_text.name = shared::g_pCoreConfig ? shared::g_pCoreConfig->HudTextLayout : "s2t_hud";
        m_text.targetName = "s2t_hud_text";

        m_menu.name = shared::g_pCoreConfig ? shared::g_pCoreConfig->HudMenuLayout : "s2t_menu";
        m_menu.targetName = "s2t_hud_menu";
        m_menu.onCreated = [](CCSCustomHudLayout* layout)
        {
            // Owner 0 is the core: the callback is never dropped for a plugin
            // unload, only with the entity (level shutdown, Clear()).
            customhud::customHudManager.HookCustomHudClick(0, layout,
                [](CCSPlayerController* player, CCSCustomHudLayout*, const char* buttonId)
                {
                    menus::menuManager.OnHudClick(player, buttonId);
                });
        };
    }

    CCSCustomHudLayout* HudManager::Ensure(OwnedLayout& layout)
    {
        if (CCSCustomHudLayout* existing = layout.handle.Get())
            return existing;

        if (layout.failed || layout.name.empty())
            return nullptr;

        // No entities before the map's game rules exist.
        if (!shared::getGlobalVars() || !shared::g_pGameRules)
            return nullptr;

        CCSCustomHudLayout* created = CCSCustomHudLayout::Create(layout.name.c_str(), layout.targetName);
        if (!created)
        {
            layout.failed = true;
            FP_ERROR("custom_hud_layout '{}' could not be spawned; HUD texts and menus are off until the next map", layout.name);
            return nullptr;
        }

        layout.handle = created->GetHandle();
        FP_INFO("custom_hud_layout '{}' spawned ({})", layout.name, layout.targetName ? layout.targetName : "");

        if (layout.onCreated)
            layout.onCreated(created);

        return created;
    }

    CCSCustomHudLayout* HudManager::TextLayout()
    {
        return Ensure(m_text);
    }

    CCSCustomHudLayout* HudManager::MenuLayout()
    {
        return Ensure(m_menu);
    }

    CCSCustomHudLayout* HudManager::MenuLayoutIfAny()
    {
        return m_menu.handle.Get();
    }

    HudManager::PlayerState* HudManager::StateOf(CCSPlayerController* player)
    {
        const int slot = SlotOf(player);
        return slot < 0 ? nullptr : &m_players[slot];
    }

    void HudManager::ResetState(PlayerState& state)
    {
        state = PlayerState{};
    }

    void HudManager::SetVariant(CCSCustomHudLayout* layout, CCSPlayerController* player, const char* panel,
                                const char* const* classes, int count, int& current, int wanted)
    {
        if (wanted < 0 || wanted >= count)
            wanted = 0;

        if (current == wanted)
            return;

        if (current >= 0 && current < count)
            layout->SetHasClass(panel, classes[current], false, player);

        layout->SetHasClass(panel, classes[wanted], true, player);
        current = wanted;
    }

    // ---- IToolkitHud ---------------------------------------------------------

    bool HudManager::IsAvailable()
    {
        return TextLayout() != nullptr;
    }

    const char* HudManager::LayoutName()
    {
        return m_text.name.c_str();
    }

    void HudManager::ShowText(CCSPlayerController* player, HudSlot slot, const char* text, float seconds, HudTextStyle style)
    {
        const int index = static_cast<int>(slot);
        if (index < 0 || index >= static_cast<int>(HudSlot::Count) || !text)
            return;

        PlayerState* state = StateOf(player);
        CCSCustomHudLayout* layout = TextLayout();
        if (!state || !layout)
            return;

        SlotState& s = state->slots[index];

        SetVariant(layout, player, kSlotPanel[index], kColorClass, static_cast<int>(HudColor::Count), s.color, static_cast<int>(style.color));
        SetVariant(layout, player, kSlotPanel[index], kSizeClass, static_cast<int>(HudSize::Count), s.size, static_cast<int>(style.size));

        layout->SetDialogVariableString(kSlotLabel[index], "text", text, player);

        // Always sent, not only on the first show: a client still loading when
        // the class was first set never saw it.
        layout->SetHasClass(kSlotPanel[index], kShow, true, player);
        s.shown = true;
        s.expire = seconds > 0.0f ? Now() + seconds : -1.0f;
    }

    void HudManager::HideText(CCSPlayerController* player, HudSlot slot)
    {
        const int index = static_cast<int>(slot);
        if (index < 0 || index >= static_cast<int>(HudSlot::Count))
            return;

        PlayerState* state = StateOf(player);
        if (!state)
            return;

        SlotState& s = state->slots[index];
        if (!s.shown)
            return;

        s.shown = false;
        s.expire = -1.0f;

        if (CCSCustomHudLayout* layout = m_text.handle.Get())
            layout->SetHasClass(kSlotPanel[index], kShow, false, player);
    }

    void HudManager::ShowPrompt(CCSPlayerController* player, const char* key, const char* text, float progress)
    {
        PlayerState* state = StateOf(player);
        CCSCustomHudLayout* layout = TextLayout();
        if (!state || !layout)
            return;

        layout->SetDialogVariableString("hud_prompt_key", "text", key ? key : "", player);
        layout->SetDialogVariableString("hud_prompt_text", "text", text ? text : "", player);

        if (progress >= 0.0f)
        {
            // (std::min) -- windows.h's min macro would eat the bare name.
            const int step = std::clamp(static_cast<int>(std::lround((std::min)(progress, 1.0f) * kBarSteps)), 0, kBarSteps);
            SetVariant(layout, player, "hud_prompt_bar", kBarClass, kBarSteps + 1, state->barStep, step);

            if (!state->bar)
            {
                layout->SetHasClass("hud_prompt_barwrap", kShow, true, player);
                state->bar = true;
            }
        }
        else if (state->bar)
        {
            layout->SetHasClass("hud_prompt_barwrap", kShow, false, player);
            state->bar = false;
        }

        layout->SetHasClass("hud_prompt", kShow, true, player);
        state->prompt = true;
    }

    void HudManager::HidePrompt(CCSPlayerController* player)
    {
        PlayerState* state = StateOf(player);
        if (!state || !state->prompt)
            return;

        state->prompt = false;

        if (CCSCustomHudLayout* layout = m_text.handle.Get())
        {
            layout->SetHasClass("hud_prompt", kShow, false, player);

            if (state->bar)
                layout->SetHasClass("hud_prompt_barwrap", kShow, false, player);
        }

        state->bar = false;
    }

    void HudManager::HideAll(CCSPlayerController* player)
    {
        for (int i = 0; i < static_cast<int>(HudSlot::Count); ++i)
            HideText(player, static_cast<HudSlot>(i));

        HidePrompt(player);
    }

    // ---- core ----------------------------------------------------------------

    void HudManager::Tick()
    {
        TK_VPROF("Source2Toolkit::HudTick");

        if (!m_text.handle.Get())
            return;

        const float now = Now();

        for (int slot = 0; slot < kMaxPlayers; ++slot)
        {
            PlayerState& state = m_players[slot];
            CCSPlayerController* player = nullptr;

            for (int i = 0; i < static_cast<int>(HudSlot::Count); ++i)
            {
                SlotState& s = state.slots[i];
                if (!s.shown || s.expire < 0.0f || now < s.expire)
                    continue;

                if (!player)
                    player = CCSPlayerController::FromSlot(slot);

                if (player)
                    HideText(player, static_cast<HudSlot>(i));
                else
                    s = SlotState{};
            }
        }
    }

    void HudManager::OnClientDisconnect(CPlayerSlot slot)
    {
        const int index = slot.Get();
        if (index < 0 || index >= kMaxPlayers)
            return;

        // The controller is still there on the disconnect callback, so the
        // entity's per-slot state can be cleared for the next occupant.
        if (CCSPlayerController* player = CCSPlayerController::FromSlot(index))
        {
            HideAll(player);

            if (CCSCustomHudLayout* layout = m_text.handle.Get())
            {
                // The colour and size classes stay interned on the entity;
                // whatever is on gets switched off with the panel hidden, so
                // nothing needs undoing here beyond the local record.
                (void)layout;
            }
        }

        ResetState(m_players[index]);
    }

    void HudManager::Clear()
    {
        m_text.handle = nullptr;
        m_text.failed = false;
        m_menu.handle = nullptr;
        m_menu.failed = false;

        for (PlayerState& state : m_players)
            ResetState(state);
    }
}
