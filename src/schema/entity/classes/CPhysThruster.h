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

#include "CPhysForce.h"

class CPhysThruster : public CPhysForce, public CBaseEntity::Factory<CPhysThruster>
{
public:
    DECLARE_SCHEMA_CLASS(CPhysThruster);

    SCHEMA_FIELD(Vector, m_localOrigin);
};
