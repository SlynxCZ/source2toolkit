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

class ragdollhierarchyjoint_t
{
public:
    DECLARE_SCHEMA_CLASS(ragdollhierarchyjoint_t);

    SCHEMA_FIELD(int32_t, parentIndex);
    SCHEMA_FIELD(int32_t, childIndex);
};
