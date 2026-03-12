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

class CEnvSplash : public CPointEntity, public CBaseEntity::Factory<CEnvSplash>
{
public:
    DECLARE_SCHEMA_CLASS(CEnvSplash);

    SCHEMA_FIELD(float, m_flScale);
};
