#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CMessage : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CMessage);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszMessage);
    SCHEMA_FIELD(float, m_MessageVolume);
    SCHEMA_FIELD(int32_t, m_MessageAttenuation);
    SCHEMA_FIELD(float, m_Radius);
    SCHEMA_FIELD(CUtlSymbolLarge, m_sNoise);
    SCHEMA_FIELD(CEntityIOOutput, m_OnShowMessage);
};
