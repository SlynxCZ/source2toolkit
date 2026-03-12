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

#include "CServerOnlyPointEntity.h"

class SpawnPoint : public CServerOnlyPointEntity, public CBaseEntity::Factory<SpawnPoint>
{
public:
    DECLARE_SCHEMA_CLASS(SpawnPoint);

    SCHEMA_FIELD(int32_t, m_iPriority);
    SCHEMA_FIELD(bool, m_bEnabled);
    SCHEMA_FIELD(int32_t, m_nType);
};
