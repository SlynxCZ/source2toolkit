#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CPhysicsShake
{
public:
    DECLARE_SCHEMA_CLASS(CPhysicsShake);

    SCHEMA_FIELD(Vector, m_force);
};
