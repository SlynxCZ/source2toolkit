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

class CPulseGameBlackboard : public CBaseEntity, public CBaseEntity::Factory<CPulseGameBlackboard>
{
public:
    DECLARE_SCHEMA_CLASS(CPulseGameBlackboard);

    SCHEMA_FIELD(CUtlString, m_strGraphName);
    SCHEMA_FIELD(CUtlString, m_strStateBlob);
};
