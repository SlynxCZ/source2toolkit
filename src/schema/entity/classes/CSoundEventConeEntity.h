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

#include "CSoundEventEntity.h"

class CSoundEventConeEntity : public CSoundEventEntity, public CBaseEntity::Factory<CSoundEventConeEntity>
{
public:
    DECLARE_SCHEMA_CLASS(CSoundEventConeEntity);

    SCHEMA_FIELD(float, m_flEmitterAngle);
    SCHEMA_FIELD(float, m_flSweetSpotAngle);
    SCHEMA_FIELD(float, m_flAttenMin);
    SCHEMA_FIELD(float, m_flAttenMax);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszParameterName);
};
