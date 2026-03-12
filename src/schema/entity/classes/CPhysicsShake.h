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

class CPhysicsShake : public CBaseEntity::Factory<CPhysicsShake>
{
public:
    DECLARE_SCHEMA_CLASS(CPhysicsShake);

    SCHEMA_FIELD(Vector, m_force);
};
