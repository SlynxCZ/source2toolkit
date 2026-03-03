#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CRuleBrushEntity.h"

class CGamePlayerZone : public CRuleBrushEntity
{
public:
    DECLARE_SCHEMA_CLASS(CGamePlayerZone);

    SCHEMA_FIELD(CEntityIOOutput, m_OnPlayerInZone);
    SCHEMA_FIELD(CEntityIOOutput, m_OnPlayerOutZone);
};
