#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CInfoFan : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CInfoFan);

    SCHEMA_FIELD(float, m_fFanForceMaxRadius);
    SCHEMA_FIELD(float, m_fFanForceMinRadius);
    SCHEMA_FIELD(float, m_flCurveDistRange);
    SCHEMA_FIELD(CUtlSymbolLarge, m_FanForceCurveString);
};
