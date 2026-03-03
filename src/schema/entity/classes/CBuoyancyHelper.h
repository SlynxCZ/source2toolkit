#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CBuoyancyHelper
{
public:
    DECLARE_SCHEMA_CLASS(CBuoyancyHelper);

    SCHEMA_FIELD(CUtlStringToken, m_nFluidType);
    SCHEMA_FIELD(float, m_flFluidDensity);
    SCHEMA_FIELD(float, m_flNeutrallyBuoyantGravity);
    SCHEMA_FIELD(float, m_flNeutrallyBuoyantLinearDamping);
    SCHEMA_FIELD(float, m_flNeutrallyBuoyantAngularDamping);
    SCHEMA_FIELD(bool, m_bNeutrallyBuoyant);
    SCHEMA_FIELD(CUtlVector<float>, m_vecFractionOfWheelSubmergedForWheelFriction);
    SCHEMA_FIELD(CUtlVector<float>, m_vecWheelFrictionScales);
    SCHEMA_FIELD(CUtlVector<float>, m_vecFractionOfWheelSubmergedForWheelDrag);
    SCHEMA_FIELD(CUtlVector<float>, m_vecWheelDrag);
};
