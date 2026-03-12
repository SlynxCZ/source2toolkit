#pragma once
#include "CBaseEntity.h"
#include "igameevents.h"
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

#include "CPointEntity.h"

class CEnvSpark : public CPointEntity, public CBaseEntity::Factory<CEnvSpark>
{
public:
    DECLARE_SCHEMA_CLASS(CEnvSpark);

    SCHEMA_FIELD(float, m_flDelay);
    SCHEMA_FIELD(int32_t, m_nMagnitude);
    SCHEMA_FIELD(int32_t, m_nTrailLength);
    SCHEMA_FIELD(int32_t, m_nType);
    SCHEMA_FIELD(CEntityIOOutput, m_OnSpark);
};
