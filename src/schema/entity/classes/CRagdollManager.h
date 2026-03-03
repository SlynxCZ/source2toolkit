#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CRagdollManager : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CRagdollManager);

    SCHEMA_FIELD(int8_t, m_iCurrentMaxRagdollCount);
    SCHEMA_FIELD(int32_t, m_iMaxRagdollCount);
    SCHEMA_FIELD(bool, m_bSaveImportant);
    SCHEMA_FIELD(bool, m_bCanTakeDamage);
};
