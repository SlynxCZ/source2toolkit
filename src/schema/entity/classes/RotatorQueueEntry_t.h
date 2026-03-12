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

#include "../enums/RotatorTargetSpace_t.h"

class RotatorQueueEntry_t : public CBaseEntity::Factory<RotatorQueueEntry_t>
{
public:
    DECLARE_SCHEMA_CLASS(RotatorQueueEntry_t);

    SCHEMA_FIELD(Quaternion, qTarget);
    SCHEMA_FIELD(RotatorTargetSpace_t, eSpace);
};
