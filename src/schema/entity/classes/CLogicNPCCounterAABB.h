#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicNPCCounter.h"

class CLogicNPCCounterAABB : public CLogicNPCCounter
{
public:
    DECLARE_SCHEMA_CLASS(CLogicNPCCounterAABB);

    SCHEMA_FIELD(Vector, m_vDistanceOuterMins);
    SCHEMA_FIELD(Vector, m_vDistanceOuterMaxs);
    SCHEMA_FIELD(Vector, m_vOuterMins);
    SCHEMA_FIELD(Vector, m_vOuterMaxs);
};
