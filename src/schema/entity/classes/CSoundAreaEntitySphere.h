#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CSoundAreaEntityBase.h"

class CSoundAreaEntitySphere : public CSoundAreaEntityBase
{
public:
    DECLARE_SCHEMA_CLASS(CSoundAreaEntitySphere);

    SCHEMA_FIELD(float, m_flRadius);
};
