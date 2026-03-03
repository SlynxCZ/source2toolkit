#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CBaseEntity;

class CLogicBranch : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicBranch);

    SCHEMA_FIELD(bool, m_bInValue);
    SCHEMA_FIELD(CUtlVector<CHandle<CBaseEntity>>, m_Listeners);
    SCHEMA_FIELD(CEntityIOOutput, m_OnTrue);
    SCHEMA_FIELD(CEntityIOOutput, m_OnFalse);
};
