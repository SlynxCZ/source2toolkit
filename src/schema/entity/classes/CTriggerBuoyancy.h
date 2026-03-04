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
#include "CBuoyancyHelper.h"

class CTriggerBuoyancy : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerBuoyancy);

    SCHEMA_FIELD(CBuoyancyHelper, m_BuoyancyHelper);
    SCHEMA_FIELD(float, m_flFluidDensity);
};
