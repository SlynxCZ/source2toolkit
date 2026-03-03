#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseFilter.h"
#include "../enums/filter_t.h"

class CBaseEntity;

class CFilterMultiple : public CBaseFilter
{
public:
    DECLARE_SCHEMA_CLASS(CFilterMultiple);

    SCHEMA_FIELD(filter_t, m_nFilterType);
    SCHEMA_FIELD_POINTER(CUtlSymbolLarge, m_iFilterName);
    SCHEMA_FIELD_POINTER(CHandle<CBaseEntity>, m_hFilter);
};
