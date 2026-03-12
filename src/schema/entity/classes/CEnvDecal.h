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

#include "CBaseModelEntity.h"
#include "InfoForResourceTypeIMaterial2.h"

class CEnvDecal : public CBaseModelEntity, public CBaseEntity::Factory<CEnvDecal>
{
public:
    DECLARE_SCHEMA_CLASS(CEnvDecal);

    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeIMaterial2 >, m_hDecalMaterial);
    SCHEMA_FIELD(float, m_flWidth);
    SCHEMA_FIELD(float, m_flHeight);
    SCHEMA_FIELD(float, m_flDepth);
    SCHEMA_FIELD(uint32_t, m_nRenderOrder);
    SCHEMA_FIELD(bool, m_bProjectOnWorld);
    SCHEMA_FIELD(bool, m_bProjectOnCharacters);
    SCHEMA_FIELD(bool, m_bProjectOnWater);
    SCHEMA_FIELD(float, m_flDepthSortBias);
};
