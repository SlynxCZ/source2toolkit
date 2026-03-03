#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"

class CTonemapTrigger : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CTonemapTrigger);

    SCHEMA_FIELD(CUtlSymbolLarge, m_tonemapControllerName);
    SCHEMA_FIELD(CEntityHandle, m_hTonemapController);
};
