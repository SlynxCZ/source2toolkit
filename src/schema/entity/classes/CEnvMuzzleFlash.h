#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CEnvMuzzleFlash : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvMuzzleFlash);

    SCHEMA_FIELD(float, m_flScale);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszParentAttachment);
};
