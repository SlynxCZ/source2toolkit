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

class CLogicGameEvent : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicGameEvent);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszEventName);
};
