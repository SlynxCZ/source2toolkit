#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class EntityRenderAttribute_t
{
public:
    DECLARE_SCHEMA_CLASS(EntityRenderAttribute_t);

    SCHEMA_FIELD(CUtlStringToken, m_ID);
    SCHEMA_FIELD(Vector4D, m_Values);
};
