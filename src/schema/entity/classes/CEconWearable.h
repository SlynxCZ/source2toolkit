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

#include "CEconEntity.h"

class CEconWearable : public CEconEntity, public CBaseEntity::Factory<CEconWearable>
{
public:
    DECLARE_SCHEMA_CLASS(CEconWearable);

    SCHEMA_FIELD(int32_t, m_nForceSkin);
    SCHEMA_FIELD(bool, m_bAlwaysAllow);
};
