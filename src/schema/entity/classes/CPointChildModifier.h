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

#include "CPointEntity.h"

class CPointChildModifier : public CPointEntity, public CBaseEntity::Factory<CPointChildModifier>
{
public:
    DECLARE_SCHEMA_CLASS(CPointChildModifier);

    SCHEMA_FIELD(bool, m_bOrphanInsteadOfDeletingChildrenOnRemove);
};
