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

#include "CEconEntity.h"

class CCSWeaponBase;
class CCSWeaponBaseVData;

class CBasePlayerWeapon : public CEconEntity, public CBaseEntity::Factory<CBasePlayerWeapon>
{
public:
    DECLARE_SCHEMA_CLASS(CBasePlayerWeapon);

    SCHEMA_FIELD(int32_t, m_nNextPrimaryAttackTick);
    SCHEMA_FIELD(float, m_flNextPrimaryAttackTickRatio);
    SCHEMA_FIELD(int32_t, m_nNextSecondaryAttackTick);
    SCHEMA_FIELD(float, m_flNextSecondaryAttackTickRatio);
    SCHEMA_FIELD(int32_t, m_iClip1);
    SCHEMA_FIELD(int32_t, m_iClip2);
    SCHEMA_FIELD_POINTER(int32_t, m_pReserveAmmo);
    SCHEMA_FIELD(CEntityIOOutput, m_OnPlayerUse);

public:
    /// <summary>Get weapon VData.</summary>
    CCSWeaponBaseVData* GetWeaponVData();
    /// <summary>Get weapon classname.</summary>
    const char* GetWeaponClassname();
};
