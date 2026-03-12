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

#include "ConstraintSoundInfo.h"
#include "CPhysConstraint.h"

class CPhysSlideConstraint : public CPhysConstraint, public CBaseEntity::Factory<CPhysSlideConstraint>
{
public:
    DECLARE_SCHEMA_CLASS(CPhysSlideConstraint);

    SCHEMA_FIELD(Vector, m_axisEnd);
    SCHEMA_FIELD(float, m_slideFriction);
    SCHEMA_FIELD(float, m_systemLoadScale);
    SCHEMA_FIELD(float, m_initialOffset);
    SCHEMA_FIELD(bool, m_bEnableLinearConstraint);
    SCHEMA_FIELD(bool, m_bEnableAngularConstraint);
    SCHEMA_FIELD(float, m_flMotorFrequency);
    SCHEMA_FIELD(float, m_flMotorDampingRatio);
    SCHEMA_FIELD(bool, m_bUseEntityPivot);
    SCHEMA_FIELD(ConstraintSoundInfo, m_soundInfo);
};
