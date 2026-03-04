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

class CFiringModeInt
{
public:
    DECLARE_SCHEMA_CLASS(CFiringModeInt);

    SCHEMA_FIELD_POINTER(int32_t, m_nValues);
};
