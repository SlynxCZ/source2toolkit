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

#include "CBaseModelEntity.h"

class CTriggerBrush : public CBaseModelEntity, public CBaseEntity::Factory<CTriggerBrush>
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerBrush);

    SCHEMA_FIELD(CEntityIOOutput, m_OnStartTouch);
    SCHEMA_FIELD(CEntityIOOutput, m_OnEndTouch);
    SCHEMA_FIELD(CEntityIOOutput, m_OnUse);
    SCHEMA_FIELD(int32_t, m_iInputFilter);
    SCHEMA_FIELD(int32_t, m_iDontMessageParent);
};
