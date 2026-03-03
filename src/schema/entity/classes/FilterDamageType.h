#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseFilter.h"

class FilterDamageType : public CBaseFilter
{
public:
    DECLARE_SCHEMA_CLASS(FilterDamageType);

    SCHEMA_FIELD(int32_t, m_iDamageType);
};
