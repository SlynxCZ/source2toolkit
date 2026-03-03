#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class RotatorHistoryEntry_t
{
public:
    DECLARE_SCHEMA_CLASS(RotatorHistoryEntry_t);

    SCHEMA_FIELD(Quaternion, qInvChange);
    SCHEMA_FIELD(float, flTimeRotationStart);
};
