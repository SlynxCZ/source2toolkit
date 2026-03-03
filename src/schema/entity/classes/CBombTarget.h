#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"

class CBaseEntity;

class CBombTarget : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CBombTarget);

    SCHEMA_FIELD(CEntityIOOutput, m_OnBombExplode);
    SCHEMA_FIELD(CEntityIOOutput, m_OnBombPlanted);
    SCHEMA_FIELD(CEntityIOOutput, m_OnBombDefused);
    SCHEMA_FIELD(bool, m_bIsBombSiteB);
    SCHEMA_FIELD(bool, m_bIsHeistBombTarget);
    SCHEMA_FIELD(bool, m_bBombPlantedHere);
    SCHEMA_FIELD(CUtlSymbolLarge, m_szMountTarget);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hInstructorHint);
    SCHEMA_FIELD(int32_t, m_nBombSiteDesignation);
};
