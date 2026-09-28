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

#include "playerslot.h"

namespace menus {
    // AddMenuOptionWithCooldown lives in IBaseMenu now, so the local
    // BaseMenu that used to supply it is gone.

    class CenterHtmlMenuInstance : public IMenuInstance
    {
    public:
        CenterHtmlMenuInstance(CCSPlayerController *player, CenterHtmlMenu *menu, uint64_t serial)
            : IMenuInstance(player, menu), chMenu_(menu), serial_(serial)
        {
        }

        void Display() override;
        void OnKeyPress(CCSPlayerController* player, int key) override;
        void Close() override;

    protected:
        int NumPerPage() const override { return 5; }

        int MenuItemsPerPage() const override
        {
            const bool exit = HasExitButton();
            const bool both = HasPrevButton() && HasNextButton();
            return (exit ? 0 : 1) + (both ? (NumPerPage() - 1) : NumPerPage());
        }

        // Hides IMenuInstance::HasNextButton, which counts NumPerPage() items
        // per page and misses the extra slot a menu without an exit button
        // gets in MenuItemsPerPage(). With exactly six options left it showed
        // all six plus a Next that led to an empty page. Kept out of the SDK
        // header so IMenuInstance stays as plugins were built against it.
        bool HasNextButton() const
        {
            const int remaining = static_cast<int>(menu_->Options().size()) - currentOffset_;
            return remaining > (HasExitButton() ? 0 : 1) + NumPerPage();
        }

    private:
        CenterHtmlMenu *chMenu_;

        /// Which opening of a menu this is, see MenuManager::IsOpen.
        uint64_t serial_;
    };

    /// A HudMenu on the core's menu layout (hud::HudManager::MenuLayout):
    /// six rows, the navigation buttons, per-player state on one entity.
    class HudMenuInstance : public IMenuInstance
    {
    public:
        static constexpr int kRows = 6;

        /// `readCapture`: whether the menu object has the CaptureInput field
        /// (IToolkitMenus004); a 003 object is shorter and means capture on.
        HudMenuInstance(CCSPlayerController* player, HudMenu* menu, uint64_t serial, bool readCapture);
        ~HudMenuInstance() override;

        void Display() override;
        void OnKeyPress(CCSPlayerController* player, int key) override;
        void Close() override;

        /// Once a frame. A HUD menu does not fade, so it is not redrawn every
        /// frame like the center HTML one; this runs the DisabledEvaluators
        /// and redraws only when what would be drawn changed -- which also
        /// covers a menu rebuilt in place from one of its handlers.
        void Refresh();

    protected:
        int NumPerPage() const override { return kRows; }

    public:
        /// Whether this menu took the mouse: then the rows are clicked and
        /// the number keys are not it.
        bool CaptureInput() const { return readCapture_ ? hudMenu_->CaptureInput : true; }

    private:
        /// Hides the layout for the player; the destructor's job, so a
        /// closed, replaced or unloaded menu never stays on screen.
        void Hide();

        /// What Display() would draw, hashed: title, page, rows, states.
        size_t Signature() const;

        int Position() const { return readCapture_ ? static_cast<int>(hudMenu_->Position) : 0; }

        HudMenu* hudMenu_;
        uint64_t serial_;
        int slot_;
        bool readCapture_;
        size_t drawn_ = 0;
        /// The pos-* class last put on menu_root for this player; -1 for none yet.
        int drawnPos_ = -1;
    };

    class MenuManager : public IToolkitMenus
    {
    public:
        void OpenCenterHtmlMenu(PluginId owner, CCSPlayerController *player, CenterHtmlMenu *menu) override;
        IMenuInstance *GetActiveMenu(CCSPlayerController *player) override;
        void CloseActiveMenu(CCSPlayerController *player) override;
        void OnKeyPress(CCSPlayerController *player, int key) override;
        void OpenHudMenu(PluginId owner, CCSPlayerController* player, HudMenu* menu) override;
    public:
        /// OpenHudMenu with a say on whether `menu` carries CaptureInput (the
        /// IToolkitMenus003 adapter passes false: its HudMenu ends before it).
        void OpenHudMenuEx(PluginId owner, CCSPlayerController* player, HudMenu* menu, bool readCapture);

        /// The plugin whose menu the player has open, 0 for none.
        PluginId OwnerOf(CCSPlayerController* player) const;

        void Tick();

        /// A click on the menu layout (hud::HudManager routes it here): the
        /// button id becomes the key the row or navigation button stands for.
        void OnHudClick(CCSPlayerController* player, const char* buttonId);

        /// Closes the player's menu while the controller still exists, so a
        /// HUD menu can hide itself and the next occupant of the slot does
        /// not inherit it.
        void OnClientDisconnect(CPlayerSlot slot);

        /// Closes whatever this plugin still has open. The menu object and the
        /// option handlers behind it live inside its library, so a menu left
        /// on someone's screen is a key press away from a closed library.
        void RemoveAllForPlugin(PluginId id);

        /// Whether the menu opened under this serial is still the one the
        /// player has open. An option handler can close its menu or open
        /// another one, which destroys the instance it was called from, and
        /// the next instance often gets the same address back from the
        /// allocator, so comparing pointers is not enough.
        bool IsOpen(CCSPlayerController *player, uint64_t serial) const;

    protected:
        struct ActiveMenu
        {
            PluginId owner = 0;
            uint64_t serial = 0;
            std::unique_ptr<IMenuInstance> instance;
            /// A HudMenuInstance, refreshed instead of redrawn in Tick().
            bool hud = false;
        };

        std::unordered_map<int, ActiveMenu> activeMenus;
        uint64_t nextSerial_ = 0;

        /// (slot, serial) pairs Tick() walks, kept to avoid a per-frame allocation.
        std::vector<std::pair<int, uint64_t>> tickSnapshot_;
    };

    extern MenuManager menuManager;
}
