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

#include "CPhysicsProp.h"

class CPhysicsPropMultiplayer : public CPhysicsProp
{
public:
    DECLARE_SCHEMA_CLASS(CPhysicsPropMultiplayer);


public:
    static CPhysicsPropMultiplayer* New(const char* className)
    {
        return CBaseEntity::New<CPhysicsPropMultiplayer>(className);
    }
};
