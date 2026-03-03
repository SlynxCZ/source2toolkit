#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "../enums/MoveType_t.h"
#include "ParticleIndex_t.h"

class CBaseEntity;

class lerpdata_t
{
public:
    DECLARE_SCHEMA_CLASS(lerpdata_t);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hEnt);
    SCHEMA_FIELD(MoveType_t, m_MoveType);
    SCHEMA_FIELD(float, m_flStartTime);
    SCHEMA_FIELD(Vector, m_vecStartOrigin);
    SCHEMA_FIELD(Quaternion, m_qStartRot);
    SCHEMA_FIELD(ParticleIndex_t, m_nFXIndex);
};
