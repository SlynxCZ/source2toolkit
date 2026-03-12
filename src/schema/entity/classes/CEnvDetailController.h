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

class CEnvDetailController : public CBaseEntity, public CBaseEntity::Factory<CEnvDetailController>
{
public:
    DECLARE_SCHEMA_CLASS(CEnvDetailController);

    SCHEMA_FIELD(float, m_flFadeStartDist);
    SCHEMA_FIELD(float, m_flFadeEndDist);
};
