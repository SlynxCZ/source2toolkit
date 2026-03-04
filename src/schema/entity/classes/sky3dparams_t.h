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

#include "fogparams_t.h"

class sky3dparams_t
{
public:
    DECLARE_SCHEMA_CLASS(sky3dparams_t);

    SCHEMA_FIELD(int16_t, scale);
    SCHEMA_FIELD(Vector, origin);
    SCHEMA_FIELD(bool, bClip3DSkyBoxNearToWorldFar);
    SCHEMA_FIELD(float, flClip3DSkyBoxNearToWorldFarOffset);
    SCHEMA_FIELD(fogparams_t, fog);
    SCHEMA_FIELD(WorldGroupId_t, m_nWorldGroupID);
};
