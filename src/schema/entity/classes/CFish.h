#pragma once
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
#include "CountdownTimer.h"

class CFishPool;

class CFish : public CBaseAnimGraph
{
public:
    DECLARE_SCHEMA_CLASS(CFish);

    SCHEMA_FIELD(CHandle<CFishPool>, m_pool);
    SCHEMA_FIELD(uint32_t, m_id);
    SCHEMA_FIELD(float, m_x);
    SCHEMA_FIELD(float, m_y);
    SCHEMA_FIELD(float, m_z);
    SCHEMA_FIELD(float, m_angle);
    SCHEMA_FIELD(float, m_angleChange);
    SCHEMA_FIELD(Vector, m_forward);
    SCHEMA_FIELD(Vector, m_perp);
    SCHEMA_FIELD(Vector, m_poolOrigin);
    SCHEMA_FIELD(float, m_waterLevel);
    SCHEMA_FIELD(float, m_speed);
    SCHEMA_FIELD(float, m_desiredSpeed);
    SCHEMA_FIELD(float, m_calmSpeed);
    SCHEMA_FIELD(float, m_panicSpeed);
    SCHEMA_FIELD(float, m_avoidRange);
    SCHEMA_FIELD(CountdownTimer, m_turnTimer);
    SCHEMA_FIELD(bool, m_turnClockwise);
    SCHEMA_FIELD(CountdownTimer, m_goTimer);
    SCHEMA_FIELD(CountdownTimer, m_moveTimer);
    SCHEMA_FIELD(CountdownTimer, m_panicTimer);
    SCHEMA_FIELD(CountdownTimer, m_disperseTimer);
    SCHEMA_FIELD(CountdownTimer, m_proximityTimer);
    SCHEMA_FIELD(CUtlVector<CFish*>, m_visible);
};
