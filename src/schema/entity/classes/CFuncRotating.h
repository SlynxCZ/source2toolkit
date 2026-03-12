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

#include "CBaseModelEntity.h"

class CFuncRotating : public CBaseModelEntity, public CBaseEntity::Factory<CFuncRotating>
{
public:
    DECLARE_SCHEMA_CLASS(CFuncRotating);

    SCHEMA_FIELD(CEntityIOOutput, m_OnStopped);
    SCHEMA_FIELD(CEntityIOOutput, m_OnStarted);
    SCHEMA_FIELD(CEntityIOOutput, m_OnReachedStart);
    SCHEMA_FIELD(RotationVector, m_localRotationVector);
    SCHEMA_FIELD(float, m_flFanFriction);
    SCHEMA_FIELD(float, m_flAttenuation);
    SCHEMA_FIELD(float, m_flVolume);
    SCHEMA_FIELD(float, m_flTargetSpeed);
    SCHEMA_FIELD(float, m_flMaxSpeed);
    SCHEMA_FIELD(float, m_flBlockDamage);
    SCHEMA_FIELD(CUtlSymbolLarge, m_NoiseRunning);
    SCHEMA_FIELD(bool, m_bReversed);
    SCHEMA_FIELD(bool, m_bAccelDecel);
    SCHEMA_FIELD(QAngle, m_prevLocalAngles);
    SCHEMA_FIELD(QAngle, m_angStart);
    SCHEMA_FIELD(bool, m_bStopAtStartPos);
    SCHEMA_FIELD(Vector, m_vecClientOrigin);
    SCHEMA_FIELD(QAngle, m_vecClientAngles);
};
