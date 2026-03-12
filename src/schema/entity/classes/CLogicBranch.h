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

#include "CLogicalEntity.h"

class CBaseEntity;

class CLogicBranch : public CLogicalEntity, public CBaseEntity::Factory<CLogicBranch>
{
public:
    DECLARE_SCHEMA_CLASS(CLogicBranch);

    SCHEMA_FIELD(bool, m_bInValue);
    SCHEMA_FIELD(CUtlVector<CHandle<CBaseEntity>>, m_Listeners);
    SCHEMA_FIELD(CEntityIOOutput, m_OnTrue);
    SCHEMA_FIELD(CEntityIOOutput, m_OnFalse);
};
