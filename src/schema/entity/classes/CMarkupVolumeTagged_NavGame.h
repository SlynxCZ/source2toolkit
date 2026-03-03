#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CMarkupVolumeWithRef.h"
#include "../enums/NavScopeFlags_t.h"

class CMarkupVolumeTagged_NavGame : public CMarkupVolumeWithRef
{
public:
    DECLARE_SCHEMA_CLASS(CMarkupVolumeTagged_NavGame);

    SCHEMA_FIELD(NavScopeFlags_t, m_nScopes);
    SCHEMA_FIELD(bool, m_bFloodFillAttribute);
    SCHEMA_FIELD(bool, m_bSplitNavSpace);
};
