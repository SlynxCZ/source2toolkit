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

#include "CBaseAnimGraph.h"

class CItem : public CBaseAnimGraph, public CBaseEntity::Factory<CItem>
{
public:
    DECLARE_SCHEMA_CLASS(CItem);

    SCHEMA_FIELD(CEntityIOOutput, m_OnPlayerTouch);
    SCHEMA_FIELD(CEntityIOOutput, m_OnPlayerPickup);
    SCHEMA_FIELD(bool, m_bActivateWhenAtRest);
    SCHEMA_FIELD(CEntityIOOutput, m_OnCacheInteraction);
    SCHEMA_FIELD(CEntityIOOutput, m_OnGlovePulled);
    SCHEMA_FIELD(Vector, m_vOriginalSpawnOrigin);
    SCHEMA_FIELD(QAngle, m_vOriginalSpawnAngles);
    SCHEMA_FIELD(bool, m_bPhysStartAsleep);
};
