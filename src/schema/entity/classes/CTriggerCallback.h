#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"

class CTriggerCallback : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerCallback);

};
