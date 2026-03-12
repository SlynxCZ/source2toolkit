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

#include "CBaseTrigger.h"

class CTriggerTeleport : public CBaseTrigger, public CBaseEntity::Factory<CTriggerTeleport>
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerTeleport);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iLandmark);
    SCHEMA_FIELD(bool, m_bUseLandmarkAngles);
    SCHEMA_FIELD(bool, m_bMirrorPlayer);
    SCHEMA_FIELD(bool, m_bCheckDestIfClearForPlayer);
};
