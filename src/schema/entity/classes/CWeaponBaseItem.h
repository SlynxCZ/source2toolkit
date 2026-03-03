#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CCSWeaponBase.h"

class CWeaponBaseItem : public CCSWeaponBase
{
public:
    DECLARE_SCHEMA_CLASS(CWeaponBaseItem);

    SCHEMA_FIELD(bool, m_bSequenceInProgress);
    SCHEMA_FIELD(bool, m_bRedraw);
};
