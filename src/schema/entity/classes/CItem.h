#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseAnimGraph.h"

class CItem : public CBaseAnimGraph
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
