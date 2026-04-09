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

#include "CBaseEntity.h"

class CPointEntity : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPointEntity);


public:
    static CPointEntity* New(const char* className)
    {
        return CBaseEntity::New<CPointEntity>(className);
    }
};
