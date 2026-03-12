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

#include "CTonemapController2.h"

class CTonemapController2Alias_env_tonemap_controller2 : public CTonemapController2, public CBaseEntity::Factory<CTonemapController2Alias_env_tonemap_controller2>
{
public:
    DECLARE_SCHEMA_CLASS(CTonemapController2Alias_env_tonemap_controller2);

};
