#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CCSWeaponBaseGun.h"

class CWeaponUSPSilencer : public CCSWeaponBaseGun
{
public:
    DECLARE_SCHEMA_CLASS(CWeaponUSPSilencer);

};
