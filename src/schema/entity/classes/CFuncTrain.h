#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBasePlatTrain.h"

class CBaseEntity;

class CFuncTrain : public CBasePlatTrain
{
public:
    DECLARE_SCHEMA_CLASS(CFuncTrain);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hCurrentTarget);
    SCHEMA_FIELD(bool, m_activated);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hEnemy);
    SCHEMA_FIELD(float, m_flBlockDamage);
    SCHEMA_FIELD(float, m_flNextBlockTime);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszLastTarget);
};
