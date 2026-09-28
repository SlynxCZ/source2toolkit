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
#include "source2toolkit/IToolkitHud.h"

#include "ehandle.h"
#include "playerslot.h"

#include <functional>
#include <string>

class CCSCustomHudLayout;
class CCSPlayerController;

namespace hud
{
    /// One custom_hud_layout the core owns: created on first use once a map
    /// runs, gone with the map, never recreated after a failure until the
    /// next map (the failure is logged once).
    struct OwnedLayout
    {
        std::string name;
        const char* targetName = nullptr;
        CHandle<CCSCustomHudLayout> handle;
        bool failed = false;
        /// Runs right after a fresh entity spawned.
        std::function<void(CCSCustomHudLayout*)> onCreated;
    };

    class HudManager final : public IToolkitHud
    {
    public:
        static constexpr int kMaxPlayers = 64;
        static constexpr int kBarSteps = 20;

        // IToolkitHud
        bool IsAvailable() override;
        void ShowText(CCSPlayerController* player, HudSlot slot, const char* text, float seconds, HudTextStyle style) override;
        void HideText(CCSPlayerController* player, HudSlot slot) override;
        void ShowPrompt(CCSPlayerController* player, const char* key, const char* text, float progress) override;
        void HidePrompt(CCSPlayerController* player) override;
        void HideAll(CCSPlayerController* player) override;
        const char* LayoutName() override;

        // core
        void Init();

        /// The text layout, spawned if it can be; null without a map or after
        /// a failed spawn.
        CCSCustomHudLayout* TextLayout();

        /// The menu layout (HudMenuLayout in core.json), same rules. Clicks on
        /// it go to MenuManager::OnHudClick.
        CCSCustomHudLayout* MenuLayout();

        /// The menu layout only if it already exists -- for closing.
        CCSCustomHudLayout* MenuLayoutIfAny();

        /// Once a frame: texts whose time is up go away.
        void Tick();

        /// The slot's state is reset so the next occupant does not inherit it.
        void OnClientDisconnect(CPlayerSlot slot);

        /// Level shutdown: the entities are gone, forget them and every state.
        void Clear();

    private:
        struct SlotState
        {
            bool shown = false;
            float expire = -1.0f;
            int color = -1;
            int size = -1;
        };

        struct PlayerState
        {
            SlotState slots[static_cast<int>(HudSlot::Count)];
            bool prompt = false;
            bool bar = false;
            int barStep = -1;
        };

        CCSCustomHudLayout* Ensure(OwnedLayout& layout);
        PlayerState* StateOf(CCSPlayerController* player);
        void ResetState(PlayerState& state);

        /// Swaps one class of a family (c-*, s-*, w*) on a panel: the old one
        /// off, the new one on. `current` remembers which is on.
        void SetVariant(CCSCustomHudLayout* layout, CCSPlayerController* player, const char* panel,
                        const char* const* classes, int count, int& current, int wanted);

        OwnedLayout m_text;
        OwnedLayout m_menu;
        PlayerState m_players[kMaxPlayers];
    };

    extern HudManager hudManager;
}
