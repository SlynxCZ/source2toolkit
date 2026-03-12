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

#include "CLogicalEntity.h"

class CBaseEntity;

class CPhysicsEntitySolver : public CLogicalEntity, public CBaseEntity::Factory<CPhysicsEntitySolver>
{
public:
    DECLARE_SCHEMA_CLASS(CPhysicsEntitySolver);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hMovingEntity);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hPhysicsBlocker);
    SCHEMA_FIELD(float, m_separationDuration);
    SCHEMA_FIELD(float, m_cancelTime);
};
