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

#include "CFuncMoveLinear.h"

class CFuncMoveLinearAlias_momentary_door : public CFuncMoveLinear, public CBaseEntity::Factory<CFuncMoveLinearAlias_momentary_door>
{
public:
    DECLARE_SCHEMA_CLASS(CFuncMoveLinearAlias_momentary_door);

};
