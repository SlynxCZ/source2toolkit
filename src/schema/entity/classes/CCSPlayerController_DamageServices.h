#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CDamageRecord.h"
#include "CPlayerControllerComponent.h"

class CCSPlayerController_DamageServices : public CPlayerControllerComponent
{
public:
    DECLARE_SCHEMA_CLASS(CCSPlayerController_DamageServices);

    SCHEMA_FIELD(int32_t, m_nSendUpdate);
    SCHEMA_FIELD(CUtlVector<CDamageRecord>, m_DamageList);
};
