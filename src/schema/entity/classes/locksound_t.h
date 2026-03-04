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

class locksound_t
{
public:
    DECLARE_SCHEMA_CLASS(locksound_t);

    SCHEMA_FIELD(CUtlSymbolLarge, sLockedSound);
    SCHEMA_FIELD(CUtlSymbolLarge, sUnlockedSound);
    SCHEMA_FIELD(float, flwaitSound);
};
