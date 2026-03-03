#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CServerOnlyPointEntity.h"

class SpawnPoint : public CServerOnlyPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(SpawnPoint);

    SCHEMA_FIELD(int32_t, m_iPriority);
    SCHEMA_FIELD(bool, m_bEnabled);
    SCHEMA_FIELD(int32_t, m_nType);
};
