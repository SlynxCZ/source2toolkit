#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CBaseEntity;

class CSceneListManager : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CSceneListManager);

    SCHEMA_FIELD(CUtlVector<CHandle<CSceneListManager>>, m_hListManagers);
    SCHEMA_FIELD_POINTER(CUtlSymbolLarge, m_iszScenes);
    SCHEMA_FIELD_POINTER(CHandle<CBaseEntity>, m_hScenes);
};
