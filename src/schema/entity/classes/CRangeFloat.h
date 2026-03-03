#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CRangeFloat
{
public:
    DECLARE_SCHEMA_CLASS(CRangeFloat);

    SCHEMA_FIELD_POINTER(float, m_pValue);
};
