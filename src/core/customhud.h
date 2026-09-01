/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
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
 * As a special exception, Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl and
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
 *   - Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl
 *   - AlliedModders LLC
 *
 * Project: Source2Toolkit
 */
#pragma once
#include "source2toolkit/IToolkitCustomHud.h"

#include "ehandle.h"

#include <vector>

class CCSCustomHudLayout;
class CCSPlayerController;

namespace customhud {
    /// CS_UM_CustomHudClicked, the user message a client sends when it clicks a
    /// panel of a custom_hud_layout it has input capture on.
    inline constexpr int CS_UM_CustomHudClicked = 390;

    struct ClickCallbackEntry
    {
        PluginId owner;
        CHandle<CCSCustomHudLayout> layout;
        CustomHudClickHandler handler;
    };

    class CustomHudManager : public IToolkitCustomHud {
    public:
        void HookCustomHudClick(PluginId owner, CCSCustomHudLayout* pLayout, CustomHudClickHandler handler) override;
        void UnhookCustomHudClick(CCSCustomHudLayout* pLayout) override;
    public:
        /// Routes one CS_UM_CustomHudClicked payload to the callbacks of the
        /// layout it names. Stale entries are dropped on the way through.
        void HandleClick(CCSPlayerController* pController, const void* pBuffer, uint32 nSize);

        /// A callback outlives neither its plugin nor the entity it points at:
        /// the handler is a std::function holding code inside the plugin's
        /// library, so it has to go before that library is closed.
        void RemoveAllForPlugin(PluginId id);
        void Clear();
    protected:
        std::vector<ClickCallbackEntry> m_callbacks;
    };

    extern CustomHudManager customHudManager;
}
