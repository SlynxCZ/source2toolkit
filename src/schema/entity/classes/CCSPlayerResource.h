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

#include "CBaseEntity.h"

class CCSPlayerResource : public CBaseEntity, public CBaseEntity::Factory<CCSPlayerResource>
{
public:
    DECLARE_SCHEMA_CLASS(CCSPlayerResource);

    SCHEMA_FIELD_POINTER(bool, m_bHostageAlive);
    SCHEMA_FIELD_POINTER(bool, m_isHostageFollowingSomeone);
    SCHEMA_FIELD_POINTER(CEntityIndex, m_iHostageEntityIDs);
    SCHEMA_FIELD(Vector, m_bombsiteCenterA);
    SCHEMA_FIELD(Vector, m_bombsiteCenterB);
    SCHEMA_FIELD_POINTER(int32_t, m_hostageRescueX);
    SCHEMA_FIELD_POINTER(int32_t, m_hostageRescueY);
    SCHEMA_FIELD_POINTER(int32_t, m_hostageRescueZ);
    SCHEMA_FIELD(bool, m_bEndMatchNextMapAllVoted);
    SCHEMA_FIELD(bool, m_foundGoalPositions);
};
