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

#include "CMarkupVolumeTagged.h"
#include "../enums/NavScopeFlags_t.h"

class CMarkupVolumeTagged_Nav : public CMarkupVolumeTagged, public CBaseEntity::Factory<CMarkupVolumeTagged_Nav>
{
public:
    DECLARE_SCHEMA_CLASS(CMarkupVolumeTagged_Nav);

    SCHEMA_FIELD(NavScopeFlags_t, m_nScopes);
};
