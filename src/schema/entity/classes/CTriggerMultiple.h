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

#include "CBaseTrigger.h"

class CTriggerMultiple : public CBaseTrigger, public CBaseEntity::Factory<CTriggerMultiple>
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerMultiple);

    SCHEMA_FIELD(CEntityIOOutput, m_OnTrigger);
};
