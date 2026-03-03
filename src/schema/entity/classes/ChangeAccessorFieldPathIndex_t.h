#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class ChangeAccessorFieldPathIndex_t
{
public:
    DECLARE_SCHEMA_CLASS(ChangeAccessorFieldPathIndex_t);

    SCHEMA_FIELD(int32_t, m_Value);
};
