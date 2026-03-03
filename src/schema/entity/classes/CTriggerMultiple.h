#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"

class CTriggerMultiple : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerMultiple);

    SCHEMA_FIELD(CEntityIOOutput, m_OnTrigger);
};
