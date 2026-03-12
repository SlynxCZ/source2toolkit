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

#include "CBaseFilter.h"

class CFilterEnemy : public CBaseFilter, public CBaseEntity::Factory<CFilterEnemy>
{
public:
    DECLARE_SCHEMA_CLASS(CFilterEnemy);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszEnemyName);
    SCHEMA_FIELD(float, m_flRadius);
    SCHEMA_FIELD(float, m_flOuterRadius);
    SCHEMA_FIELD(int32_t, m_nMaxSquadmatesPerEnemy);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszPlayerName);
};
