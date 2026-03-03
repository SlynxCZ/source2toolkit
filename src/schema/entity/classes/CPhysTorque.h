#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPhysForce.h"

class CPhysTorque : public CPhysForce
{
public:
    DECLARE_SCHEMA_CLASS(CPhysTorque);

    SCHEMA_FIELD(Vector, m_axis);
};
