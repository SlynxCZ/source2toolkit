#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CPointGamestatsCounter : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPointGamestatsCounter);

    SCHEMA_FIELD(CUtlSymbolLarge, m_strStatisticName);
    SCHEMA_FIELD(bool, m_bDisabled);
};
