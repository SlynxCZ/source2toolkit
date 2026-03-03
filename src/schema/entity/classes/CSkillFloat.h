#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CSkillFloat
{
public:
    DECLARE_SCHEMA_CLASS(CSkillFloat);

    SCHEMA_FIELD_POINTER(float, m_pValue);
};
