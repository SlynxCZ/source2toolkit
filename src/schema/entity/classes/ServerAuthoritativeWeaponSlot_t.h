#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class ServerAuthoritativeWeaponSlot_t
{
public:
    DECLARE_SCHEMA_CLASS(ServerAuthoritativeWeaponSlot_t);

    SCHEMA_FIELD(uint16_t, unClass);
    SCHEMA_FIELD(uint16_t, unSlot);
    SCHEMA_FIELD(uint16_t, unItemDefIdx);
};
