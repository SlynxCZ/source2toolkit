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

#include "CLogicalEntity.h"
#include "../enums/navproperties_t.h"

class CLogicNavigation : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicNavigation);

    SCHEMA_FIELD(bool, m_isOn);
    SCHEMA_FIELD(navproperties_t, m_navProperty);
};
