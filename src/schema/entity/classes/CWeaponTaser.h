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

class CWeaponTaser : public CCSWeaponBaseGun, public CBaseEntity::Factory<CWeaponTaser>
{
public:
    DECLARE_SCHEMA_CLASS(CWeaponTaser);

    SCHEMA_FIELD(float, m_fFireTime);
    SCHEMA_FIELD(int32_t, m_nLastAttackTick);
};
