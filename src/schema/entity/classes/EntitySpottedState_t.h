#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class EntitySpottedState_t
{
public:
    DECLARE_SCHEMA_CLASS(EntitySpottedState_t);

    SCHEMA_FIELD(bool, m_bSpotted);
    SCHEMA_FIELD_POINTER(uint32_t, m_bSpottedByMask);
};
