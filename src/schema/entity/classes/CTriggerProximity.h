#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"

class CBaseEntity;

class CTriggerProximity : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerProximity);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hMeasureTarget);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszMeasureTarget);
    SCHEMA_FIELD(float, m_fRadius);
    SCHEMA_FIELD(int32_t, m_nTouchers);
};
