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

#include "CPhysConstraint.h"

class CBaseEntity;

class CPhysWheelConstraint : public CPhysConstraint, public CBaseEntity::Factory<CPhysWheelConstraint>
{
public:
    DECLARE_SCHEMA_CLASS(CPhysWheelConstraint);

    SCHEMA_FIELD(float, m_flSuspensionFrequency);
    SCHEMA_FIELD(float, m_flSuspensionDampingRatio);
    SCHEMA_FIELD(float, m_flSuspensionHeightOffset);
    SCHEMA_FIELD(bool, m_bEnableSuspensionLimit);
    SCHEMA_FIELD(float, m_flMinSuspensionOffset);
    SCHEMA_FIELD(float, m_flMaxSuspensionOffset);
    SCHEMA_FIELD(bool, m_bEnableSteeringLimit);
    SCHEMA_FIELD(float, m_flMinSteeringAngle);
    SCHEMA_FIELD(float, m_flMaxSteeringAngle);
    SCHEMA_FIELD(float, m_flSteeringAxisFriction);
    SCHEMA_FIELD(float, m_flSpinAxisFriction);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hSteeringMimicsEntity);
};
