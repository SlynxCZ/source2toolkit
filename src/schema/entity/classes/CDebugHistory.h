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

class CDebugHistory : public CBaseEntity, public CBaseEntity::Factory<CDebugHistory>
{
public:
    DECLARE_SCHEMA_CLASS(CDebugHistory);

    SCHEMA_FIELD(int32_t, m_nNpcEvents);
};
