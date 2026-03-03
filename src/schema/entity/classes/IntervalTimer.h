#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class IntervalTimer
{
public:
    DECLARE_SCHEMA_CLASS(IntervalTimer);

    SCHEMA_FIELD(float, m_timestamp);
    SCHEMA_FIELD(WorldGroupId_t, m_nWorldGroupId);
};
