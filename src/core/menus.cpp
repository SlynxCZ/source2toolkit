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
#include "menus.h"

#include "hud.h"
#include "slowguard.h"

#include "source2toolkit/schema/entity/classes/CCSCustomHudLayout.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <functional>

namespace menus
{
    MenuManager menuManager;

    void CenterHtmlMenuInstance::Display()
    {
        if (!player_ || !menu_) return;

        if (menuManager.GetActiveMenu(player_) != this)
        {
            Reset();
            return;
        }

        // The evaluators are plugin code and may close this menu or open
        // another one for the player, which destroys this instance.
        CCSPlayerController* player = player_;
        const uint64_t serial = serial_;

        auto& options = menu_->Options();
        for (size_t i = 0; i < options.size(); ++i)
        {
            auto& opt = options[i];
            if (!opt.DisabledEvaluator) continue;

            opt.Disabled = opt.DisabledEvaluator();
            if (!menuManager.IsOpen(player, serial)) return;
        }

        const auto& opts = menu_->Options();
        const int total = static_cast<int>(opts.size());

        std::string html;
        html.reserve(512);
        html += "<b><font color='";
        html += chMenu_->TitleColor;
        html += "'>";
        html += chMenu_->Title();
        html += "</font></b><br>\n";

        int keyOffset = 1;
        const int pageEnd = (std::min)(currentOffset_ + MenuItemsPerPage(), total);
        for (int i = currentOffset_; i < pageEnd; ++i)
        {
            const auto& opt = opts[i];
            const std::string& color = opt.Disabled ? chMenu_->DisabledColor : chMenu_->EnabledColor;
            html += "<font color='";
            html += color;
            html += "'>!";
            html += std::to_string(keyOffset++);
            html += "</font> ";
            html += opt.Text;
            html += "<br>\n";
        }

        if (HasPrevButton())
        {
            html += "<font color='";
            html += chMenu_->PrevPageColor;
            html += "'>!7</font> &#60;- Prev<br>\n";
        }
        if (HasNextButton())
        {
            html += "<font color='";
            html += chMenu_->NextPageColor;
            html += "'>!8</font> -> Next<br>\n";
        }
        if (HasExitButton())
        {
            html += "<font color='";
            html += chMenu_->CloseColor;
            html += "'>!9</font> -> Close<br>\n";
        }

        player_->PrintToCenterHtml(html.c_str(), 3, true);
    }

    void CenterHtmlMenuInstance::OnKeyPress(CCSPlayerController* p, int key)
    {
        if (p != player_) return;
        if (!menu_) return;

        // 8 = Next, 7 = Prev, 9 = Close (matches C#)
        if (key == 8 && HasNextButton())
        {
            NextPage();
            return;
        }
        if (key == 7 && HasPrevButton())
        {
            PrevPage();
            return;
        }
        if (key == 9 && HasExitButton())
        {
            Close();
            return;
        }

        // Item keys are only the ones Display() printed for this page. C#
        // accepts 1..9 here, so !6, or !7 without a Prev button, picked an
        // option from the next page that the player never saw.
        if (key < 1 || key > MenuItemsPerPage()) return;

        const int idx = currentOffset_ + (key - 1);
        auto& options = menu_->Options();
        if (idx < 0 || idx >= (int)options.size()) return;

        auto& opt = options[idx];
        if (opt.Disabled || !opt.OnSelect) return;

        // The handler may close this menu or open another one for the player
        // (a submenu), and either destroys this instance. Nothing of `this`
        // may be touched after the call unless it is still the open menu.
        CCSPlayerController* player = player_;
        const uint64_t serial = serial_;

        // Called through a copy: a handler that rebuilds this same menu in
        // place (ClearOptions + AddMenuOption) destroys the std::function it
        // is running from.
        const auto onSelect = opt.OnSelect;
        {
            ::slow::Guard slowGuard("menu option", opt.Text.c_str(), menuManager.OwnerOf(player));
            onSelect(player, opt);
        }

        if (!menuManager.IsOpen(player, serial))
            return;

        // Apply PostSelectAction just like CSSharp BaseMenuInstance
        switch (menu_->GetPostSelectAction())
        {
        case PostSelectAction::Close:
            Close();
            break;
        case PostSelectAction::Reset:
            while (!prevPageOffsets_.empty()) prevPageOffsets_.pop();
            page_ = 0;
            currentOffset_ = 0;
            break;
        case PostSelectAction::Nothing:
        default:
            break;
        }
    }

