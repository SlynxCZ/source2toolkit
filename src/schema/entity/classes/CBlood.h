#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "../enums/BloodType.h"
#include "CPointEntity.h"

class CBlood : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CBlood);

    SCHEMA_FIELD(QAngle, m_vecSprayAngles);
    SCHEMA_FIELD(Vector, m_vecSprayDir);
    SCHEMA_FIELD(float, m_flAmount);
    SCHEMA_FIELD(BloodType, m_Color);
};
