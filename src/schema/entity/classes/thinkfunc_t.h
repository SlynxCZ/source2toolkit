#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class thinkfunc_t
{
public:
    DECLARE_SCHEMA_CLASS(thinkfunc_t);

    SCHEMA_FIELD(CUtlStringToken, m_nContext);
    SCHEMA_FIELD(int32_t, m_nNextThinkTick);
    SCHEMA_FIELD(int32_t, m_nLastThinkTick);
};
