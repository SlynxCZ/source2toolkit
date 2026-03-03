#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "../enums/attributeprovidertypes_t.h"

class CBaseEntity;

class CAttributeManager
{
public:
    DECLARE_SCHEMA_CLASS(CAttributeManager);

    SCHEMA_FIELD(CUtlVector<CHandle<CBaseEntity>>, m_Providers);
    SCHEMA_FIELD(int32_t, m_iReapplyProvisionParity);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hOuter);
    SCHEMA_FIELD(bool, m_bPreventLoopback);
    SCHEMA_FIELD(attributeprovidertypes_t, m_ProviderType);
    SCHEMA_FIELD(CUtlVector<CAttributeManager::cached_attribute_float_t>, m_CachedResults);
};
