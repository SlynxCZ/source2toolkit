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

#include "CTriggerMultiple.h"

class CTriggerImpact : public CTriggerMultiple, public CBaseEntity::Factory<CTriggerImpact>
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerImpact);

    SCHEMA_FIELD(float, m_flMagnitude);
    SCHEMA_FIELD(float, m_flNoise);
    SCHEMA_FIELD(float, m_flViewkick);
};
