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

#include "CBaseEntity.h"

class CCSPlayerPawn;

class CPlayerPing : public CBaseEntity, public CBaseEntity::Factory<CPlayerPing>
{
public:
    DECLARE_SCHEMA_CLASS(CPlayerPing);

    SCHEMA_FIELD(CHandle<CCSPlayerPawn>, m_hPlayer);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hPingedEntity);
    SCHEMA_FIELD(int32_t, m_iType);
    SCHEMA_FIELD(bool, m_bUrgent);
    SCHEMA_FIELD_POINTER(char, m_szPlaceName);
};
