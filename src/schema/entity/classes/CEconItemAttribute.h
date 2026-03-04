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

class CEconItemAttribute
{
public:
    DECLARE_SCHEMA_CLASS(CEconItemAttribute);

    SCHEMA_FIELD(uint16_t, m_iAttributeDefinitionIndex);
    SCHEMA_FIELD(float, m_flValue);
    SCHEMA_FIELD(float, m_flInitialValue);
    SCHEMA_FIELD(int32_t, m_nRefundableCurrency);
    SCHEMA_FIELD(bool, m_bSetBonus);
};
