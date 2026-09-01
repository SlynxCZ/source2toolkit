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
#include "source2toolkit/IToolkitEntities.h"
#include "source2toolkit/schema/entityio.h"

#include "eiface.h"
#include "entitysystem.h"

namespace entities {
    class EntitiesManager : public IToolkitEntities {
    public:
        CCSGameRules* GetGameRules() override;
        CBaseEntity* FindPickerEntity(CBasePlayerController* pPlayer, CCSGameRules* pGameRules = nullptr) override;
        CBaseEntity* FindEntityByClassname(CEntityInstance* pStart, const char* name) override;
        CBaseEntity* FindEntityByName(CEntityInstance* pStartEntity, const char* szName, CEntityInstance* pSearchingEntity = nullptr, CEntityInstance* pActivator = nullptr, CEntityInstance* pCaller = nullptr, IEntityFindFilter* pFilter = nullptr) override;

        CBaseEntity* CreateEntityByName(const char* pszClassName) override;

        void AddEntityListener(IEntityListener* pListener) override;
        void RemoveEntityListener(IEntityListener* pListener) override;

        void AcceptInput(CEntityInstance* pTarget, const char* pszInput, CEntityInstance* pActivator, CEntityInstance* pCaller, const char* pszValue = "") override;
        void AddEntityIOEvent(CEntityInstance* pTarget, const char* pszInput, CEntityInstance* pActivator = nullptr, CEntityInstance* pCaller = nullptr, const char* pszValue = "", float flDelay = 0.0f) override;

        void AddEntityIOListener(IEntityIOListener* pListener, const char* pchClassName, const char* pchOutputName, bool post = false) override;
        void RemoveEntityIOListener(IEntityIOListener* pListener, const char* pchClassName, const char* pchOutputName, bool post = false) override;
    };

    extern EntitiesManager entitiesManager;
}
