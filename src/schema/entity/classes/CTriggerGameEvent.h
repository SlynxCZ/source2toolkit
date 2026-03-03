#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"

class CTriggerGameEvent : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerGameEvent);

    SCHEMA_FIELD(CUtlString, m_strStartTouchEventName);
    SCHEMA_FIELD(CUtlString, m_strEndTouchEventName);
    SCHEMA_FIELD(CUtlString, m_strTriggerID);
};
