#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseFilter.h"

class FilterHealth : public CBaseFilter
{
public:
    DECLARE_SCHEMA_CLASS(FilterHealth);

    SCHEMA_FIELD(bool, m_bAdrenalineActive);
    SCHEMA_FIELD(int32_t, m_iHealthMin);
    SCHEMA_FIELD(int32_t, m_iHealthMax);
};
