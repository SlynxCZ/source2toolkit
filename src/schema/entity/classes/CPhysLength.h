#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPhysConstraint.h"

class CPhysLength : public CPhysConstraint
{
public:
    DECLARE_SCHEMA_CLASS(CPhysLength);

    SCHEMA_FIELD_POINTER(Vector, m_offset);
    SCHEMA_FIELD(Vector, m_vecAttach);
    SCHEMA_FIELD(float, m_addLength);
    SCHEMA_FIELD(float, m_minLength);
    SCHEMA_FIELD(float, m_totalLength);
};
