#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class ParticleIndex_t
{
public:
    DECLARE_SCHEMA_CLASS(ParticleIndex_t);

    SCHEMA_FIELD(int32_t, m_Value);
};
