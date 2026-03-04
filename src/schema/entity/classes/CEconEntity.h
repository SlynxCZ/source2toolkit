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

#include "CAttributeContainer.h"
#include "CBaseFlex.h"

class CBaseEntity;

class CEconEntity : public CBaseFlex
{
public:
    DECLARE_SCHEMA_CLASS(CEconEntity);

    SCHEMA_FIELD(CAttributeContainer, m_AttributeManager);
    SCHEMA_FIELD(uint32_t, m_OriginalOwnerXuidLow);
    SCHEMA_FIELD(uint32_t, m_OriginalOwnerXuidHigh);
    SCHEMA_FIELD(int32_t, m_nFallbackPaintKit);
    SCHEMA_FIELD(int32_t, m_nFallbackSeed);
    SCHEMA_FIELD(float, m_flFallbackWear);
    SCHEMA_FIELD(int32_t, m_nFallbackStatTrak);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hOldProvidee);
    SCHEMA_FIELD(int32_t, m_iOldOwnerClass);
};
