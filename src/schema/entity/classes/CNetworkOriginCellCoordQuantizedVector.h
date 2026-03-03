#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CNetworkOriginCellCoordQuantizedVector
{
public:
    DECLARE_SCHEMA_CLASS(CNetworkOriginCellCoordQuantizedVector);

    SCHEMA_FIELD(uint16_t, m_cellX);
    SCHEMA_FIELD(uint16_t, m_cellY);
    SCHEMA_FIELD(uint16_t, m_cellZ);
    SCHEMA_FIELD(uint16_t, m_nOutsideWorld);
    SCHEMA_FIELD(float, m_vecX);
    SCHEMA_FIELD(float, m_vecY);
    SCHEMA_FIELD(float, m_vecZ);
};
