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

class CRopeKeyframeAlias_move_rope : public CRopeKeyframe
{
public:
    DECLARE_SCHEMA_CLASS(CRopeKeyframeAlias_move_rope);


public:
    static CRopeKeyframeAlias_move_rope* New(const char* className)
    {
        return CBaseEntity::New<CRopeKeyframeAlias_move_rope>(className);
    }
};
