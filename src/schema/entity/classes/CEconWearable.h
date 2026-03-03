#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CEconEntity.h"

class CEconWearable : public CEconEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEconWearable);

    SCHEMA_FIELD(int32_t, m_nForceSkin);
    SCHEMA_FIELD(bool, m_bAlwaysAllow);
};
