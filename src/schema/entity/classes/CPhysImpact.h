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

#include "CPointEntity.h"

class CPhysImpact : public CPointEntity, public CBaseEntity::Factory<CPhysImpact>
{
public:
    DECLARE_SCHEMA_CLASS(CPhysImpact);

    SCHEMA_FIELD(float, m_damage);
    SCHEMA_FIELD(float, m_distance);
    SCHEMA_FIELD(CUtlSymbolLarge, m_directionEntityName);
};
