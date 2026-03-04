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

#include "CBaseTrigger.h"

class CBuyZone : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CBuyZone);

    SCHEMA_FIELD(int32_t, m_LegacyTeamNum);
};
