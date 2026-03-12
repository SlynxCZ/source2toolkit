#pragma once
#include "igameevents.h"
#include "ehandle.h"
#include "entityhandle.h"
#include "vector.h"
#include "utlsymbol.h"
#include "utlsymbollarge.h"
#include "utlstring.h"
#include "utlstringtoken.h"
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
