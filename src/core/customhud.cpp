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
#include "customhud.h"

#include "networkmessages.h"

#include "source2toolkit/schema/entity/classes/CCSCustomHudLayout.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController.h"

#include <google/protobuf/message.h>

#include <algorithm>
#include <string>

namespace customhud
{
    CustomHudManager customHudManager;

    void CustomHudManager::HookCustomHudClick(PluginId owner, CCSCustomHudLayout* pLayout, CustomHudClickHandler handler)
    {
        if (!pLayout || !handler)
            return;

        m_callbacks.push_back({owner, CHandle<CCSCustomHudLayout>(pLayout), std::move(handler)});
    }

    void CustomHudManager::UnhookCustomHudClick(CCSCustomHudLayout* pLayout)
    {
        if (!pLayout)
            return;

        const CHandle<CCSCustomHudLayout> handle(pLayout);

        std::erase_if(m_callbacks, [&handle](const ClickCallbackEntry& e)
        {
            return e.layout == handle;
        });
    }

    void CustomHudManager::HandleClick(CCSPlayerController* pController, const void* pBuffer, uint32 nSize)
    {
        if (m_callbacks.empty() || !pController || !pBuffer)
            return;

        // The message is parsed through the engine's own descriptor rather than
        // a generated header -- CCSUsrMsg_CustomHudClicked is newer than the
        // protobuf checkout the toolkit builds against.
        void* pMessage = networkmessages::networkMessagesManager.AllocateNetMessageByID(CS_UM_CustomHudClicked);

        if (!pMessage)
            return;

        if (!static_cast<google::protobuf::Message*>(pMessage)->ParseFromArray(pBuffer, static_cast<int>(nSize)))
        {
            networkmessages::networkMessagesManager.DeallocateNetMessage(pMessage);
            return;
        }

        const uint32 nPackedHandle = networkmessages::networkMessagesManager.GetUInt32(pMessage, "custom_hud_layout");
        const std::string sButtonId = networkmessages::networkMessagesManager.GetString(pMessage, "button_id");

        networkmessages::networkMessagesManager.DeallocateNetMessage(pMessage);

        // Low 14 bits of a packed handle are the entity index; the stored
        // CHandle carries the serial, so a recycled index cannot match.
        const int nEntryIndex = static_cast<int>(nPackedHandle & 0x3FFF);

        // Collect first, fire second: a handler is free to open another layout
        // or drop its own callback, either of which would move this vector out
        // from under an iterator.
        std::vector<std::pair<CCSCustomHudLayout*, CustomHudClickHandler>> fire;

        for (auto it = m_callbacks.begin(); it != m_callbacks.end();)
        {
            CCSCustomHudLayout* pLayout = it->layout.Get();

            // Prune callbacks whose layout is gone while we are walking anyway.
            if (!pLayout)
            {
                it = m_callbacks.erase(it);
                continue;
            }

            if (it->layout.GetEntryIndex() == nEntryIndex)
                fire.emplace_back(pLayout, it->handler);

            ++it;
        }

        for (auto& [pLayout, handler] : fire)
            handler(pController, pLayout, sButtonId.c_str());
    }

    void CustomHudManager::RemoveAllForPlugin(PluginId id)
    {
        std::erase_if(m_callbacks, [id](const ClickCallbackEntry& e)
        {
            return e.owner == id;
        });
    }

    void CustomHudManager::Clear()
    {
        m_callbacks.clear();
    }
}
