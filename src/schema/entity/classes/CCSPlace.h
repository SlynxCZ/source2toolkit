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

#include "CServerOnlyModelEntity.h"

class CCSPlace : public CServerOnlyModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CCSPlace);

    SCHEMA_FIELD(CUtlSymbolLarge, m_name);
};
