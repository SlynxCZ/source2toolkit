#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CCSGameModeRules.h"

class CCSGameModeRules_Noop : public CCSGameModeRules
{
public:
    DECLARE_SCHEMA_CLASS(CCSGameModeRules_Noop);

};
