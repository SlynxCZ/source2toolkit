#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CMarkupVolumeTagged.h"
#include "../enums/NavScopeFlags_t.h"

class CMarkupVolumeTagged_Nav : public CMarkupVolumeTagged
{
public:
    DECLARE_SCHEMA_CLASS(CMarkupVolumeTagged_Nav);

    SCHEMA_FIELD(NavScopeFlags_t, m_nScopes);
};
