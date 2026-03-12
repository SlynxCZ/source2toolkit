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

#include "CBaseFilter.h"

class CFilterContext : public CBaseFilter, public CBaseEntity::Factory<CFilterContext>
{
public:
    DECLARE_SCHEMA_CLASS(CFilterContext);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iFilterContext);
};
