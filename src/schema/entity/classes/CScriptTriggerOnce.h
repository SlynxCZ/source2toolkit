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

#include "CTriggerOnce.h"

class CScriptTriggerOnce : public CTriggerOnce, public CBaseEntity::Factory<CScriptTriggerOnce>
{
public:
    DECLARE_SCHEMA_CLASS(CScriptTriggerOnce);

    SCHEMA_FIELD(Vector, m_vExtent);
};
