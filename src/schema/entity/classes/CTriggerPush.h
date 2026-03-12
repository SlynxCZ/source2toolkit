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

class CPathSimple;

class CTriggerPush : public CBaseTrigger, public CBaseEntity::Factory<CTriggerPush>
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerPush);

    SCHEMA_FIELD(QAngle, m_angPushEntitySpace);
    SCHEMA_FIELD(Vector, m_vecPushDirEntitySpace);
    SCHEMA_FIELD(bool, m_bTriggerOnStartTouch);
    SCHEMA_FIELD(bool, m_bUsePathSimple);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszPathSimpleName);
    SCHEMA_FIELD(CPathSimple*, m_PathSimple);
    SCHEMA_FIELD(uint32_t, m_splinePushType);
};
