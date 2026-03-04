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

class CLogicCase : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicCase);

    SCHEMA_FIELD_POINTER(CUtlSymbolLarge, m_nCase);
    SCHEMA_FIELD(int32_t, m_nShuffleCases);
    SCHEMA_FIELD(int32_t, m_nLastShuffleCase);
    SCHEMA_FIELD_POINTER(uint8_t, m_uchShuffleCaseMap);
    SCHEMA_FIELD_POINTER(CEntityIOOutput, m_OnCase);
};
