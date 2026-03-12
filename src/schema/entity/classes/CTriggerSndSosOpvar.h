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

class CBaseEntity;

class CTriggerSndSosOpvar : public CBaseTrigger, public CBaseEntity::Factory<CTriggerSndSosOpvar>
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerSndSosOpvar);

    SCHEMA_FIELD(CUtlVector<CHandle<CBaseEntity>>, m_hTouchingPlayers);
    SCHEMA_FIELD(Vector, m_flPosition);
    SCHEMA_FIELD(float, m_flCenterSize);
    SCHEMA_FIELD(float, m_flMinVal);
    SCHEMA_FIELD(float, m_flMaxVal);
    SCHEMA_FIELD(CUtlSymbolLarge, m_opvarName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_stackName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_operatorName);
    SCHEMA_FIELD(bool, m_bVolIs2D);
    SCHEMA_FIELD_POINTER(char, m_opvarNameChar);
    SCHEMA_FIELD_POINTER(char, m_stackNameChar);
    SCHEMA_FIELD_POINTER(char, m_operatorNameChar);
    SCHEMA_FIELD(Vector, m_VecNormPos);
    SCHEMA_FIELD(float, m_flNormCenterSize);
};
