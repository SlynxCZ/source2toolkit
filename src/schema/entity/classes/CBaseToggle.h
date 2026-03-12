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

#include "CBaseModelEntity.h"
#include "../enums/TOGGLE_STATE.h"

class CBaseEntity;

class CBaseToggle : public CBaseModelEntity, public CBaseEntity::Factory<CBaseToggle>
{
public:
    DECLARE_SCHEMA_CLASS(CBaseToggle);

    SCHEMA_FIELD(TOGGLE_STATE, m_toggle_state);
    SCHEMA_FIELD(float, m_flMoveDistance);
    SCHEMA_FIELD(float, m_flWait);
    SCHEMA_FIELD(float, m_flLip);
    SCHEMA_FIELD(bool, m_bAlwaysFireBlockedOutputs);
    SCHEMA_FIELD(Vector, m_vecPosition1);
    SCHEMA_FIELD(Vector, m_vecPosition2);
    SCHEMA_FIELD(QAngle, m_vecMoveAng);
    SCHEMA_FIELD(QAngle, m_vecAngle1);
    SCHEMA_FIELD(QAngle, m_vecAngle2);
    SCHEMA_FIELD(float, m_flHeight);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hActivator);
    SCHEMA_FIELD(Vector, m_vecFinalDest);
    SCHEMA_FIELD(QAngle, m_vecFinalAngle);
    SCHEMA_FIELD(int32_t, m_movementType);
    SCHEMA_FIELD(CUtlSymbolLarge, m_sMaster);
};
