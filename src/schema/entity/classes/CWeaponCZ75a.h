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

class CWeaponCZ75a : public CCSWeaponBaseGun, public CBaseEntity::Factory<CWeaponCZ75a>
{
public:
    DECLARE_SCHEMA_CLASS(CWeaponCZ75a);

    SCHEMA_FIELD(bool, m_bMagazineRemoved);
};
