#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>


class CBaseModelEntity;

class CDestructiblePartsComponent
{
public:
    DECLARE_SCHEMA_CLASS(CDestructiblePartsComponent);

    SCHEMA_FIELD(CEntityInstance*, __m_pChainEntity);
    SCHEMA_FIELD(CUtlVector<uint16_t>, m_vecDamageTakenByHitGroup);
    SCHEMA_FIELD(CHandle<CBaseModelEntity>, m_hOwner);
};
