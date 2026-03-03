#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CCSWeaponBase.h"

class CKnife : public CCSWeaponBase
{
public:
    DECLARE_SCHEMA_CLASS(CKnife);

    SCHEMA_FIELD(bool, m_bFirstAttack);
};
