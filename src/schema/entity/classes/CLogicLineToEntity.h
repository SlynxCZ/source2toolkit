#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CBaseEntity;

class CLogicLineToEntity : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicLineToEntity);

    SCHEMA_FIELD(CUtlSymbolLarge, m_SourceName);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_StartEntity);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_EndEntity);
};
