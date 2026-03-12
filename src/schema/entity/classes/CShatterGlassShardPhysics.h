#pragma once
#include "CBaseEntity.h"
#include "igameevents.h"
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

#include "CPhysicsProp.h"
#include "shard_model_desc_t.h"

class CShatterGlassShardPhysics : public CPhysicsProp, public CBaseEntity::Factory<CShatterGlassShardPhysics>
{
public:
    DECLARE_SCHEMA_CLASS(CShatterGlassShardPhysics);

    SCHEMA_FIELD(bool, m_bDebris);
    SCHEMA_FIELD(uint32_t, m_hParentShard);
    SCHEMA_FIELD(shard_model_desc_t, m_ShardDesc);
};
