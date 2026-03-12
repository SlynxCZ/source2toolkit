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

#include "CPlayerPawnComponent.h"

class CCSPlayer_DamageReactServices : public CPlayerPawnComponent, public CBaseEntity::Factory<CCSPlayer_DamageReactServices>
{
public:
    DECLARE_SCHEMA_CLASS(CCSPlayer_DamageReactServices);

};
