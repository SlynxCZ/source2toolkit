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

class ragdollelement_t
{
public:
    DECLARE_SCHEMA_CLASS(ragdollelement_t);

    SCHEMA_FIELD(Vector, originParentSpace);
    SCHEMA_FIELD(int32_t, parentIndex);
    SCHEMA_FIELD(float, m_flRadius);
    SCHEMA_FIELD(int32_t, m_nHeight);
};
