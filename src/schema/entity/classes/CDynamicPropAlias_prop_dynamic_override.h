#pragma once
#include "CBaseEntity.h"
#include "igameevents.h"
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

#include "CDynamicProp.h"

class CDynamicPropAlias_prop_dynamic_override : public CDynamicProp, public CBaseEntity::Factory<CDynamicPropAlias_prop_dynamic_override>
{
public:
    DECLARE_SCHEMA_CLASS(CDynamicPropAlias_prop_dynamic_override);

};
