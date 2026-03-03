#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CCSGameModeRules.h"

class CCSGameModeRules_ArmsRace : public CCSGameModeRules
{
public:
    DECLARE_SCHEMA_CLASS(CCSGameModeRules_ArmsRace);

    SCHEMA_FIELD(CUtlVector<CUtlString>, m_WeaponSequence);
};
