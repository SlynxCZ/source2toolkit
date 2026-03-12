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

class CInfoWorldLayer : public CBaseEntity, public CBaseEntity::Factory<CInfoWorldLayer>
{
public:
    DECLARE_SCHEMA_CLASS(CInfoWorldLayer);

    SCHEMA_FIELD(CEntityIOOutput, m_pOutputOnEntitiesSpawned);
    SCHEMA_FIELD(CUtlSymbolLarge, m_worldName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_layerName);
    SCHEMA_FIELD(bool, m_bWorldLayerVisible);
    SCHEMA_FIELD(bool, m_bEntitiesSpawned);
    SCHEMA_FIELD(bool, m_bCreateAsChildSpawnGroup);
    SCHEMA_FIELD(uint32_t, m_hLayerSpawnGroup);
};
