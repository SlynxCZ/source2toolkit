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

#include "CBaseEntity.h"

class CEnableMotionFixup : public CBaseEntity, public CBaseEntity::Factory<CEnableMotionFixup>
{
public:
    DECLARE_SCHEMA_CLASS(CEnableMotionFixup);

};
