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

#include "CPointEntity.h"

class CEnvMuzzleFlash : public CPointEntity, public CBaseEntity::Factory<CEnvMuzzleFlash>
{
public:
    DECLARE_SCHEMA_CLASS(CEnvMuzzleFlash);

    SCHEMA_FIELD(float, m_flScale);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszParentAttachment);
};
