#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPhysConstraint.h"

class CRagdollConstraint : public CPhysConstraint
{
public:
    DECLARE_SCHEMA_CLASS(CRagdollConstraint);

    SCHEMA_FIELD(float, m_xmin);
    SCHEMA_FIELD(float, m_xmax);
    SCHEMA_FIELD(float, m_ymin);
    SCHEMA_FIELD(float, m_ymax);
    SCHEMA_FIELD(float, m_zmin);
    SCHEMA_FIELD(float, m_zmax);
    SCHEMA_FIELD(float, m_xfriction);
    SCHEMA_FIELD(float, m_yfriction);
    SCHEMA_FIELD(float, m_zfriction);
};
