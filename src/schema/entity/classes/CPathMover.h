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

#include "CPathWithDynamicNodes.h"

class CFuncMover;
class CPathMoverEntitySpawner;

class CPathMover : public CPathWithDynamicNodes, public CBaseEntity::Factory<CPathMover>
{
public:
    DECLARE_SCHEMA_CLASS(CPathMover);

    SCHEMA_FIELD(CUtlVector<CHandle<CFuncMover>>, m_vecMovers);
    SCHEMA_FIELD(CHandle<CPathMoverEntitySpawner>, m_hMoverSpawner);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszMoverSpawnerName);
};
