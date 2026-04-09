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

#include "CBaseAnimGraph.h"

class CItemSoda : public CBaseAnimGraph
{
public:
    DECLARE_SCHEMA_CLASS(CItemSoda);


public:
    static CItemSoda* New(const char* className)
    {
        return CBaseEntity::New<CItemSoda>(className);
    }
};
