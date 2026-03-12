#pragma once
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

class CountdownTimer : public CBaseEntity::Factory<CountdownTimer>
{
public:
    DECLARE_SCHEMA_CLASS(CountdownTimer);

    SCHEMA_FIELD(float, m_duration);
    SCHEMA_FIELD(float, m_timestamp);
    SCHEMA_FIELD(float, m_timescale);
    SCHEMA_FIELD(WorldGroupId_t, m_nWorldGroupId);
};
