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

#include "CBaseEntity.h"

class CSoundEventParameter : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CSoundEventParameter);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszParamName);
    SCHEMA_FIELD(float, m_flFloatValue);
};
