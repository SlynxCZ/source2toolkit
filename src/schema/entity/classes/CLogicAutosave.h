#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CLogicAutosave : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicAutosave);

    SCHEMA_FIELD(bool, m_bForceNewLevelUnit);
    SCHEMA_FIELD(int32_t, m_minHitPoints);
    SCHEMA_FIELD(int32_t, m_minHitPointsToCommit);
};
