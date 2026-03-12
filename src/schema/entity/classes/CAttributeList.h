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

#include "CEconItemAttribute.h"

class CAttributeManager;

class CAttributeList
{
public:
    DECLARE_SCHEMA_CLASS(CAttributeList);

    SCHEMA_FIELD(CUtlVector<CEconItemAttribute>, m_Attributes);
    SCHEMA_FIELD(CAttributeManager*, m_pManager);
};
