#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CLightEntity;

class CMultiLightProxy : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CMultiLightProxy);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszLightNameFilter);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszLightClassFilter);
    SCHEMA_FIELD(float, m_flLightRadiusFilter);
    SCHEMA_FIELD(float, m_flBrightnessDelta);
    SCHEMA_FIELD(bool, m_bPerformScreenFade);
    SCHEMA_FIELD(float, m_flTargetBrightnessMultiplier);
    SCHEMA_FIELD(float, m_flCurrentBrightnessMultiplier);
    SCHEMA_FIELD(CUtlVector<CHandle<CLightEntity>>, m_vecLights);
};
