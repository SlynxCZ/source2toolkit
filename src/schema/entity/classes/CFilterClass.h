#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseFilter.h"

class CFilterClass : public CBaseFilter
{
public:
    DECLARE_SCHEMA_CLASS(CFilterClass);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iFilterClass);
};
