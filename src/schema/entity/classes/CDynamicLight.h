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

#include "CBaseModelEntity.h"

class CDynamicLight : public CBaseModelEntity, public CBaseEntity::Factory<CDynamicLight>
{
public:
    DECLARE_SCHEMA_CLASS(CDynamicLight);

    SCHEMA_FIELD(uint8_t, m_ActualFlags);
    SCHEMA_FIELD(uint8_t, m_Flags);
    SCHEMA_FIELD(uint8_t, m_LightStyle);
    SCHEMA_FIELD(bool, m_On);
    SCHEMA_FIELD(float, m_Radius);
    SCHEMA_FIELD(int32_t, m_Exponent);
    SCHEMA_FIELD(float, m_InnerAngle);
    SCHEMA_FIELD(float, m_OuterAngle);
    SCHEMA_FIELD(float, m_SpotRadius);
};
