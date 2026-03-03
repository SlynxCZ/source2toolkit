#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CServerOnlyPointEntity.h"

class CPointPrefab : public CServerOnlyPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPointPrefab);

    SCHEMA_FIELD(CUtlSymbolLarge, m_targetMapName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_forceWorldGroupID);
    SCHEMA_FIELD(CUtlSymbolLarge, m_associatedRelayTargetName);
    SCHEMA_FIELD(bool, m_fixupNames);
    SCHEMA_FIELD(bool, m_bLoadDynamic);
    SCHEMA_FIELD(CHandle<CPointPrefab>, m_associatedRelayEntity);
};
