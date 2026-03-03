#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "../enums/HitGroup_t.h"

class DestructibleHitGroupToDestroy_t
{
public:
    DECLARE_SCHEMA_CLASS(DestructibleHitGroupToDestroy_t);

    SCHEMA_FIELD(HitGroup_t, m_nHitGroup);
    SCHEMA_FIELD(int32_t, m_nMaxDamageLevel);
};
