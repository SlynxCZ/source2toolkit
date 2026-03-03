#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CSoundEventEntity.h"

class CSoundEventOBBEntity : public CSoundEventEntity
{
public:
    DECLARE_SCHEMA_CLASS(CSoundEventOBBEntity);

    SCHEMA_FIELD(Vector, m_vMins);
    SCHEMA_FIELD(Vector, m_vMaxs);
};
