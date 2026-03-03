#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CLogicGameEventListener : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicGameEventListener);

    SCHEMA_FIELD(CEntityIOOutput, m_OnEventFired);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszGameEventName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszGameEventItem);
    SCHEMA_FIELD(bool, m_bEnabled);
    SCHEMA_FIELD(bool, m_bStartDisabled);
};
