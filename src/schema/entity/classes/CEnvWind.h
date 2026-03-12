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
#include "CEnvWindShared.h"

class CEnvWind : public CBaseEntity, public CBaseEntity::Factory<CEnvWind>
{
public:
    DECLARE_SCHEMA_CLASS(CEnvWind);

    SCHEMA_FIELD(CEnvWindShared, m_EnvWindShared);
};
