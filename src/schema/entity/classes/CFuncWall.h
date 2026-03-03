#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"

class CFuncWall : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CFuncWall);

    SCHEMA_FIELD(int32_t, m_nState);
};
