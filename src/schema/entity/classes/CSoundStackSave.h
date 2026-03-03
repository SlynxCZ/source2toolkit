#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CSoundStackSave : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CSoundStackSave);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszStackName);
};
