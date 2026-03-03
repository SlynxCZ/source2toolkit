#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CPathMover;

class CPathMoverEntitySpawner : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPathMoverEntitySpawner);

    SCHEMA_FIELD_POINTER(CUtlSymbolLarge, m_szSpawnTemplates);
    SCHEMA_FIELD(int32_t, m_nSpawnIndex);
    SCHEMA_FIELD(CHandle<CPathMover>, m_hPathMover);
    SCHEMA_FIELD(float, m_flSpawnFrequencySeconds);
    SCHEMA_FIELD(float, m_flSpawnFrequencyDistToNearestMover);
    SCHEMA_FIELD(int32_t, m_nMaxActive);
    SCHEMA_FIELD(float, m_flLastSpawnTime);
    SCHEMA_FIELD(bool, m_bEnabled);
};
