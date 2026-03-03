#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CCSWeaponBaseShotgun.h"

class CWeaponSawedoff : public CCSWeaponBaseShotgun
{
public:
    DECLARE_SCHEMA_CLASS(CWeaponSawedoff);

};
