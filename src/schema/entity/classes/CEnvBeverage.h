#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CEnvBeverage : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvBeverage);

    SCHEMA_FIELD(bool, m_CanInDispenser);
    SCHEMA_FIELD(int32_t, m_nBeverageType);
};
