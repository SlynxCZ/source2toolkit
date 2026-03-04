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

#include "CDynamicProp.h"

class COrnamentProp : public CDynamicProp
{
public:
    DECLARE_SCHEMA_CLASS(COrnamentProp);

    SCHEMA_FIELD(CUtlSymbolLarge, m_initialOwner);
};
