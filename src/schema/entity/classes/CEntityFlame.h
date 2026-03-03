#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CEntityFlame : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEntityFlame);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hEntAttached);
    SCHEMA_FIELD(bool, m_bCheapEffect);
    SCHEMA_FIELD(float, m_flSize);
    SCHEMA_FIELD(bool, m_bUseHitboxes);
    SCHEMA_FIELD(int32_t, m_iNumHitboxFires);
    SCHEMA_FIELD(float, m_flHitboxFireScale);
    SCHEMA_FIELD(float, m_flLifetime);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hAttacker);
    SCHEMA_FIELD(float, m_flDirectDamagePerSecond);
    SCHEMA_FIELD(int32_t, m_iCustomDamageType);
};
