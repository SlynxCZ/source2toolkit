#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"
#include "../enums/PointOrientConstraint_t.h"
#include "../enums/PointOrientGoalDirectionType_t.h"

class CPointOrient : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPointOrient);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszSpawnTargetName);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hTarget);
    SCHEMA_FIELD(bool, m_bActive);
    SCHEMA_FIELD(PointOrientGoalDirectionType_t, m_nGoalDirection);
    SCHEMA_FIELD(PointOrientConstraint_t, m_nConstraint);
    SCHEMA_FIELD(float, m_flMaxTurnRate);
    SCHEMA_FIELD(float, m_flLastGameTime);
};
