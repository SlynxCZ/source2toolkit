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

class CWeaponUSPSilencer : public CCSWeaponBaseGun, public CBaseEntity::Factory<CWeaponUSPSilencer>
{
public:
    DECLARE_SCHEMA_CLASS(CWeaponUSPSilencer);

};
