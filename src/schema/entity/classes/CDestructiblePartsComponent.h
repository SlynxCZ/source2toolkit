#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CNetworkVarChainer.h"

class CBaseModelEntity;

class CDestructiblePartsComponent
{
public:
    DECLARE_SCHEMA_CLASS(CDestructiblePartsComponent);

    SCHEMA_FIELD(CNetworkVarChainer, __m_pChainEntity);
    SCHEMA_FIELD(CUtlVector<uint16_t>, m_vecDamageTakenByHitGroup);
    SCHEMA_FIELD(CHandle<CBaseModelEntity>, m_hOwner);
};
