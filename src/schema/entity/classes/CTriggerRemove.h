#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"

class CTriggerRemove : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerRemove);

    SCHEMA_FIELD(CEntityIOOutput, m_OnRemove);
};
