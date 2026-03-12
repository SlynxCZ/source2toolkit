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

#include "CTriggerHurt.h"

class CScriptTriggerHurt : public CTriggerHurt, public CBaseEntity::Factory<CScriptTriggerHurt>
{
public:
    DECLARE_SCHEMA_CLASS(CScriptTriggerHurt);

    SCHEMA_FIELD(Vector, m_vExtent);
};
