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

#include "CModelPointEntity.h"

class CRevertSaved : public CModelPointEntity, public CBaseEntity::Factory<CRevertSaved>
{
public:
    DECLARE_SCHEMA_CLASS(CRevertSaved);

    SCHEMA_FIELD(float, m_loadTime);
    SCHEMA_FIELD(float, m_Duration);
    SCHEMA_FIELD(float, m_HoldTime);
};
