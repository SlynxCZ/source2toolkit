#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class AutoRoomDoorwayPairs_t
{
public:
    DECLARE_SCHEMA_CLASS(AutoRoomDoorwayPairs_t);

    SCHEMA_FIELD(Vector, vP1);
    SCHEMA_FIELD(Vector, vP2);
};
