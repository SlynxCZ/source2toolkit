#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPhysicsProp.h"
#include "shard_model_desc_t.h"

class CShatterGlassShardPhysics : public CPhysicsProp
{
public:
    DECLARE_SCHEMA_CLASS(CShatterGlassShardPhysics);

    SCHEMA_FIELD(bool, m_bDebris);
    SCHEMA_FIELD(uint32_t, m_hParentShard);
    SCHEMA_FIELD(shard_model_desc_t, m_ShardDesc);
};
