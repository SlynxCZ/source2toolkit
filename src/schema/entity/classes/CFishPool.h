#pragma once
#include "CBaseEntity.h"
#include "igameevents.h"
#include "ehandle.h"
#include "entityhandle.h"
#include "vector.h"
#include "utlsymbol.h"
#include "utlsymbollarge.h"
#include "utlstring.h"
#include "utlstringtoken.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"
#include "CountdownTimer.h"

class CFish;

class CFishPool : public CBaseEntity, public CBaseEntity::Factory<CFishPool>
{
public:
    DECLARE_SCHEMA_CLASS(CFishPool);

    SCHEMA_FIELD(int32_t, m_fishCount);
    SCHEMA_FIELD(float, m_maxRange);
    SCHEMA_FIELD(float, m_swimDepth);
    SCHEMA_FIELD(float, m_waterLevel);
    SCHEMA_FIELD(bool, m_isDormant);
    SCHEMA_FIELD(CUtlVector<CHandle<CFish>>, m_fishes);
    SCHEMA_FIELD(CountdownTimer, m_visTimer);
};
