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

#include "CPointEntity.h"
#include "../enums/RotatorTargetSpace_t.h"

class CRotatorTarget : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CRotatorTarget);

    SCHEMA_FIELD(CEntityIOOutput, m_OnArrivedAt);
    SCHEMA_FIELD(RotatorTargetSpace_t, m_eSpace);
};
