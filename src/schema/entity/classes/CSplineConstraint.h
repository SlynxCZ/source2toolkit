#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPhysConstraint.h"

class CBaseEntity;

class CSplineConstraint : public CPhysConstraint
{
public:
    DECLARE_SCHEMA_CLASS(CSplineConstraint);

    SCHEMA_FIELD(Vector, m_vAnchorOffsetRestore);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hSplineEntity);
    SCHEMA_FIELD(bool, m_bEnableLateralConstraint);
    SCHEMA_FIELD(bool, m_bEnableVerticalConstraint);
    SCHEMA_FIELD(bool, m_bEnableAngularConstraint);
    SCHEMA_FIELD(bool, m_bEnableLimit);
    SCHEMA_FIELD(bool, m_bFireEventsOnPath);
    SCHEMA_FIELD(float, m_flLinearFrequency);
    SCHEMA_FIELD(float, m_flLinarDampingRatio);
    SCHEMA_FIELD(float, m_flJointFriction);
    SCHEMA_FIELD(float, m_flTransitionTime);
    SCHEMA_FIELD(Vector, m_vPreSolveAnchorPos);
    SCHEMA_FIELD(float, m_StartTransitionTime);
    SCHEMA_FIELD(Vector, m_vTangentSpaceAnchorAtTransitionStart);
};
