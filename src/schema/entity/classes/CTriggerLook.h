#pragma once
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

#include "CTriggerOnce.h"

class CBaseEntity;

class CTriggerLook : public CTriggerOnce, public CBaseEntity::Factory<CTriggerLook>
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerLook);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hLookTarget);
    SCHEMA_FIELD(float, m_flFieldOfView);
    SCHEMA_FIELD(float, m_flLookTime);
    SCHEMA_FIELD(float, m_flLookTimeTotal);
    SCHEMA_FIELD(float, m_flLookTimeLast);
    SCHEMA_FIELD(float, m_flTimeoutDuration);
    SCHEMA_FIELD(bool, m_bTimeoutFired);
    SCHEMA_FIELD(bool, m_bIsLooking);
    SCHEMA_FIELD(bool, m_b2DFOV);
    SCHEMA_FIELD(bool, m_bUseVelocity);
    SCHEMA_FIELD(bool, m_bTestOcclusion);
    SCHEMA_FIELD(bool, m_bTestAllVisibleOcclusion);
    SCHEMA_FIELD(CEntityIOOutput, m_OnTimeout);
    SCHEMA_FIELD(CEntityIOOutput, m_OnStartLook);
    SCHEMA_FIELD(CEntityIOOutput, m_OnEndLook);
};
