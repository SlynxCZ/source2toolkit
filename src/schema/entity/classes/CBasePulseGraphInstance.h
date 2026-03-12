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

class CBasePulseGraphInstance : public CBaseEntity::Factory<CBasePulseGraphInstance>
{
public:
    DECLARE_SCHEMA_CLASS(CBasePulseGraphInstance);

};
