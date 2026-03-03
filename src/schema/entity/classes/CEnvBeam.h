#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBeam.h"
#include "InfoForResourceTypeIMaterial2.h"
#include "../enums/Touch_t.h"

class CBaseEntity;

class CEnvBeam : public CBeam
{
public:
    DECLARE_SCHEMA_CLASS(CEnvBeam);

    SCHEMA_FIELD(int32_t, m_active);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeIMaterial2 >, m_spriteTexture);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszStartEntity);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszEndEntity);
    SCHEMA_FIELD(float, m_life);
    SCHEMA_FIELD(float, m_boltWidth);
    SCHEMA_FIELD(float, m_noiseAmplitude);
    SCHEMA_FIELD(int32_t, m_speed);
    SCHEMA_FIELD(float, m_restrike);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszSpriteName);
    SCHEMA_FIELD(int32_t, m_frameStart);
    SCHEMA_FIELD(Vector, m_vEndPointWorld);
    SCHEMA_FIELD(Vector, m_vEndPointRelative);
    SCHEMA_FIELD(float, m_radius);
    SCHEMA_FIELD(Touch_t, m_TouchType);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iFilterName);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hFilter);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszDecal);
    SCHEMA_FIELD(CEntityIOOutput, m_OnTouchedByEntity);
};
