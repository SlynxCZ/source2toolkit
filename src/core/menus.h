//
// Created by Michal Přikryl on 16.04.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "source2toolkit/IToolkitMenus.h"

namespace menus {
    class BaseMenu : public IBaseMenu
    {
    public:
        ChatMenuOption &AddMenuOptionWithCooldown(
                std::string optionText,
                std::function<void(CCSPlayerController *, ChatMenuOption &)> action,
                bool disabled = false,
                bool close = true,
                std::function<bool()> disabledEvaluator = nullptr) override;
    };

    class CenterHtmlMenuInstance : public IMenuInstance
    {
    public:
        CenterHtmlMenuInstance(CCSPlayerController *player, CenterHtmlMenu *menu)
            : IMenuInstance(player, menu), chMenu_(menu)
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

    private:
        CenterHtmlMenu *chMenu_;
    };

    class MenuManager : public IToolkitMenus
    {
    public:
        void OpenCenterHtmlMenu(CCSPlayerController *player, CenterHtmlMenu *menu) override;
        IMenuInstance *GetActiveMenu(CCSPlayerController *player) override;
        void CloseActiveMenu(CCSPlayerController *player) override;
        void OnKeyPress(CCSPlayerController *player, int key) override;
    public:
        void Tick();
    protected:
        std::unordered_map<int, std::unique_ptr<IMenuInstance>> activeMenus;
    };

    extern MenuManager menuManager;
}
