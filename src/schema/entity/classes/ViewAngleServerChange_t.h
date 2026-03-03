#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "../enums/FixAngleSet_t.h"

class ViewAngleServerChange_t
{
public:
    DECLARE_SCHEMA_CLASS(ViewAngleServerChange_t);

    SCHEMA_FIELD(FixAngleSet_t, nType);
    SCHEMA_FIELD(QAngle, qAngle);
    SCHEMA_FIELD(uint32_t, nIndex);
};
