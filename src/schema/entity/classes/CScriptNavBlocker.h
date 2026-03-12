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

#include "CFuncNavBlocker.h"

class CScriptNavBlocker : public CFuncNavBlocker, public CBaseEntity::Factory<CScriptNavBlocker>
{
public:
    DECLARE_SCHEMA_CLASS(CScriptNavBlocker);

    SCHEMA_FIELD(Vector, m_vExtent);
};
