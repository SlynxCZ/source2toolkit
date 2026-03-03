#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CCSWeaponBaseGun.h"

class CWeaponCZ75a : public CCSWeaponBaseGun
{
public:
    DECLARE_SCHEMA_CLASS(CWeaponCZ75a);

    SCHEMA_FIELD(bool, m_bMagazineRemoved);
};
