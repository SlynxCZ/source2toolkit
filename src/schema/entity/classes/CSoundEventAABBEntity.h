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

class CSoundEventAABBEntity : public CSoundEventEntity, public CBaseEntity::Factory<CSoundEventAABBEntity>
{
public:
    DECLARE_SCHEMA_CLASS(CSoundEventAABBEntity);

    SCHEMA_FIELD(Vector, m_vMins);
    SCHEMA_FIELD(Vector, m_vMaxs);
};
