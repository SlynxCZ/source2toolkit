#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CEnvViewPunch : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvViewPunch);

    SCHEMA_FIELD(float, m_flRadius);
    SCHEMA_FIELD(QAngle, m_angViewPunch);
};
