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

#include "CServerOnlyPointEntity.h"

class CPointPrefab : public CServerOnlyPointEntity, public CBaseEntity::Factory<CPointPrefab>
{
public:
    DECLARE_SCHEMA_CLASS(CPointPrefab);

    SCHEMA_FIELD(CUtlSymbolLarge, m_targetMapName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_forceWorldGroupID);
    SCHEMA_FIELD(CUtlSymbolLarge, m_associatedRelayTargetName);
    SCHEMA_FIELD(bool, m_fixupNames);
    SCHEMA_FIELD(bool, m_bLoadDynamic);
    SCHEMA_FIELD(CHandle<CPointPrefab>, m_associatedRelayEntity);
};
