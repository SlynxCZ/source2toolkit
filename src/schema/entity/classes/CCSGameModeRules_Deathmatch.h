#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CCSGameModeRules.h"

class CCSGameModeRules_Deathmatch : public CCSGameModeRules
{
public:
    DECLARE_SCHEMA_CLASS(CCSGameModeRules_Deathmatch);

    SCHEMA_FIELD(float, m_flDMBonusStartTime);
    SCHEMA_FIELD(float, m_flDMBonusTimeLength);
    SCHEMA_FIELD(CUtlString, m_sDMBonusWeapon);
};
