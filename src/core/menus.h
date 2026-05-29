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
#include "source2toolkit/IToolkitMenus.h"

namespace menus {
    class BaseMenu : public IBaseMenu
    {
    public:
        ChatMenuOption &AddMenuOptionWithCooldown(
                std::string optionText,
                std::function<void(ICSPlayerController *, ChatMenuOption &)> action,
                bool disabled = false,
                bool close = true,
                std::function<bool()> disabledEvaluator = nullptr) override;
    };

    class CenterHtmlMenuInstance : public IMenuInstance
    {
    public:
        CenterHtmlMenuInstance(ICSPlayerController *player, CenterHtmlMenu *menu)
            : IMenuInstance(player, menu), chMenu_(menu)
        {
        }

        void Display() override;
        void OnKeyPress(ICSPlayerController* player, int key) override;
        void Close() override;

    protected:
        int NumPerPage() const override { return 5; }

        int MenuItemsPerPage() const override
        {
            const bool exit = HasExitButton();
            const bool both = HasPrevButton() && HasNextButton();
            return (exit ? 0 : 1) + (both ? (NumPerPage() - 1) : NumPerPage());
        }

    private:
        CenterHtmlMenu *chMenu_;
    };

    class MenuManager : public IToolkitMenus
    {
    public:
        void OpenCenterHtmlMenu(ICSPlayerController *player, CenterHtmlMenu *menu) override;
        IMenuInstance *GetActiveMenu(ICSPlayerController *player) override;
        void CloseActiveMenu(ICSPlayerController *player) override;
        void OnKeyPress(ICSPlayerController *player, int key) override;
    public:
        void Tick();
    protected:
        std::unordered_map<int, std::unique_ptr<IMenuInstance>> activeMenus;
    };

    extern MenuManager menuManager;
}
