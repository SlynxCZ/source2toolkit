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

#include "CPointEntity.h"
#include "../enums/DamageTypes_t.h"

class CBaseEntity;

class CPointHurt : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPointHurt);

    SCHEMA_FIELD(int32_t, m_nDamage);
    SCHEMA_FIELD(DamageTypes_t, m_bitsDamageType);
    SCHEMA_FIELD(float, m_flRadius);
    SCHEMA_FIELD(float, m_flDelay);
    SCHEMA_FIELD(CUtlSymbolLarge, m_strTarget);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_pActivator);
};
