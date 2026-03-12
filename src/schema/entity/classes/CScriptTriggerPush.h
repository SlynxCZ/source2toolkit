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

#include "CTriggerPush.h"

class CScriptTriggerPush : public CTriggerPush, public CBaseEntity::Factory<CScriptTriggerPush>
{
public:
    DECLARE_SCHEMA_CLASS(CScriptTriggerPush);

    SCHEMA_FIELD(Vector, m_vExtent);
};
