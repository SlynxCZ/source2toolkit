#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CTriggerMultiple.h"

class CTriggerOnce : public CTriggerMultiple
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerOnce);

};
