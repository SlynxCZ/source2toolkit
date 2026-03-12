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

class CPlayer_ItemServices : public CPlayerPawnComponent, public CBaseEntity::Factory<CPlayer_ItemServices>
{
public:
    DECLARE_SCHEMA_CLASS(CPlayer_ItemServices);

};
