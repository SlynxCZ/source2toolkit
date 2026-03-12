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

class IntervalTimer : public CBaseEntity::Factory<IntervalTimer>
{
public:
    DECLARE_SCHEMA_CLASS(IntervalTimer);

    SCHEMA_FIELD(float, m_timestamp);
    SCHEMA_FIELD(WorldGroupId_t, m_nWorldGroupId);
};
