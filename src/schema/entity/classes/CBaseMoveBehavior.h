#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPathKeyFrame.h"

class CBaseMoveBehavior : public CPathKeyFrame
{
public:
    DECLARE_SCHEMA_CLASS(CBaseMoveBehavior);

    SCHEMA_FIELD(int32_t, m_iPositionInterpolator);
    SCHEMA_FIELD(int32_t, m_iRotationInterpolator);
    SCHEMA_FIELD(float, m_flAnimStartTime);
    SCHEMA_FIELD(float, m_flAnimEndTime);
    SCHEMA_FIELD(float, m_flAverageSpeedAcrossFrame);
    SCHEMA_FIELD(CPathKeyFrame*, m_pCurrentKeyFrame);
    SCHEMA_FIELD(CPathKeyFrame*, m_pTargetKeyFrame);
    SCHEMA_FIELD(CPathKeyFrame*, m_pPreKeyFrame);
    SCHEMA_FIELD(CPathKeyFrame*, m_pPostKeyFrame);
    SCHEMA_FIELD(float, m_flTimeIntoFrame);
    SCHEMA_FIELD(int32_t, m_iDirection);
};
