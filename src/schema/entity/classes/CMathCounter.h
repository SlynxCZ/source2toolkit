#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CMathCounter : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CMathCounter);

    SCHEMA_FIELD(float, m_flMin);
    SCHEMA_FIELD(float, m_flMax);
    SCHEMA_FIELD(bool, m_bHitMin);
    SCHEMA_FIELD(bool, m_bHitMax);
    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(CEntityIOOutput, m_OnHitMin);
    SCHEMA_FIELD(CEntityIOOutput, m_OnHitMax);
    SCHEMA_FIELD(CEntityIOOutput, m_OnChangedFromMin);
    SCHEMA_FIELD(CEntityIOOutput, m_OnChangedFromMax);
};
