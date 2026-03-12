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

#include "CPointEntity.h"

class CBaseEntity;

class CPointAngularVelocitySensor : public CPointEntity, public CBaseEntity::Factory<CPointAngularVelocitySensor>
{
public:
    DECLARE_SCHEMA_CLASS(CPointAngularVelocitySensor);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hTargetEntity);
    SCHEMA_FIELD(float, m_flThreshold);
    SCHEMA_FIELD(int32_t, m_nLastCompareResult);
    SCHEMA_FIELD(int32_t, m_nLastFireResult);
    SCHEMA_FIELD(float, m_flFireTime);
    SCHEMA_FIELD(float, m_flFireInterval);
    SCHEMA_FIELD(float, m_flLastAngVelocity);
    SCHEMA_FIELD(QAngle, m_lastOrientation);
    SCHEMA_FIELD(Vector, m_vecAxis);
    SCHEMA_FIELD(bool, m_bUseHelper);
    SCHEMA_FIELD(CEntityIOOutput, m_OnLessThan);
    SCHEMA_FIELD(CEntityIOOutput, m_OnLessThanOrEqualTo);
    SCHEMA_FIELD(CEntityIOOutput, m_OnGreaterThan);
    SCHEMA_FIELD(CEntityIOOutput, m_OnGreaterThanOrEqualTo);
    SCHEMA_FIELD(CEntityIOOutput, m_OnEqualTo);
};
