#pragma once
#include "igameevents.h"
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

#include "ExternalAnimGraphHandle_t.h"

class CAnimGraphControllerBase
{
public:
    DECLARE_SCHEMA_CLASS(CAnimGraphControllerBase);

    SCHEMA_FIELD(ExternalAnimGraphHandle_t, m_hExternalGraph);
};
