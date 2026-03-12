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

#include "CPointEntity.h"

class CPathCorner : public CPointEntity, public CBaseEntity::Factory<CPathCorner>
{
public:
    DECLARE_SCHEMA_CLASS(CPathCorner);

    SCHEMA_FIELD(float, m_flWait);
    SCHEMA_FIELD(float, m_flRadius);
    SCHEMA_FIELD(CEntityIOOutput, m_OnPass);
};
