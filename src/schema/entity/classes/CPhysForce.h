#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CConstantForceController.h"
#include "CPointEntity.h"

class CBaseEntity;

class CPhysForce : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPhysForce);

    SCHEMA_FIELD(CUtlSymbolLarge, m_nameAttach);
    SCHEMA_FIELD(float, m_force);
    SCHEMA_FIELD(float, m_forceTime);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_attachedObject);
    SCHEMA_FIELD(bool, m_wasRestored);
    SCHEMA_FIELD(CConstantForceController, m_integrator);
};
