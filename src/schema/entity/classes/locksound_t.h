#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class locksound_t
{
public:
    DECLARE_SCHEMA_CLASS(locksound_t);

    SCHEMA_FIELD(CUtlSymbolLarge, sLockedSound);
    SCHEMA_FIELD(CUtlSymbolLarge, sUnlockedSound);
    SCHEMA_FIELD(float, flwaitSound);
};
