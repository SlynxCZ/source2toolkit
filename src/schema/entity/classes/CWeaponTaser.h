#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CCSWeaponBaseGun.h"

class CWeaponTaser : public CCSWeaponBaseGun
{
public:
    DECLARE_SCHEMA_CLASS(CWeaponTaser);

    SCHEMA_FIELD(float, m_fFireTime);
    SCHEMA_FIELD(int32_t, m_nLastAttackTick);
};
