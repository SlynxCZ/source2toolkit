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

class CPulseGameBlackboard : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPulseGameBlackboard);

    SCHEMA_FIELD(CUtlString, m_strGraphName);
    SCHEMA_FIELD(CUtlString, m_strStateBlob);
};
