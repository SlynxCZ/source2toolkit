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

#include "CPhysicsProp.h"

class CPhysicsPropRespawnable : public CPhysicsProp
{
public:
    DECLARE_SCHEMA_CLASS(CPhysicsPropRespawnable);

    SCHEMA_FIELD(Vector, m_vOriginalSpawnOrigin);
    SCHEMA_FIELD(QAngle, m_vOriginalSpawnAngles);
    SCHEMA_FIELD(Vector, m_vOriginalMins);
    SCHEMA_FIELD(Vector, m_vOriginalMaxs);
    SCHEMA_FIELD(float, m_flRespawnDuration);
};
