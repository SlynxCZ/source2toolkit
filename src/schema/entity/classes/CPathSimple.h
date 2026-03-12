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

#include "CBaseEntity.h"
#include "CPathQueryComponent.h"

class CPathSimple : public CBaseEntity, public CBaseEntity::Factory<CPathSimple>
{
public:
    DECLARE_SCHEMA_CLASS(CPathSimple);

    SCHEMA_FIELD(CPathQueryComponent, m_CPathQueryComponent);
    SCHEMA_FIELD(CUtlString, m_pathString);
    SCHEMA_FIELD(bool, m_bClosedLoop);
};
