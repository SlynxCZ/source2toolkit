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

class RotatorHistoryEntry_t : public CBaseEntity::Factory<RotatorHistoryEntry_t>
{
public:
    DECLARE_SCHEMA_CLASS(RotatorHistoryEntry_t);

    SCHEMA_FIELD(Quaternion, qInvChange);
    SCHEMA_FIELD(float, flTimeRotationStart);
};
