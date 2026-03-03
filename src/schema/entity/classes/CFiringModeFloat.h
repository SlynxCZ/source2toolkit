#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CFiringModeFloat
{
public:
    DECLARE_SCHEMA_CLASS(CFiringModeFloat);

    SCHEMA_FIELD_POINTER(float, m_flValues);
};
