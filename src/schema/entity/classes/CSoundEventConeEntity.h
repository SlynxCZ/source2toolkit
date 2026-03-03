#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CSoundEventEntity.h"

class CSoundEventConeEntity : public CSoundEventEntity
{
public:
    DECLARE_SCHEMA_CLASS(CSoundEventConeEntity);

    SCHEMA_FIELD(float, m_flEmitterAngle);
    SCHEMA_FIELD(float, m_flSweetSpotAngle);
    SCHEMA_FIELD(float, m_flAttenMin);
    SCHEMA_FIELD(float, m_flAttenMax);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszParameterName);
};
