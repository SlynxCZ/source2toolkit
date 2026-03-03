#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class Extent
{
public:
    DECLARE_SCHEMA_CLASS(Extent);

    SCHEMA_FIELD(Vector, lo);
    SCHEMA_FIELD(Vector, hi);
};
