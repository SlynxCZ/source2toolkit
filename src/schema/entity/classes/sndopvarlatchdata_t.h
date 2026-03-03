#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class sndopvarlatchdata_t
{
public:
    DECLARE_SCHEMA_CLASS(sndopvarlatchdata_t);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszStack);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszOperator);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszOpvar);
    SCHEMA_FIELD(float, m_flVal);
    SCHEMA_FIELD(Vector, m_vPos);
};
