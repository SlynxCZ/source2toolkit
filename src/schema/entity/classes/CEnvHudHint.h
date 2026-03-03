#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CEnvHudHint : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvHudHint);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszMessage);
};
