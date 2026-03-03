#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CRagdollMagnet : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CRagdollMagnet);

    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(float, m_radius);
    SCHEMA_FIELD(float, m_force);
    SCHEMA_FIELD(Vector, m_axis);
};
