#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class PredictedDamageTag_t
{
public:
    DECLARE_SCHEMA_CLASS(PredictedDamageTag_t);

    SCHEMA_FIELD(int32_t, nTagTick);
    SCHEMA_FIELD(float, flFlinchModSmall);
    SCHEMA_FIELD(float, flFlinchModLarge);
    SCHEMA_FIELD(float, flFriendlyFireDamageReductionRatio);
};
