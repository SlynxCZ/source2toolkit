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

#include "CBaseTrigger.h"

class CTriggerSave : public CBaseTrigger, public CBaseEntity::Factory<CTriggerSave>
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerSave);

    SCHEMA_FIELD(bool, m_bForceNewLevelUnit);
    SCHEMA_FIELD(float, m_fDangerousTimer);
    SCHEMA_FIELD(int32_t, m_minHitPoints);
};
