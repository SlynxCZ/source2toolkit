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

#include "CBaseEntity.h"

class CPhysicsWire : public CBaseEntity, public CBaseEntity::Factory<CPhysicsWire>
{
public:
    DECLARE_SCHEMA_CLASS(CPhysicsWire);

    SCHEMA_FIELD(int32_t, m_nDensity);
};
