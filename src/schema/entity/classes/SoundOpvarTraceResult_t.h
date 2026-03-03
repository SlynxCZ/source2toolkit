#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class SoundOpvarTraceResult_t
{
public:
    DECLARE_SCHEMA_CLASS(SoundOpvarTraceResult_t);

    SCHEMA_FIELD(Vector, vPos);
    SCHEMA_FIELD(bool, bDidHit);
    SCHEMA_FIELD(float, flDistSqrToCenter);
};
