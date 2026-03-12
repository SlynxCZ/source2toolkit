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

#include "CRopeKeyframe.h"

class CRopeKeyframeAlias_move_rope : public CRopeKeyframe, public CBaseEntity::Factory<CRopeKeyframeAlias_move_rope>
{
public:
    DECLARE_SCHEMA_CLASS(CRopeKeyframeAlias_move_rope);

};
