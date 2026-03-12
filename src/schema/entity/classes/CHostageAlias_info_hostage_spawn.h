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

#include "CHostage.h"

class CHostageAlias_info_hostage_spawn : public CHostage, public CBaseEntity::Factory<CHostageAlias_info_hostage_spawn>
{
public:
    DECLARE_SCHEMA_CLASS(CHostageAlias_info_hostage_spawn);

};
