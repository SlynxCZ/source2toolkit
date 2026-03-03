#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CVectorExponentialMovingAverage.h"

class CMovementStatsProperty
{
public:
    DECLARE_SCHEMA_CLASS(CMovementStatsProperty);

    SCHEMA_FIELD(int32_t, m_nUseCounter);
    SCHEMA_FIELD(CVectorExponentialMovingAverage, m_emaMovementDirection);
};