    void CenterHtmlMenuInstance::Close()
    {
        // CloseActiveMenu destroys this instance.
        CCSPlayerController* player = player_;
        menuManager.CloseActiveMenu(player);
        if (player)
        {
            player->PrintToCenterHtml(" ", 3, true);
        }
    }


    // ---- HUD menu ------------------------------------------------------------

    namespace
    {
        constexpr const char* kRowPanel[HudMenuInstance::kRows] = {
            "menu_row_0", "menu_row_1", "menu_row_2", "menu_row_3", "menu_row_4", "menu_row_5",
        };
        constexpr const char* kRowKey[HudMenuInstance::kRows] = {
            "menu_row_0_key", "menu_row_1_key", "menu_row_2_key", "menu_row_3_key", "menu_row_4_key", "menu_row_5_key",
        };
        constexpr const char* kRowText[HudMenuInstance::kRows] = {
            "menu_row_0_text", "menu_row_1_text", "menu_row_2_text", "menu_row_3_text", "menu_row_4_text", "menu_row_5_text",
        };
        constexpr const char* kShow = "show";
        constexpr const char* kDisabled = "disabled";

        void HashIn(size_t& seed, size_t value)
        {
            seed ^= value + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
        }
    }

    HudMenuInstance::HudMenuInstance(CCSPlayerController* player, HudMenu* menu, uint64_t serial, bool readCapture)
        : IMenuInstance(player, menu), hudMenu_(menu), serial_(serial), slot_(player ? player->GetSlot() : -1), readCapture_(readCapture)
    {
    }

    HudMenuInstance::~HudMenuInstance()
    {
        Hide();
    }

    void HudMenuInstance::Hide()
    {
        CCSCustomHudLayout* layout = hud::hudManager.MenuLayoutIfAny();
        CCSPlayerController* player = slot_ >= 0 ? CCSPlayerController::FromSlot(slot_) : nullptr;
        if (!layout || !player)
            return;

        layout->SetHasClass("menu_root", kShow, false, player);
        layout->SetHasClass("menu_dim", kShow, false, player);
        layout->SetInputCaptureEnabled(false, player);
    }

    size_t HudMenuInstance::Signature() const
    {
        size_t h = std::hash<std::string>{}(menu_->Title());
        HashIn(h, static_cast<size_t>(currentOffset_));

        const auto& opts = menu_->Options();
        HashIn(h, opts.size());

        const int end = (std::min)(currentOffset_ + kRows, static_cast<int>(opts.size()));
        for (int i = currentOffset_; i < end; ++i)
        {
            HashIn(h, std::hash<std::string>{}(opts[i].Text));
            HashIn(h, opts[i].Disabled ? 1 : 0);
        }

        HashIn(h, std::hash<std::string>{}(hudMenu_->PrevText));
        HashIn(h, std::hash<std::string>{}(hudMenu_->NextText));
        HashIn(h, std::hash<std::string>{}(hudMenu_->CloseText));
        HashIn(h, HasExitButton() ? 1 : 0);
        HashIn(h, hudMenu_->DimBackground ? 1 : 0);
        HashIn(h, CaptureInput() ? 1 : 0);
        HashIn(h, static_cast<size_t>(Position()));
        return h;
    }

