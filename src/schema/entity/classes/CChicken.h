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

#include "CAttributeContainer.h"
#include "CDynamicProp.h"
#include "CountdownTimer.h"
#include "../enums/ChickenActivity.h"

class CBaseEntity;
class CCSPlayerPawn;

class CChicken : public CDynamicProp, public CBaseEntity::Factory<CChicken>
{
public:
    DECLARE_SCHEMA_CLASS(CChicken);

    SCHEMA_FIELD(CAttributeContainer, m_AttributeManager);
    SCHEMA_FIELD(CountdownTimer, m_updateTimer);
    SCHEMA_FIELD(Vector, m_stuckAnchor);
    SCHEMA_FIELD(CountdownTimer, m_stuckTimer);
    SCHEMA_FIELD(CountdownTimer, m_collisionStuckTimer);
    SCHEMA_FIELD(bool, m_isOnGround);
    SCHEMA_FIELD(Vector, m_vFallVelocity);
    SCHEMA_FIELD(ChickenActivity, m_desiredActivity);
    SCHEMA_FIELD(ChickenActivity, m_currentActivity);
    SCHEMA_FIELD(CountdownTimer, m_activityTimer);
    SCHEMA_FIELD(float, m_turnRate);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_fleeFrom);
    SCHEMA_FIELD(CountdownTimer, m_moveRateThrottleTimer);
    SCHEMA_FIELD(CountdownTimer, m_startleTimer);
    SCHEMA_FIELD(CountdownTimer, m_vocalizeTimer);
    SCHEMA_FIELD(float, m_flWhenZombified);
    SCHEMA_FIELD(bool, m_jumpedThisFrame);
    SCHEMA_FIELD(CHandle<CCSPlayerPawn>, m_leader);
    SCHEMA_FIELD(CountdownTimer, m_reuseTimer);
    SCHEMA_FIELD(bool, m_hasBeenUsed);
    SCHEMA_FIELD(CountdownTimer, m_jumpTimer);
    SCHEMA_FIELD(float, m_flLastJumpTime);
    SCHEMA_FIELD(bool, m_bInJump);
    SCHEMA_FIELD(CountdownTimer, m_repathTimer);
    SCHEMA_FIELD(Vector, m_vecPathGoal);
    SCHEMA_FIELD(float, m_flActiveFollowStartTime);
    SCHEMA_FIELD(CountdownTimer, m_followMinuteTimer);
    SCHEMA_FIELD(CountdownTimer, m_BlockDirectionTimer);
};
