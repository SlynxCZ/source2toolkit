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

class CBaseFilter : public CLogicalEntity, public CBaseEntity::Factory<CBaseFilter>
{
public:
    DECLARE_SCHEMA_CLASS(CBaseFilter);

    SCHEMA_FIELD(bool, m_bNegated);
    SCHEMA_FIELD(CEntityIOOutput, m_OnPass);
    SCHEMA_FIELD(CEntityIOOutput, m_OnFail);
};
