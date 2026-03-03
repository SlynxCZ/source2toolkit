#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CBaseEntity;

class CPhysicsEntitySolver : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPhysicsEntitySolver);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hMovingEntity);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hPhysicsBlocker);
    SCHEMA_FIELD(float, m_separationDuration);
    SCHEMA_FIELD(float, m_cancelTime);
};
