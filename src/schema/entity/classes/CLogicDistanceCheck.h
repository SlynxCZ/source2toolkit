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

class CLogicDistanceCheck : public CLogicalEntity, public CBaseEntity::Factory<CLogicDistanceCheck>
{
public:
    DECLARE_SCHEMA_CLASS(CLogicDistanceCheck);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszEntityA);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszEntityB);
    SCHEMA_FIELD(float, m_flZone1Distance);
    SCHEMA_FIELD(float, m_flZone2Distance);
    SCHEMA_FIELD(CEntityIOOutput, m_InZone1);
    SCHEMA_FIELD(CEntityIOOutput, m_InZone2);
    SCHEMA_FIELD(CEntityIOOutput, m_InZone3);
};
