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

#include "CLogicalEntity.h"

class CLogicCompare : public CLogicalEntity, public CBaseEntity::Factory<CLogicCompare>
{
public:
    DECLARE_SCHEMA_CLASS(CLogicCompare);

    SCHEMA_FIELD(float, m_flInValue);
    SCHEMA_FIELD(float, m_flCompareValue);
};
