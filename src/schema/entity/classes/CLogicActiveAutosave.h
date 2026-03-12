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

#include "CLogicAutosave.h"

class CLogicActiveAutosave : public CLogicAutosave, public CBaseEntity::Factory<CLogicActiveAutosave>
{
public:
    DECLARE_SCHEMA_CLASS(CLogicActiveAutosave);

    SCHEMA_FIELD(int32_t, m_TriggerHitPoints);
    SCHEMA_FIELD(float, m_flTimeToTrigger);
    SCHEMA_FIELD(float, m_flStartTime);
    SCHEMA_FIELD(float, m_flDangerousTime);
};
