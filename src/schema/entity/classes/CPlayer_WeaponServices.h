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

#include "CPlayerPawnComponent.h"

class CBasePlayerWeapon;

class CPlayer_WeaponServices : public CPlayerPawnComponent, public CBaseEntity::Factory<CPlayer_WeaponServices>
{
public:
    DECLARE_SCHEMA_CLASS(CPlayer_WeaponServices);

    SCHEMA_FIELD(CUtlVector<CHandle<CBasePlayerWeapon>>, m_hMyWeapons);
    SCHEMA_FIELD(CHandle<CBasePlayerWeapon>, m_hActiveWeapon);
    SCHEMA_FIELD(CHandle<CBasePlayerWeapon>, m_hLastWeapon);
    SCHEMA_FIELD_POINTER(uint16_t, m_iAmmo);
    SCHEMA_FIELD(bool, m_bPreventWeaponPickup);
};
