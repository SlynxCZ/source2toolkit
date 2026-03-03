#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"

class CRuleEntity : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CRuleEntity);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszMaster);
};
