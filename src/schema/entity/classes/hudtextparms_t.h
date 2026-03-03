#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class hudtextparms_t
{
public:
    DECLARE_SCHEMA_CLASS(hudtextparms_t);

    SCHEMA_FIELD(Color, color1);
    SCHEMA_FIELD(Color, color2);
    SCHEMA_FIELD(uint8_t, effect);
    SCHEMA_FIELD(uint8_t, channel);
    SCHEMA_FIELD(float, x);
    SCHEMA_FIELD(float, y);
};
