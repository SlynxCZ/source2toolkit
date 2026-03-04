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

#include "CLogicalEntity.h"

class CLogicCollisionPair : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicCollisionPair);

    SCHEMA_FIELD(CUtlSymbolLarge, m_nameAttach1);
    SCHEMA_FIELD(CUtlSymbolLarge, m_nameAttach2);
    SCHEMA_FIELD(bool, m_includeHierarchy);
    SCHEMA_FIELD(bool, m_supportMultipleEntitiesWithSameName);
    SCHEMA_FIELD(bool, m_disabled);
    SCHEMA_FIELD(bool, m_succeeded);
};
