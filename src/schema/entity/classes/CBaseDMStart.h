#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CBaseDMStart : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CBaseDMStart);

    SCHEMA_FIELD(CUtlSymbolLarge, m_Master);
};
