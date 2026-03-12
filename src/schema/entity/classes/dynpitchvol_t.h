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

#include "dynpitchvol_base_t.h"

class dynpitchvol_t : public dynpitchvol_base_t, public CBaseEntity::Factory<dynpitchvol_t>
{
public:
    DECLARE_SCHEMA_CLASS(dynpitchvol_t);

};
