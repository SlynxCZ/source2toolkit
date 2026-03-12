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

class CBaseEntity;

class CSceneListManager : public CLogicalEntity, public CBaseEntity::Factory<CSceneListManager>
{
public:
    DECLARE_SCHEMA_CLASS(CSceneListManager);

    SCHEMA_FIELD(CUtlVector<CHandle<CSceneListManager>>, m_hListManagers);
    SCHEMA_FIELD_POINTER(CUtlSymbolLarge, m_iszScenes);
    SCHEMA_FIELD_POINTER(CHandle<CBaseEntity>, m_hScenes);
};
