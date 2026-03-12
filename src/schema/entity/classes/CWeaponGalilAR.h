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

#include "CCSWeaponBaseGun.h"

class CWeaponGalilAR : public CCSWeaponBaseGun, public CBaseEntity::Factory<CWeaponGalilAR>
{
public:
    DECLARE_SCHEMA_CLASS(CWeaponGalilAR);

};
