#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CLogicAchievement : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicAchievement);

    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszAchievementEventID);
    SCHEMA_FIELD(CEntityIOOutput, m_OnFired);
};
