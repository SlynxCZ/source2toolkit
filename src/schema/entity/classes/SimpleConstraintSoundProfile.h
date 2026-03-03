#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class SimpleConstraintSoundProfile
{
public:
    DECLARE_SCHEMA_CLASS(SimpleConstraintSoundProfile);

    SCHEMA_FIELD(float, m_flKeyPointMinSoundThreshold);
    SCHEMA_FIELD(float, m_flKeyPointMaxSoundThreshold);
    SCHEMA_FIELD(float, m_reversalSoundThresholdSmall);
    SCHEMA_FIELD(float, m_reversalSoundThresholdMedium);
    SCHEMA_FIELD(float, m_reversalSoundThresholdLarge);
};
