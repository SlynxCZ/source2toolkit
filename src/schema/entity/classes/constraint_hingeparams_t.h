#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "constraint_axislimit_t.h"
#include "constraint_breakableparams_t.h"

class constraint_hingeparams_t
{
public:
    DECLARE_SCHEMA_CLASS(constraint_hingeparams_t);

    SCHEMA_FIELD(Vector, worldPosition);
    SCHEMA_FIELD(Vector, worldAxisDirection);
    SCHEMA_FIELD(constraint_axislimit_t, hingeAxis);
    SCHEMA_FIELD(constraint_breakableparams_t, constraint);
};
