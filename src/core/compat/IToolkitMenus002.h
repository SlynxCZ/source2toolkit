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

/**
 * IToolkitMenus002, as the SDK shipped it up to core v1.0.28: the four
 * methods before OpenHudMenu was appended. CenterHtmlMenu and IMenuInstance
 * did not change, so the current header's types serve. Handed to plugins
 * built against the 002 header; see compat.h.
 */

#include "source2toolkit/IToolkitMenus.h"

namespace compat
{
    class IToolkitMenus_002
    {
    public:
        virtual ~IToolkitMenus_002() = default;
        virtual void OpenCenterHtmlMenu(PluginId owner, CCSPlayerController* player, CenterHtmlMenu* menu) = 0;
        virtual IMenuInstance* GetActiveMenu(CCSPlayerController* player) = 0;
        virtual void CloseActiveMenu(CCSPlayerController* player) = 0;
        virtual void OnKeyPress(CCSPlayerController* player, int key) = 0;
    };

    class Menus002 final : public IToolkitMenus_002
    {
    public:
        void OpenCenterHtmlMenu(PluginId owner, CCSPlayerController* player, CenterHtmlMenu* menu) override;
        IMenuInstance* GetActiveMenu(CCSPlayerController* player) override;
        void CloseActiveMenu(CCSPlayerController* player) override;
        void OnKeyPress(CCSPlayerController* player, int key) override;
    };

    extern Menus002 menus002;
}
