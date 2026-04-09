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

#include "CCSWeaponBaseGun.h"

class CWeaponM4A1Silencer : public CCSWeaponBaseGun
{
public:
    DECLARE_SCHEMA_CLASS(CWeaponM4A1Silencer);


public:
    static CWeaponM4A1Silencer* New(const char* className)
    {
        return CBaseEntity::New<CWeaponM4A1Silencer>(className);
    }
};
