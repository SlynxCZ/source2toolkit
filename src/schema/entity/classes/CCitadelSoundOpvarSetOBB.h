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

class CCitadelSoundOpvarSetOBB : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CCitadelSoundOpvarSetOBB);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszStackName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszOperatorName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszOpvarName);
    SCHEMA_FIELD(Vector, m_vDistanceInnerMins);
    SCHEMA_FIELD(Vector, m_vDistanceInnerMaxs);
    SCHEMA_FIELD(Vector, m_vDistanceOuterMins);
    SCHEMA_FIELD(Vector, m_vDistanceOuterMaxs);
    SCHEMA_FIELD(int32_t, m_nAABBDirection);
};
