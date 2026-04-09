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

class CWeaponAug : public CCSWeaponBaseGun
{
public:
    DECLARE_SCHEMA_CLASS(CWeaponAug);


public:
    static CWeaponAug* New(const char* className)
    {
        return CBaseEntity::New<CWeaponAug>(className);
    }
};
