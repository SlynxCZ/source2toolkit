#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class ResourceId_t
{
public:
    DECLARE_SCHEMA_CLASS(ResourceId_t);

    SCHEMA_FIELD(uint64_t, m_Value);
};
