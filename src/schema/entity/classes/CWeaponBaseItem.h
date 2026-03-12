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

#include "CCSWeaponBase.h"

class CWeaponBaseItem : public CCSWeaponBase, public CBaseEntity::Factory<CWeaponBaseItem>
{
public:
    DECLARE_SCHEMA_CLASS(CWeaponBaseItem);

    SCHEMA_FIELD(bool, m_bSequenceInProgress);
    SCHEMA_FIELD(bool, m_bRedraw);
};
