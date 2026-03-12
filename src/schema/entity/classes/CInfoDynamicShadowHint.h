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

class CBaseEntity;

class CInfoDynamicShadowHint : public CPointEntity, public CBaseEntity::Factory<CInfoDynamicShadowHint>
{
public:
    DECLARE_SCHEMA_CLASS(CInfoDynamicShadowHint);

    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(float, m_flRange);
    SCHEMA_FIELD(int32_t, m_nImportance);
    SCHEMA_FIELD(int32_t, m_nLightChoice);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hLight);
};
