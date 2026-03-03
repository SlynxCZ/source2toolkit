#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class constraint_breakableparams_t
{
public:
    DECLARE_SCHEMA_CLASS(constraint_breakableparams_t);

    SCHEMA_FIELD(float, strength);
    SCHEMA_FIELD(float, forceLimit);
    SCHEMA_FIELD(float, torqueLimit);
    SCHEMA_FIELD_POINTER(float, bodyMassScale);
    SCHEMA_FIELD(bool, isActive);
};
