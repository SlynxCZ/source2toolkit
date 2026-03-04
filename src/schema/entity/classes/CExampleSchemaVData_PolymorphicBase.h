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

class CExampleSchemaVData_PolymorphicBase
{
public:
    DECLARE_SCHEMA_CLASS(CExampleSchemaVData_PolymorphicBase);

    SCHEMA_FIELD(int32_t, m_nBase);
};
