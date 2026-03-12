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

class CExampleSchemaVData_Monomorphic : public CBaseEntity::Factory<CExampleSchemaVData_Monomorphic>
{
public:
    DECLARE_SCHEMA_CLASS(CExampleSchemaVData_Monomorphic);

    SCHEMA_FIELD(int32_t, m_nExample1);
    SCHEMA_FIELD(int32_t, m_nExample2);
};
