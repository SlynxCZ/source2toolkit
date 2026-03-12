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

class CLogicAuto : public CBaseEntity, public CBaseEntity::Factory<CLogicAuto>
{
public:
    DECLARE_SCHEMA_CLASS(CLogicAuto);

    SCHEMA_FIELD(CEntityIOOutput, m_OnMapSpawn);
    SCHEMA_FIELD(CEntityIOOutput, m_OnDemoMapSpawn);
    SCHEMA_FIELD(CEntityIOOutput, m_OnNewGame);
    SCHEMA_FIELD(CEntityIOOutput, m_OnLoadGame);
    SCHEMA_FIELD(CEntityIOOutput, m_OnMapTransition);
    SCHEMA_FIELD(CEntityIOOutput, m_OnBackgroundMap);
    SCHEMA_FIELD(CEntityIOOutput, m_OnMultiNewMap);
    SCHEMA_FIELD(CEntityIOOutput, m_OnMultiNewRound);
    SCHEMA_FIELD(CEntityIOOutput, m_OnVREnabled);
    SCHEMA_FIELD(CEntityIOOutput, m_OnVRNotEnabled);
    SCHEMA_FIELD(CUtlSymbolLarge, m_globalstate);
};
