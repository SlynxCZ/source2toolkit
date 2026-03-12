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

#include "CBaseDoor.h"

class CRotDoor : public CBaseDoor, public CBaseEntity::Factory<CRotDoor>
{
public:
    DECLARE_SCHEMA_CLASS(CRotDoor);

    SCHEMA_FIELD(bool, m_bSolidBsp);
};
