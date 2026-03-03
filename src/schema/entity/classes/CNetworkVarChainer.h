#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "ChangeAccessorFieldPathIndex_t.h"

class CNetworkVarChainer
{
public:
    DECLARE_SCHEMA_CLASS(CNetworkVarChainer);

    SCHEMA_FIELD(ChangeAccessorFieldPathIndex_t, m_PathIndex);
};
