#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CLogicDistanceAutosave : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicDistanceAutosave);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszTargetEntity);
    SCHEMA_FIELD(float, m_flDistanceToPlayer);
    SCHEMA_FIELD(bool, m_bForceNewLevelUnit);
    SCHEMA_FIELD(bool, m_bCheckCough);
    SCHEMA_FIELD(bool, m_bThinkDangerous);
    SCHEMA_FIELD(float, m_flDangerousTime);
};
