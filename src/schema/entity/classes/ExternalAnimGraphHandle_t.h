#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class ExternalAnimGraphHandle_t
{
public:
    DECLARE_SCHEMA_CLASS(ExternalAnimGraphHandle_t);

    SCHEMA_FIELD(uint32_t, m_Value);
};
