#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"

class CTriggerToggleSave : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerToggleSave);

};
