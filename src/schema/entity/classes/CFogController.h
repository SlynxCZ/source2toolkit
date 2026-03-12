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
#include "fogparams_t.h"

class CFogController : public CBaseEntity, public CBaseEntity::Factory<CFogController>
{
public:
    DECLARE_SCHEMA_CLASS(CFogController);

    SCHEMA_FIELD(fogparams_t, m_fog);
    SCHEMA_FIELD(bool, m_bUseAngles);
    SCHEMA_FIELD(int32_t, m_iChangedVariables);
};