    void HudMenuInstance::Display()
    {
        if (!player_ || !menu_) return;

        if (menuManager.GetActiveMenu(player_) != this)
        {
            Reset();
            return;
        }

        CCSCustomHudLayout* layout = hud::hudManager.MenuLayout();
        if (!layout)
            return;

        // The evaluators are plugin code and may close this menu or open
        // another one for the player, which destroys this instance.
        CCSPlayerController* player = player_;
        const uint64_t serial = serial_;

        auto& options = menu_->Options();
        for (size_t i = 0; i < options.size(); ++i)
        {
            auto& opt = options[i];
            if (!opt.DisabledEvaluator) continue;

            opt.Disabled = opt.DisabledEvaluator();
            if (!menuManager.IsOpen(player, serial)) return;
        }

        const auto& opts = menu_->Options();
        const int total = static_cast<int>(opts.size());

        layout->SetDialogVariableString("menu_title", "text", menu_->Title().c_str(), player);

        for (int row = 0; row < kRows; ++row)
        {
            const int idx = currentOffset_ + row;
            if (idx < total)
            {
                const auto& opt = opts[idx];
                layout->SetDialogVariableString(kRowKey[row], "text", std::to_string(row + 1).c_str(), player);
                layout->SetDialogVariableString(kRowText[row], "text", opt.Text.c_str(), player);
                layout->SetHasClass(kRowPanel[row], kDisabled, opt.Disabled, player);
                layout->SetHasClass(kRowPanel[row], kShow, true, player);
            }
            else
            {
                layout->SetHasClass(kRowPanel[row], kShow, false, player);
            }
        }

        layout->SetDialogVariableString("menu_prev_text", "text", hudMenu_->PrevText.c_str(), player);
        layout->SetDialogVariableString("menu_next_text", "text", hudMenu_->NextText.c_str(), player);
        layout->SetDialogVariableString("menu_close_text", "text", hudMenu_->CloseText.c_str(), player);
        layout->SetHasClass("menu_prev", kShow, HasPrevButton(), player);
        layout->SetHasClass("menu_next", kShow, HasNextButton(), player);
        layout->SetHasClass("menu_close", kShow, HasExitButton(), player);

        const int pages = total > 0 ? (total + kRows - 1) / kRows : 1;
        if (pages > 1)
        {
            const std::string footer = std::to_string(page_ + 1) + " / " + std::to_string(pages);
            layout->SetDialogVariableString("menu_footer", "text", footer.c_str(), player);
        }
        layout->SetHasClass("menu_footer", kShow, pages > 1, player);

        layout->SetHasClass("menu_dim", kShow, hudMenu_->DimBackground, player);
        // Where the window sits: all three set, so a position left on the
        // slot by an earlier menu does not linger next to this one's.
        const int pos = Position();
        if (pos != drawnPos_)
        {
            static constexpr const char* kPosClass[] = { "pos-left", "pos-center", "pos-right" };
            for (int i = 0; i < 3; ++i)
                layout->SetHasClass("menu_root", kPosClass[i], i == pos, player);
            drawnPos_ = pos;
        }

        layout->SetHasClass("menu_root", kShow, true, player);
        layout->SetInputCaptureEnabled(CaptureInput(), player);

        drawn_ = Signature();
    }

    void HudMenuInstance::Refresh()
    {
        if (!player_ || !menu_) return;

        CCSPlayerController* player = player_;
        const uint64_t serial = serial_;

        auto& options = menu_->Options();
        for (size_t i = 0; i < options.size(); ++i)
        {
            auto& opt = options[i];
            if (!opt.DisabledEvaluator) continue;

            opt.Disabled = opt.DisabledEvaluator();
            if (!menuManager.IsOpen(player, serial)) return;
        }

        if (Signature() != drawn_)
            Display();
    }

    void HudMenuInstance::OnKeyPress(CCSPlayerController* p, int key)
    {
        if (p != player_) return;
        if (!menu_) return;

        // 7 = Prev, 8 = Next, 9 = Close, as the center HTML menu.
        if (key == 8 && HasNextButton())
        {
            NextPage();
            return;
        }
        if (key == 7 && HasPrevButton())
        {
            PrevPage();
            return;
        }
        if (key == 9 && HasExitButton())
        {
            Close();
            return;
        }

        if (key < 1 || key > kRows) return;

        const int idx = currentOffset_ + (key - 1);
        auto& options = menu_->Options();
        if (idx < 0 || idx >= (int)options.size()) return;

        auto& opt = options[idx];
        if (opt.Disabled || !opt.OnSelect) return;

        // The handler may close this menu or open another one for the player
        // (a submenu), and either destroys this instance. Nothing of `this`
        // may be touched after the call unless it is still the open menu.
        CCSPlayerController* player = player_;
        const uint64_t serial = serial_;

        // Called through a copy: a handler that rebuilds this same menu in
        // place (ClearOptions + AddMenuOption) destroys the std::function it
        // is running from.
        const auto onSelect = opt.OnSelect;
        {
            ::slow::Guard slowGuard("menu option", opt.Text.c_str(), menuManager.OwnerOf(player));
            onSelect(player, opt);
        }

        if (!menuManager.IsOpen(player, serial))
            return;

        switch (menu_->GetPostSelectAction())
        {
        case PostSelectAction::Close:
            Close();
            return;
        case PostSelectAction::Reset:
            while (!prevPageOffsets_.empty()) prevPageOffsets_.pop();
            page_ = 0;
            currentOffset_ = 0;
            break;
        case PostSelectAction::Nothing:
        default:
            break;
        }

        // Whatever the handler changed is on screen right away; Refresh()
        // would catch it a frame later anyway.
        Display();
    }

    void HudMenuInstance::Close()
    {
        // CloseActiveMenu destroys this instance; the destructor hides it.
        menuManager.CloseActiveMenu(player_);
    }

    void MenuManager::OpenHudMenu(PluginId owner, CCSPlayerController* player, HudMenu* menu)
    {
        OpenHudMenuEx(owner, player, menu, true);
    }

