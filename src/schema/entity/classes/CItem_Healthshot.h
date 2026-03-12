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

#include "CWeaponBaseItem.h"

class CItem_Healthshot : public CWeaponBaseItem, public CBaseEntity::Factory<CItem_Healthshot>
{
public:
    DECLARE_SCHEMA_CLASS(CItem_Healthshot);

};
