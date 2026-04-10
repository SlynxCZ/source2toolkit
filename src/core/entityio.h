//
// Created by Michal Přikryl on 11.04.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "source2toolkit/schema/entity/classes/CCSPlayerController.h"
#include "source2toolkit/schema/entityio.h"
#include "source2toolkit/IToolkitEntityIO.h"

#include "eiface.h"
#include "entitysystem.h"

namespace entityio {
    class EntityIO : public IToolkitEntityIO {
        CBaseEntity* FindPickerEntity(CBasePlayerController* pPlayer, CCSGameRules* pGameRules = nullptr) override;
        CBaseEntity* FindEntityByClassname(CEntityInstance* pStart, const char* name) override;
        CBaseEntity* FindEntityByName(CEntityInstance* pStartEntity, const char* szName, CEntityInstance* pSearchingEntity = nullptr, CEntityInstance* pActivator = nullptr, CEntityInstance* pCaller = nullptr, IEntityFindFilter* pFilter = nullptr) override;

        CBaseEntity* CreateEntityByName(const char* pszClassName) override;

        void AcceptInput(CEntityInstance* pTarget, const char* pszInput, CEntityInstance* pActivator, CEntityInstance* pCaller, const char* pszValue = "") override;
        void AddEntityIOEvent(CEntityInstance* pTarget, const char* pszInput, CEntityInstance* pActivator = nullptr, CEntityInstance* pCaller = nullptr, const char* pszValue = "", float flDelay = 0.0f) override;

        void AddEntityIOListener(IEntityIOListener* pListener, const char* pchClassName, const char* pchOutputName, Mode nMode = Mode::Pre) override;
        void RemoveEntityIOListener(IEntityIOListener* pListener, const char* pchClassName, const char* pchOutputName, Mode nMode = Mode::Pre) override;
    };

    extern EntityIO entityIo;
}
