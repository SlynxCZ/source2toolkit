#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CServerOnlyPointEntity.h"

class CPointTeleport : public CServerOnlyPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPointTeleport);

    SCHEMA_FIELD(Vector, m_vSaveOrigin);
    SCHEMA_FIELD(QAngle, m_vSaveAngles);
    SCHEMA_FIELD(bool, m_bTeleportParentedEntities);
    SCHEMA_FIELD(bool, m_bTeleportUseCurrentAngle);
};
