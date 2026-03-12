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

#include "CLogicalEntity.h"

class CMathCounter : public CLogicalEntity, public CBaseEntity::Factory<CMathCounter>
{
public:
    DECLARE_SCHEMA_CLASS(CMathCounter);

    SCHEMA_FIELD(float, m_flMin);
    SCHEMA_FIELD(float, m_flMax);
    SCHEMA_FIELD(bool, m_bHitMin);
    SCHEMA_FIELD(bool, m_bHitMax);
    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(CEntityIOOutput, m_OnHitMin);
    SCHEMA_FIELD(CEntityIOOutput, m_OnHitMax);
    SCHEMA_FIELD(CEntityIOOutput, m_OnChangedFromMin);
    SCHEMA_FIELD(CEntityIOOutput, m_OnChangedFromMax);
};
