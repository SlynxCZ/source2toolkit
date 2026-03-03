#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CBaseEntity;

class PhysicsRagdollPose_t
{
public:
    DECLARE_SCHEMA_CLASS(PhysicsRagdollPose_t);

    SCHEMA_FIELD(CUtlVector<CTransform>, m_Transforms);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hOwner);
    SCHEMA_FIELD(bool, m_bSetFromDebugHistory);
};
