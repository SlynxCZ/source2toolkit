#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CInfoGameEventProxy : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CInfoGameEventProxy);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszEventName);
    SCHEMA_FIELD(float, m_flRange);
};
