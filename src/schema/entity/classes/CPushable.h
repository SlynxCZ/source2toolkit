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

#include "CBreakable.h"

class CPushable : public CBreakable
{
public:
    DECLARE_SCHEMA_CLASS(CPushable);


public:
    static CPushable* New(const char* className)
    {
        return CBaseEntity::New<CPushable>(className);
    }
};
