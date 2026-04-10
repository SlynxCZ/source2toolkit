//
// Created by Michal Přikryl on 11.04.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "entityio.h"

#include "addresses.h"
#include "commands.h"
#include "events.h"
#include "shared.h"
#include "source2toolkit/utils/plat.h"
#include "utils/scheduler.h"
#include "utils/vectorextends.h"
#include "dynlibutils/module.h"
#include "iserver.h"
#include "source2toolkit/schema/entity/classes/CBeam.h"
#include "schema/cgameresourceserviceserver.h"

namespace entityio
{
    EntityIO entityIo;

    CBaseEntity* EntityIO::FindPickerEntity(CBasePlayerController* pPlayer, CCSGameRules* pGameRules)
    {
        return UTIL_FindPickerEntity(pPlayer, pGameRules);
    }

    CBaseEntity* EntityIO::FindEntityByClassname(CEntityInstance* pStart, const char* name)
    {
        return UTIL_FindEntityByClassname(pStart, name);
    }

    CBaseEntity* EntityIO::FindEntityByName(CEntityInstance* pStartEntity, const char* szName, CEntityInstance* pSearchingEntity, CEntityInstance* pActivator, CEntityInstance* pCaller, IEntityFindFilter* pFilter)
    {
        return UTIL_FindEntityByName(pStartEntity, szName, pSearchingEntity, pActivator, pCaller, pFilter);
    }

    CBaseEntity* EntityIO::CreateEntityByName(const char* pszClassName)
    {
        return UTIL_CreateEntityByName(pszClassName);
    }

    void EntityIO::AcceptInput(CEntityInstance* pTarget, const char* pszInput, CEntityInstance* pActivator, CEntityInstance* pCaller, const char* pszValue)
    {
        return UTIL_AcceptInput(pTarget, pszInput, pActivator, pCaller, pszValue);
    }

    void EntityIO::AddEntityIOEvent(CEntityInstance* pTarget, const char* pszInput, CEntityInstance* pActivator, CEntityInstance* pCaller, const char* pszValue, float flDelay)
    {
        return UTIL_AddEntityIOEvent(pTarget, pszInput, pActivator, pCaller, pszValue, flDelay);
    }

    void EntityIO::AddEntityIOListener(IEntityIOListener* pListener, const char* pchClassName, const char* pchOutputName, Mode nMode)
    {
        UTIL_AddEntityIOListener(pListener, pchClassName, pchOutputName, nMode);
    }

    void EntityIO::RemoveEntityIOListener(IEntityIOListener* pListener, const char* pchClassName, const char* pchOutputName, Mode nMode)
    {
        UTIL_RemoveEntityIOListener(pListener, pchClassName, pchOutputName, nMode);
    }
}
