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

#include "CPointEntity.h"

class CBaseEntity;

class CPointAngleSensor : public CPointEntity, public CBaseEntity::Factory<CPointAngleSensor>
{
public:
    DECLARE_SCHEMA_CLASS(CPointAngleSensor);

    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(CUtlSymbolLarge, m_nLookAtName);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hTargetEntity);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hLookAtEntity);
    SCHEMA_FIELD(float, m_flDuration);
    SCHEMA_FIELD(float, m_flDotTolerance);
    SCHEMA_FIELD(float, m_flFacingTime);
    SCHEMA_FIELD(bool, m_bFired);
    SCHEMA_FIELD(CEntityIOOutput, m_OnFacingLookat);
    SCHEMA_FIELD(CEntityIOOutput, m_OnNotFacingLookat);
};
