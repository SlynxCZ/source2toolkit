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

#include "CLogicalEntity.h"
#include "CMotorController.h"

class CBaseEntity;

class CPhysMotor : public CLogicalEntity, public CBaseEntity::Factory<CPhysMotor>
{
public:
    DECLARE_SCHEMA_CLASS(CPhysMotor);

    SCHEMA_FIELD(CUtlSymbolLarge, m_nameAttach);
    SCHEMA_FIELD(CUtlSymbolLarge, m_nameAnchor);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hAttachedObject);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hAnchorObject);
    SCHEMA_FIELD(float, m_spinUp);
    SCHEMA_FIELD(float, m_spinDown);
    SCHEMA_FIELD(float, m_flMotorFriction);
    SCHEMA_FIELD(float, m_additionalAcceleration);
    SCHEMA_FIELD(float, m_angularAcceleration);
    SCHEMA_FIELD(float, m_flTorqueScale);
    SCHEMA_FIELD(float, m_flTargetSpeed);
    SCHEMA_FIELD(float, m_flSpeedWhenSpinUpOrSpinDownStarted);
    SCHEMA_FIELD(CMotorController, m_motor);
};
