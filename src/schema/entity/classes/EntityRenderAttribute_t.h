#pragma once
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

class EntityRenderAttribute_t : public CBaseEntity::Factory<EntityRenderAttribute_t>
{
public:
    DECLARE_SCHEMA_CLASS(EntityRenderAttribute_t);

    SCHEMA_FIELD_POINTER(CUtlStringToken, m_ID);
    SCHEMA_FIELD(Vector4D, m_Values);
};
