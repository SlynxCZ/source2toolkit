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

class CSoundOpvarSetPointBase : public CBaseEntity, public CBaseEntity::Factory<CSoundOpvarSetPointBase>
{
public:
    DECLARE_SCHEMA_CLASS(CSoundOpvarSetPointBase);

    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(CEntityHandle, m_hSource);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszSourceEntityName);
    SCHEMA_FIELD(Vector, m_vLastPosition);
    SCHEMA_FIELD(float, m_flRefreshTime);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszStackName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszOperatorName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszOpvarName);
    SCHEMA_FIELD(int32_t, m_iOpvarIndex);
    SCHEMA_FIELD(bool, m_bUseAutoCompare);
    SCHEMA_FIELD(bool, m_bFastRefresh);
};
