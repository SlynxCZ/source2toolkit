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

#include "source2toolkit/schema/entity/classes/CCSPlayerController.h"

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

        for (auto& opt : menu_->Options())
        {
            if (opt.DisabledEvaluator)
            {
                opt.Disabled = opt.DisabledEvaluator();
            }
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

        // Only 1..9 are item keys, same as C#
        if (key < 1 || key > 9) return;

        const int idx = currentOffset_ + (key - 1);
        auto& options = menu_->Options();
        if (idx < 0 || idx >= (int)options.size()) return;

        auto& opt = options[idx];
        if (opt.Disabled || !opt.OnSelect) return;

        auto *self = this;

        opt.OnSelect(player_, opt);

        if (menuManager.GetActiveMenu(player_) != self)
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
        menuManager.CloseActiveMenu(player_);
        if (player_)
        {
            player_->PrintToCenterHtml(" ", 3, true);
        }
    }

    void MenuManager::OpenCenterHtmlMenu(CCSPlayerController* player, CenterHtmlMenu* menu)
    {
        if (!player || !menu) return;
        CloseActiveMenu(player);

        auto inst = std::make_unique<CenterHtmlMenuInstance>(player, menu);

        activeMenus[player->GetSlot()] = std::move(inst);
        activeMenus[player->GetSlot()]->Display();
    }

    IMenuInstance* MenuManager::GetActiveMenu(CCSPlayerController* player)
    {
        if (!player) return nullptr;

        auto it = activeMenus.find(player->GetSlot());
        return (it == activeMenus.end()) ? nullptr : it->second.get();
    }

    void MenuManager::CloseActiveMenu(CCSPlayerController* player)
    {
        if (!player) return;

        auto it = activeMenus.find(player->GetSlot());
        if (it != activeMenus.end())
        {
            it->second->Reset();
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
        for (auto& kv : activeMenus)
        {
            if (kv.second) kv.second->Display();
        }
    }
}
