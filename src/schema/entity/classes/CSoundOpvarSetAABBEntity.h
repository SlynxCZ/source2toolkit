#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CSoundOpvarSetPointEntity.h"

class CSoundOpvarSetAABBEntity : public CSoundOpvarSetPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CSoundOpvarSetAABBEntity);

    SCHEMA_FIELD(Vector, m_vDistanceInnerMins);
    SCHEMA_FIELD(Vector, m_vDistanceInnerMaxs);
    SCHEMA_FIELD(Vector, m_vDistanceOuterMins);
    SCHEMA_FIELD(Vector, m_vDistanceOuterMaxs);
    SCHEMA_FIELD(int32_t, m_nAABBDirection);
    SCHEMA_FIELD(Vector, m_vInnerMins);
    SCHEMA_FIELD(Vector, m_vInnerMaxs);
    SCHEMA_FIELD(Vector, m_vOuterMins);
    SCHEMA_FIELD(Vector, m_vOuterMaxs);
};
