#pragma once
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

class CMotorController
{
public:
    DECLARE_SCHEMA_CLASS(CMotorController);

    SCHEMA_FIELD(float, m_speed);
    SCHEMA_FIELD(float, m_maxTorque);
    SCHEMA_FIELD(Vector, m_axis);
    SCHEMA_FIELD(float, m_inertiaFactor);
};
