#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"

class CFuncVPhysicsClip : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CFuncVPhysicsClip);

    SCHEMA_FIELD(bool, m_bDisabled);
};
