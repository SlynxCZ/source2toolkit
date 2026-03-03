#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CEnvGlobal : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvGlobal);

    SCHEMA_FIELD(CUtlSymbolLarge, m_globalstate);
    SCHEMA_FIELD(int32_t, m_triggermode);
    SCHEMA_FIELD(int32_t, m_initialstate);
    SCHEMA_FIELD(int32_t, m_counter);
};
