#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CIronSightController
{
public:
    DECLARE_SCHEMA_CLASS(CIronSightController);

    SCHEMA_FIELD(bool, m_bIronSightAvailable);
    SCHEMA_FIELD(float, m_flIronSightAmount);
    SCHEMA_FIELD(float, m_flIronSightAmountGained);
    SCHEMA_FIELD(float, m_flIronSightAmountBiased);
};
