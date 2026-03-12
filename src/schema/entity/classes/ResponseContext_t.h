#pragma once
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

class ResponseContext_t
{
public:
    DECLARE_SCHEMA_CLASS(ResponseContext_t);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszValue);
    SCHEMA_FIELD(float, m_fExpirationTime);
};