    PluginId MenuManager::OwnerOf(CCSPlayerController* player) const
    {
        if (!player) return 0;

        auto it = activeMenus.find(player->GetSlot());
        return it == activeMenus.end() ? 0 : it->second.owner;
    }

    void MenuManager::OpenHudMenuEx(PluginId owner, CCSPlayerController* player, HudMenu* menu, bool readCapture)
    {
        if (!player || !menu) return;
        CloseActiveMenu(player);

        const uint64_t serial = ++nextSerial_;
        auto inst = std::make_unique<HudMenuInstance>(player, menu, serial, readCapture);

        auto& active = activeMenus[player->GetSlot()];
        active.owner = owner;
        active.serial = serial;
        active.hud = true;
        active.instance = std::move(inst);
        active.instance->Display();
    }

    void MenuManager::OnHudClick(CCSPlayerController* player, const char* buttonId)
    {
        if (!player || !buttonId) return;

        auto it = activeMenus.find(player->GetSlot());
        if (it == activeMenus.end() || !it->second.hud || !it->second.instance)
            return;

        int key = 0;
        if (!strncmp(buttonId, "menu_row_", 9))
            key = atoi(buttonId + 9) + 1;
        else if (!strcmp(buttonId, "menu_prev"))
            key = 7;
        else if (!strcmp(buttonId, "menu_next"))
            key = 8;
        else if (!strcmp(buttonId, "menu_close"))
            key = 9;

        if (key < 1 || key > 9)
            return;

        it->second.instance->OnKeyPress(player, key);
    }

    void MenuManager::OnClientDisconnect(CPlayerSlot slot)
    {
        auto it = activeMenus.find(slot.Get());
        if (it != activeMenus.end())
            activeMenus.erase(it);
    }

    void MenuManager::OpenCenterHtmlMenu(PluginId owner, CCSPlayerController* player, CenterHtmlMenu* menu)
    {
        if (!player || !menu) return;
        CloseActiveMenu(player);

        const uint64_t serial = ++nextSerial_;
        auto inst = std::make_unique<CenterHtmlMenuInstance>(player, menu, serial);

        auto& active = activeMenus[player->GetSlot()];
        active.owner = owner;
        active.serial = serial;
        active.hud = false;
        active.instance = std::move(inst);
        active.instance->Display();
    }

    bool MenuManager::IsOpen(CCSPlayerController* player, uint64_t serial) const
    {
        if (!player) return false;

        auto it = activeMenus.find(player->GetSlot());
        return it != activeMenus.end() && it->second.instance && it->second.serial == serial;
    }

    IMenuInstance* MenuManager::GetActiveMenu(CCSPlayerController* player)
    {
        if (!player) return nullptr;

        auto it = activeMenus.find(player->GetSlot());
        return (it == activeMenus.end()) ? nullptr : it->second.instance.get();
    }

    void MenuManager::CloseActiveMenu(CCSPlayerController* player)
    {
        if (!player) return;

        auto it = activeMenus.find(player->GetSlot());
        if (it != activeMenus.end())
        {
            it->second.instance->Reset();
            activeMenus.erase(it);
        }
    }

    void MenuManager::OnKeyPress(CCSPlayerController* player, int key)
    {
        auto* inst = GetActiveMenu(player);
        if (inst)
        {
            inst->OnKeyPress(player, key);
        }
    }

    void MenuManager::Tick()
    {
        // Display() runs the plugins' DisabledEvaluators, which may open or
        // close menus and so change activeMenus under a live iterator. Walk a
        // snapshot and skip whatever was closed or replaced meanwhile.
        tickSnapshot_.clear();
        for (const auto& kv : activeMenus)
            tickSnapshot_.emplace_back(kv.first, kv.second.serial);

        for (const auto& [slot, serial] : tickSnapshot_)
        {
            auto it = activeMenus.find(slot);
            if (it == activeMenus.end() || it->second.serial != serial || !it->second.instance)
                continue;

            if (it->second.hud)
                static_cast<HudMenuInstance*>(it->second.instance.get())->Refresh();
            else
                it->second.instance->Display();
        }
    }

    void MenuManager::RemoveAllForPlugin(PluginId id)
    {
        for (auto it = activeMenus.begin(); it != activeMenus.end(); )
        {
            if (it->second.owner != id)
            {
                ++it;
                continue;
            }

            // Clears the panel the player is looking at, the same as closing
            // it by hand would.
            if (it->second.instance)
                it->second.instance->Reset();

            it = activeMenus.erase(it);
        }
    }
}
