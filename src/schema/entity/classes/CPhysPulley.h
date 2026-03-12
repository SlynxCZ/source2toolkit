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

#include "CPhysConstraint.h"

class CPhysPulley : public CPhysConstraint, public CBaseEntity::Factory<CPhysPulley>
{
public:
    DECLARE_SCHEMA_CLASS(CPhysPulley);

    SCHEMA_FIELD(Vector, m_position2);
    SCHEMA_FIELD_POINTER(Vector, m_offset);
    SCHEMA_FIELD(float, m_addLength);
    SCHEMA_FIELD(float, m_gearRatio);
};
