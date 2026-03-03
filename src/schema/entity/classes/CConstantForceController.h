#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CConstantForceController
{
public:
    DECLARE_SCHEMA_CLASS(CConstantForceController);

    SCHEMA_FIELD(Vector, m_linear);
    SCHEMA_FIELD(RotationVector, m_angular);
    SCHEMA_FIELD(Vector, m_linearSave);
    SCHEMA_FIELD(RotationVector, m_angularSave);
};
