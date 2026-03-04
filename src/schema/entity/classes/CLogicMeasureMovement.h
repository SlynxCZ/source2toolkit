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

class CLogicMeasureMovement : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicMeasureMovement);

    SCHEMA_FIELD(CUtlSymbolLarge, m_strMeasureTarget);
    SCHEMA_FIELD(CUtlSymbolLarge, m_strMeasureReference);
    SCHEMA_FIELD(CUtlSymbolLarge, m_strTargetReference);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hMeasureTarget);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hMeasureReference);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hTarget);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hTargetReference);
    SCHEMA_FIELD(float, m_flScale);
    SCHEMA_FIELD(int32_t, m_nMeasureType);
};
