#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CFuncTimescale : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CFuncTimescale);

    SCHEMA_FIELD(float, m_flDesiredTimescale);
    SCHEMA_FIELD(float, m_flAcceleration);
    SCHEMA_FIELD(float, m_flMinBlendRate);
    SCHEMA_FIELD(float, m_flBlendDeltaMultiplier);
    SCHEMA_FIELD(bool, m_isStarted);
};
