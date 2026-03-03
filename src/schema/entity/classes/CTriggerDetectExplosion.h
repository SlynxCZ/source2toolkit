#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"

class CTriggerDetectExplosion : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerDetectExplosion);

    SCHEMA_FIELD(CEntityIOOutput, m_OnDetectedExplosion);
};
