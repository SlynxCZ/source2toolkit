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

#include "CBaseCSGrenadeProjectile.h"

class CDecoyProjectile : public CBaseCSGrenadeProjectile, public CBaseEntity::Factory<CDecoyProjectile>
{
public:
    DECLARE_SCHEMA_CLASS(CDecoyProjectile);

    SCHEMA_FIELD(int32_t, m_nDecoyShotTick);
    SCHEMA_FIELD(int32_t, m_shotsRemaining);
    SCHEMA_FIELD(float, m_fExpireTime);
    SCHEMA_FIELD(uint16_t, m_decoyWeaponDefIndex);
};
