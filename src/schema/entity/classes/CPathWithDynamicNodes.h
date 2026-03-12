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

#include "CPathSimple.h"

class CPathNode;

class CPathWithDynamicNodes : public CPathSimple, public CBaseEntity::Factory<CPathWithDynamicNodes>
{
public:
    DECLARE_SCHEMA_CLASS(CPathWithDynamicNodes);

    SCHEMA_FIELD(CUtlVector<CHandle<CPathNode>>, m_vecPathNodes);
    SCHEMA_FIELD(CTransform, m_xInitialPathWorldToLocal);
};
